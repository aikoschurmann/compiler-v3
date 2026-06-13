#include "codegen_internal.h"
#include "sema/intrinsics.h"
#include "datastructures/scope.h"

static LLVMValueRef codegen_intrinsic_print(CodegenContext *ctx, AstNode *arg, bool newline) {
    if (!arg) ICE("codegen_intrinsic_print: arg is NULL");
    if (!arg->type) ICE("codegen_intrinsic_print: arg missing type");

    const char *func_name = NULL;
    Type *t = arg->type;
    LLVMTypeRef param_t = NULL;

    if (t->kind == TYPE_PRIMITIVE) {
        switch (t->as.primitive) {
            case PRIM_I32:  
                func_name = "print_i32"; 
                param_t = LLVMInt32TypeInContext(ctx->context);
                break;
            case PRIM_I64:  
                func_name = "print_i64"; 
                param_t = LLVMInt64TypeInContext(ctx->context);
                break;
            case PRIM_F32:  
                func_name = "print_f32"; 
                param_t = LLVMFloatTypeInContext(ctx->context);
                break;
            case PRIM_F64:  
                func_name = "print_f64"; 
                param_t = LLVMDoubleTypeInContext(ctx->context);
                break;
            case PRIM_BOOL: 
                func_name = "print_bool"; 
                param_t = LLVMInt8TypeInContext(ctx->context);
                break;
            case PRIM_CHAR: 
                func_name = "print_char"; 
                param_t = LLVMInt8TypeInContext(ctx->context);
                break;
            case PRIM_STR:  
                func_name = "print_str"; 
                param_t = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
                break;
            default: break;
        }
    }

    if (!func_name) ICE("codegen_intrinsic_print: unsupported type");

    LLVMValueRef func = LLVMGetNamedFunction(ctx->module, func_name);
    if (!func) {
        LLVMTypeRef ret_ty = LLVMVoidTypeInContext(ctx->context);
        LLVMTypeRef fn_ty = LLVMFunctionType(ret_ty, &param_t, 1, 0);
        func = LLVMAddFunction(ctx->module, func_name, fn_ty);
    }

    LLVMValueRef val = codegen_expr(ctx, arg);
    LLVMValueRef call = LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(func), func, &val, 1, "");

    if (newline) {
        const char *nl_name = "print_newline";
        LLVMValueRef nl_func = LLVMGetNamedFunction(ctx->module, nl_name);
        if (!nl_func) {
            LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), NULL, 0, 0);
            nl_func = LLVMAddFunction(ctx->module, nl_name, fn_ty);
        }
        LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(nl_func), nl_func, NULL, 0, "");
    }

    return call;
}

LLVMValueRef codegen_expr_call(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE("Call expression missing type.");
    AstCallExpr *call = &expr->data.call_expr;

    // Check for intrinsic
    if (call->callee->node_type == AST_IDENTIFIER) {
        Slice *s = (Slice*)call->callee->data.identifier.intern_result->key;
        if (s->len == 5 && memcmp(s->ptr, "print", 5) == 0) {
            size_t arg_count = call->args ? call->args->count : 0;
            for (size_t i = 0; i < arg_count; i++) {
                codegen_intrinsic_print(ctx, *(AstNode**)dynarray_get(call->args, i), false);
            }
            return NULL;
        }
        if (s->len == 7 && memcmp(s->ptr, "println", 7) == 0) {
            size_t arg_count = call->args ? call->args->count : 0;
            if (arg_count == 0) {
                // Just newline
                const char *nl_name = "print_newline";
                LLVMValueRef nl_func = LLVMGetNamedFunction(ctx->module, nl_name);
                if (!nl_func) {
                    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), NULL, 0, 0);
                    nl_func = LLVMAddFunction(ctx->module, nl_name, fn_ty);
                }
                LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(nl_func), nl_func, NULL, 0, "");
            } else {
                for (size_t i = 0; i < arg_count; i++) {
                    codegen_intrinsic_print(ctx, *(AstNode**)dynarray_get(call->args, i), i == arg_count - 1);
                }
            }
            return NULL;
        }
    }

    LLVMValueRef callee = codegen_expr(ctx, call->callee);
    if (!callee) return NULL;

    Type *fn_type_sema = call->callee->type;
    bool sret = type_is_indirect(ctx, fn_type_sema->as.func.return_type);
    
    LLVMTypeRef func_type = get_llvm_function_type(ctx, fn_type_sema);
    
    size_t param_count = call->args ? call->args->count : 0;
    size_t llvm_arg_count = param_count + (sret ? 1 : 0);
    LLVMValueRef *args = malloc(sizeof(LLVMValueRef) * llvm_arg_count);
    
    LLVMValueRef sret_alloca = NULL;
    size_t idx = 0;
    
    if (sret) {
        sret_alloca = LLVMBuildAlloca(ctx->builder, get_llvm_type(ctx, fn_type_sema->as.func.return_type), "sret_temp");
        args[idx++] = sret_alloca;
    }

    for (size_t i = 0; i < param_count; i++) {
        AstNode *arg_node = *(AstNode**)dynarray_get(call->args, i);
        Type *param_type = fn_type_sema->as.func.params[i];
        
        if (type_is_indirect(ctx, param_type)) {
            // Must pass by value (copy into alloca), then pass pointer
            LLVMValueRef val = codegen_expr(ctx, arg_node);
            LLVMValueRef alloca = LLVMBuildAlloca(ctx->builder, get_llvm_type(ctx, param_type), "byval_temp");
            LLVMBuildStore(ctx->builder, val, alloca);
            args[idx++] = alloca;
        } else if (arg_node->type->kind == TYPE_ARRAY && arg_node->type->as.array.size_known && param_type->kind == TYPE_ARRAY && !param_type->as.array.size_known) {
            // Decay to fat pointer
            LLVMValueRef ptr = codegen_expr(ctx, arg_node);
            LLVMValueRef len = LLVMConstInt(LLVMInt64TypeInContext(ctx->context), arg_node->type->as.array.size, 0);

            LLVMTypeRef slice_ty = get_llvm_type(ctx, param_type);
            LLVMValueRef slice_val = LLVMGetUndef(slice_ty);
            slice_val = LLVMBuildInsertValue(ctx->builder, slice_val, ptr, 0, "slice_ptr");
            slice_val = LLVMBuildInsertValue(ctx->builder, slice_val, len, 1, "slice_len");
            args[idx++] = slice_val;
        } else {
            args[idx++] = codegen_expr(ctx, arg_node);
        }
        
        if (!args[idx-1]) ICE("Failed to generate code for call argument %zu", i);
    }
    
    bool is_void = LLVMGetTypeKind(LLVMGetReturnType(func_type)) == LLVMVoidTypeKind;
    LLVMValueRef call_inst = LLVMBuildCall2(ctx->builder, func_type, callee, args, (unsigned)llvm_arg_count, (sret || is_void) ? "" : "calltmp");
    
    // Add call-site attributes to match function signature
    unsigned attr_idx = 1;
    if (sret) {
        LLVMAddCallSiteAttribute(call_inst, attr_idx++, LLVMCreateTypeAttribute(ctx->context, 
            LLVMGetEnumAttributeKindForName("sret", 4), get_llvm_type(ctx, fn_type_sema->as.func.return_type)));
    }
    
    for (size_t i = 0; i < param_count; i++) {
        if (type_is_indirect(ctx, fn_type_sema->as.func.params[i])) {
            LLVMAddCallSiteAttribute(call_inst, attr_idx, LLVMCreateTypeAttribute(ctx->context, 
                LLVMGetEnumAttributeKindForName("byval", 5), get_llvm_type(ctx, fn_type_sema->as.func.params[i])));
        }
        attr_idx++;
    }
    
    free(args);
    
    return sret ? LLVMBuildLoad2(ctx->builder, get_llvm_type(ctx, fn_type_sema->as.func.return_type), sret_alloca, "sret_load") : call_inst;
}