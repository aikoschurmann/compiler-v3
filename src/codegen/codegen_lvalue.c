#include "codegen_internal.h"

LLVMValueRef codegen_lvalue(CodegenContext *ctx, AstNode *expr) {
    if (!expr) return NULL;
    if (!expr->type) ICE_AT(expr, "LValue node missing type.");

    if (expr->node_type == AST_IDENTIFIER) {
        AstIdentifier *ident = &expr->data.identifier;
        
        // 1. Try local variables first
        if (ident->intern_result) {
            void *key = (void*)(intptr_t)ident->intern_result->entry->dense_index;
            LLVMValueRef val = codegen_map_get(ctx->locals, key);
            if (val) return val;
        }

        // 2. Try global/mangled symbols
        CompilationUnit *current_unit = module_loader_get_unit(ctx->loader, expr->filename);
        if (current_unit && current_unit->global_scope) {
            Symbol *sym = scope_lookup_symbol(current_unit->global_scope, ident->intern_result, expr->filename);
            if (sym) {
                CompilationUnit *origin_unit = module_loader_get_unit(ctx->loader, sym->filename);
                char *mangled = mangle_name(ctx, origin_unit, ident->intern_result);
                
                LLVMValueRef val = LLVMGetNamedFunction(ctx->module, mangled);
                if (!val) val = LLVMGetNamedGlobal(ctx->module, mangled);
                
                free(mangled);
                if (val) return val;
            }
        }

        ICE_AT(expr, "Identifier '%s' could not be resolved to an lvalue.", ((Slice*)ident->intern_result->key)->ptr);
        return NULL;
    }

    if (expr->node_type == AST_SUBSCRIPT_EXPR) {
        AstSubscriptExpr *sub = &expr->data.subscript_expr;
        Type *target_type = sub->target->type;
        if (!target_type) ICE_AT(sub->target, "Subscript target missing type.");
        LLVMValueRef idx = codegen_expr(ctx, sub->index);

        if (target_type->kind == TYPE_ARRAY) {
            if (target_type->as.array.size_known) {
                // target is a pointer to the array [N x T]*
                LLVMValueRef target = codegen_lvalue(ctx, sub->target);
                LLVMTypeRef arr_ty = get_llvm_type(ctx, target_type);
                LLVMValueRef indices[] = {
                    LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0),
                    idx
                };
                return LLVMBuildInBoundsGEP2(ctx->builder, arr_ty, target, indices, 2, "arrayidx");
            } else {
                // Fat Pointer (Slice): target is a pointer to the struct {T*, i64}*
                LLVMValueRef struct_ptr = codegen_lvalue(ctx, sub->target);
                if (!struct_ptr) ICE_AT(sub->target, "Subscript target failed to resolve.");
                LLVMTypeRef struct_ty = get_llvm_type(ctx, target_type);
                
                // 1. Extract the 'ptr' field (Index 0)
                LLVMValueRef data_ptr_ptr = LLVMBuildStructGEP2(ctx->builder, struct_ty, struct_ptr, 0, "data_ptr_ptr");
                LLVMTypeRef elem_ptr_ty = LLVMStructGetTypeAtIndex(struct_ty, 0);
                LLVMValueRef data_ptr = LLVMBuildLoad2(ctx->builder, elem_ptr_ty, data_ptr_ptr, "data_ptr");

                // 2. GEP from the extracted pointer
                LLVMTypeRef elem_ty = get_llvm_type(ctx, target_type->as.array.base);
                return LLVMBuildGEP2(ctx->builder, elem_ty, data_ptr, &idx, 1, "arrayidx");
            }
        } else {
            // Pointer or String: target is the pointer itself (T*) or (i8*)
            LLVMValueRef target = codegen_expr(ctx, sub->target);
            LLVMTypeRef elem_ty = NULL;
            
            if (target_type->kind == TYPE_POINTER) {
                elem_ty = get_llvm_type(ctx, target_type->as.ptr.base);
            } else if (target_type->kind == TYPE_PRIMITIVE && target_type->as.primitive == PRIM_STR) {
                elem_ty = LLVMInt8TypeInContext(ctx->context);
            } else {
                ICE_AT(sub->target, "Subscript target must be array, pointer, or string");
            }
            
            return LLVMBuildGEP2(ctx->builder, elem_ty, target, &idx, 1, "ptr_idx");
        }
    }

    if (expr->node_type == AST_MEMBER_EXPR) {
        AstMemberExpr *mem_expr = &expr->data.member_expr;
        
        // Module access handling
        if (mem_expr->symbol) {
            CompilationUnit *u = module_loader_get_unit(ctx->loader, mem_expr->symbol->filename);
            if (!u) ICE("Failed to find CompilationUnit for symbol in '%s'", mem_expr->symbol->filename ? mem_expr->symbol->filename : "unknown");
            
            char *mangled = mangle_name(ctx, u, mem_expr->member);
            LLVMValueRef val = LLVMGetNamedFunction(ctx->module, mangled);
            if (!val) val = LLVMGetNamedGlobal(ctx->module, mangled);
            
            if (!val) ICE("Failed to find LLVM value for mangled symbol '%s'", mangled);
            
            free(mangled);
            return val;
        }

        Type *target_type = mem_expr->target->type;
        if (!target_type) ICE_AT(mem_expr->target, "Member expression target missing type.");

        if (target_type->kind == TYPE_ARRAY) {
             if (!target_type->as.array.size_known) {
                 LLVMValueRef target_lvalue = codegen_lvalue(ctx, mem_expr->target);
                 if (!target_lvalue) ICE_AT(mem_expr->target, "Member expression target failed to resolve.");
                 LLVMTypeRef struct_ty = get_llvm_type(ctx, target_type);
                 // Index 1 for 'len'
                 return LLVMBuildStructGEP2(ctx->builder, struct_ty, target_lvalue, 1, "len_gep");
             }
        }

        Type *underlying = target_type;
        if (underlying->kind == TYPE_POINTER) underlying = underlying->as.ptr.base;

        if (underlying->kind == TYPE_STRUCT) {
            LLVMValueRef target_lvalue = codegen_lvalue(ctx, mem_expr->target);
            if (!target_lvalue) ICE_AT(mem_expr->target, "Member expression target failed to resolve.");

            // If target was a pointer, we need to load it first to get the struct pointer
            if (target_type->kind == TYPE_POINTER) {
                LLVMTypeRef ptr_ty = get_llvm_type(ctx, target_type);
                target_lvalue = LLVMBuildLoad2(ctx->builder, ptr_ty, target_lvalue, "deref_ptr");
            }

            LLVMTypeRef struct_ty = get_llvm_type(ctx, underlying);
            return LLVMBuildStructGEP2(ctx->builder, struct_ty, target_lvalue, mem_expr->field_index, "field_gep");
        }
        ICE_AT(expr, "Member access requires struct or slice");
    }

    if (expr->node_type == AST_UNARY_EXPR && expr->data.unary_expr.op == OP_DEREF) {
        return codegen_expr(ctx, expr->data.unary_expr.expr);
    }

    ICE_AT(expr, "Unhandled lvalue node type %d", expr->node_type);
}
