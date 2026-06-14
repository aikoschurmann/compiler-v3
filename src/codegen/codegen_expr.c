#include "codegen_internal.h"
#include "codegen/codegen_utils.h"

// Forward declaration
LLVMValueRef codegen_expr(CodegenContext *ctx, AstNode *expr);

LLVMValueRef codegen_expr_intrinsic(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE("Intrinsic node (kind %d) missing type.", expr->data.intrinsic.kind);
    IntrinsicKind kind = expr->data.intrinsic.kind;
    DynArray *args = expr->data.intrinsic.args;
    
    // Explicitly define types for calling conventions
    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8TypeInContext(ctx->context), 0);
    LLVMTypeRef i64ty = LLVMInt64TypeInContext(ctx->context);
    
    if (kind == INTRINSIC_ALLOC) {
        // Dynamically get arguments based on count (2 or 3 args)
        AstNode *allocator_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 1 : 0);
        AstNode *count_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 2 : 1);
        
        if (!allocator_arg->type) ICE("@alloc allocator argument missing type.");
        if (!count_arg->type) ICE("@alloc count argument missing type.");

        // 1. Target Type Extraction
        Type *target_type = expr->type;
        if (target_type->kind == TYPE_POINTER) target_type = target_type->as.ptr.base;
        LLVMTypeRef llvm_target_type = get_llvm_type(ctx, target_type);

        // 2. Evaluate Allocator and Count
        LLVMValueRef allocator_val = codegen_expr(ctx, allocator_arg);
        LLVMValueRef count_val = codegen_expr(ctx, count_arg);
        LLVMValueRef total_bytes = LLVMBuildMul(ctx->builder, 
            LLVMBuildIntCast(ctx->builder, count_val, i64ty, "count_i64"), 
            LLVMSizeOf(llvm_target_type), "alloc_bytes");

        // 3. EXTRACT: Use ExtractValue
        if (LLVMGetTypeKind(LLVMTypeOf(allocator_val)) != LLVMStructTypeKind) {
            ICE("@alloc expected struct value for allocator, got %d", LLVMGetTypeKind(LLVMTypeOf(allocator_val)));
        }
        
        // Use symbolic field indices
        size_t ctx_idx = struct_field_index(allocator_arg->type, "ctx");
        size_t alloc_idx = struct_field_index(allocator_arg->type, "alloc");
        if (ctx_idx == (size_t)-1 || alloc_idx == (size_t)-1) ICE("@alloc allocator missing required fields");
        
        LLVMValueRef ctx_val = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)ctx_idx, "ctx_val");
        LLVMValueRef alloc_fn = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)alloc_idx, "alloc_fn_val");

        // 4. CALL: Setup function type and invoke
        LLVMTypeRef alloc_fn_ty = LLVMFunctionType(i8ptr, (LLVMTypeRef[]){i8ptr, i64ty}, 2, 0);
        LLVMValueRef call_args[] = { ctx_val, total_bytes };
        LLVMValueRef raw_mem = LLVMBuildCall2(ctx->builder, alloc_fn_ty, alloc_fn, call_args, 2, "raw_mem");

        return LLVMBuildBitCast(ctx->builder, raw_mem, LLVMPointerType(llvm_target_type, 0), "typed_mem");
    }
    else if (kind == INTRINSIC_FREE) {
        AstNode *allocator_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 1 : 0);
        AstNode *ptr_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 2 : 1);

        if (!allocator_arg->type) ICE("@free allocator argument missing type.");
        if (!ptr_arg->type) ICE("@free pointer argument missing type.");

        LLVMValueRef allocator_val = codegen_expr(ctx, allocator_arg);
        LLVMValueRef ptr_val = codegen_expr(ctx, ptr_arg);

        if (LLVMGetTypeKind(LLVMTypeOf(allocator_val)) != LLVMStructTypeKind) {
            ICE("@free expected struct value for allocator, got %d", LLVMGetTypeKind(LLVMTypeOf(allocator_val)));
        }
        
        // Use symbolic field indices
        size_t ctx_idx = struct_field_index(allocator_arg->type, "ctx");
        size_t free_idx = struct_field_index(allocator_arg->type, "free");
        if (ctx_idx == (size_t)-1 || free_idx == (size_t)-1) ICE("@free allocator missing required fields");
        
        LLVMValueRef ctx_val = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)ctx_idx, "ctx_val");
        LLVMValueRef free_fn = LLVMBuildExtractValue(ctx->builder, allocator_val, (unsigned)free_idx, "free_fn_val");

        LLVMValueRef void_ptr = LLVMBuildBitCast(ctx->builder, ptr_val, i8ptr, "void_ptr");
        LLVMTypeRef free_fn_ty = LLVMFunctionType(LLVMVoidTypeInContext(ctx->context), (LLVMTypeRef[]){i8ptr, i8ptr}, 2, 0);
        LLVMValueRef call_args[] = { ctx_val, void_ptr };
        return LLVMBuildCall2(ctx->builder, free_fn_ty, free_fn, call_args, 2, "");
    }
    return NULL;
}

LLVMValueRef codegen_expr_literal(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE_AT(expr, "Literal node missing type.");
    LLVMTypeRef ty = get_llvm_type(ctx, expr->type);
    
    if (expr->data.literal.type == INT_LITERAL) {
        return LLVMConstInt(ty, expr->data.literal.value.int_val, 0);
    } else if (expr->data.literal.type == CHAR_LITERAL) {
        return LLVMConstInt(ty, (unsigned char)expr->data.literal.value.char_val, 0);
    } else if (expr->data.literal.type == BOOL_LITERAL) {
        return LLVMConstInt(ty, expr->data.literal.value.bool_val, 0);
    } else if (expr->data.literal.type == FLOAT_LITERAL) {
        return LLVMConstReal(ty, expr->data.literal.value.float_val);
    } else if (expr->data.literal.type == STRING_LITERAL) {
        InternResult *res = expr->data.literal.value.string_val;
        Slice *s = (Slice*)res->key;
        char *str = malloc(s->len + 1);
        memcpy(str, s->ptr, s->len);
        str[s->len] = '\0';
        LLVMValueRef gstr = LLVMBuildGlobalStringPtr(ctx->builder, str, "str_lit");
        free(str);
        return gstr;
    } else if (expr->data.literal.type == NULL_LITERAL) {
        return LLVMConstNull(ty);
    }
    return NULL;
}

LLVMValueRef codegen_expr_ident(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE_AT(expr, "Identifier missing type.");
    
    LLVMValueRef ptr = codegen_lvalue(ctx, expr);
    return codegen_load_value(ctx, ptr, expr->type);
}

LLVMValueRef codegen_expr_member(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE_AT(expr, "Member expression missing type.");

    // Use unified lvalue-then-load pattern
    LLVMValueRef ptr = codegen_lvalue(ctx, expr);
    if (!ptr) return NULL;

    return codegen_load_value(ctx, ptr, expr->type);
}

LLVMValueRef codegen_expr_struct_literal(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE_AT(expr, "Struct literal missing type.");

    AstStructLiteral *lit = &expr->data.struct_literal;
    LLVMTypeRef struct_ty = get_llvm_type(ctx, expr->type);

    size_t count = lit->fields ? lit->fields->count : 0;
    bool all_const = true;
    LLVMValueRef *vals = count > 0 ? malloc(sizeof(LLVMValueRef) * count) : NULL;

    for (size_t i = 0; i < count; i++) {
        AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
        vals[i] = codegen_expr(ctx, init->expr);
        
        LLVMTypeRef field_ty = get_llvm_type(ctx, expr->type->as.struct_type.fields[init->field_index].type);
        if (vals[i] && LLVMTypeOf(vals[i]) != field_ty) {
            if (LLVMIsAConstant(vals[i])) {
                vals[i] = LLVMConstBitCast(vals[i], field_ty);
            } else {
                vals[i] = LLVMBuildBitCast(ctx->builder, vals[i], field_ty, "struct_bitcast");
            }
        }

        if (!vals[i] || !LLVMIsAConstant(vals[i])) {
            all_const = false;
        }
    }

    if (all_const && count > 0) {
        size_t total_fields = expr->type->as.struct_type.field_count;
        LLVMValueRef *ordered_vals = malloc(sizeof(LLVMValueRef) * total_fields);

        // Initialize with null/undef constants
        for(size_t i=0; i < total_fields; i++) {
            ordered_vals[i] = LLVMConstNull(get_llvm_type(ctx, expr->type->as.struct_type.fields[i].type));
        }

        for (size_t i = 0; i < count; i++) {
            AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
            ordered_vals[init->field_index] = vals[i];
        }

        LLVMValueRef res = LLVMConstNamedStruct(struct_ty, ordered_vals, (unsigned int)total_fields);
        free(vals);
        free(ordered_vals);
        return res;
    }

    // Fallback to dynamic version
    LLVMValueRef alloca = create_entry_block_alloca(ctx, struct_ty, "struct_lit");
    for (size_t i = 0; i < count; i++) {
        AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
        LLVMBuildStore(ctx->builder, vals[i], LLVMBuildStructGEP2(ctx->builder, struct_ty, alloca, (unsigned int)init->field_index, "field_ptr"));
    }
    if (vals) free(vals);
    return LLVMBuildLoad2(ctx->builder, struct_ty, alloca, "struct_val");
}

LLVMValueRef codegen_expr_initializer_list(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE_AT(expr, "Initializer list missing type.");

    AstInitializeList *init  = &expr->data.initializer_list;
    size_t             count = init->elements->count;
    LLVMValueRef *vals = malloc(sizeof(LLVMValueRef) * count);
    bool all_const = true;

    for (size_t i = 0; i < count; i++) {
        vals[i] = codegen_expr(ctx, *(AstNode**)dynarray_get(init->elements, i));
        if (!vals[i] || !LLVMIsAConstant(vals[i])) {
            all_const = false;
        }
    }

    LLVMTypeRef  ty  = get_llvm_type(ctx, expr->type);
    LLVMValueRef res = NULL;

    if (LLVMGetTypeKind(ty) == LLVMArrayTypeKind) {
        LLVMTypeRef elem_ty = LLVMGetElementType(ty);
        if (all_const) {
            res = LLVMConstArray(elem_ty, vals, count);
        } else {
            LLVMValueRef alloca = create_entry_block_alloca(ctx, ty, "array_tmp");
            for (size_t i = 0; i < count; i++) {
                LLVMValueRef idxs[2] = {
                    LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0),
                    LLVMConstInt(LLVMInt32TypeInContext(ctx->context), (unsigned long long)i, 0)
                };
                LLVMValueRef gep = LLVMBuildGEP2(ctx->builder, ty, alloca, idxs, 2, "elem_ptr");
                if (vals[i]) {
                    LLVMBuildStore(ctx->builder, vals[i], gep);
                }
            }
            res = LLVMBuildLoad2(ctx->builder, ty, alloca, "array_val");
        }
    }
    free(vals);
    return res;
}

LLVMValueRef codegen_const_value(CodegenContext *ctx, Type *type, ConstValue *val) {
    LLVMTypeRef ty = get_llvm_type(ctx, type);
    if (val->type == INT_LITERAL) {
        if (LLVMGetTypeKind(ty) == LLVMPointerTypeKind) {
            if (val->value.int_val == 0) return LLVMConstNull(ty);
            return LLVMConstIntToPtr(LLVMConstInt(LLVMInt64TypeInContext(ctx->context), val->value.int_val, 0), ty);
        }
        return LLVMConstInt(ty, val->value.int_val, 0);
    } else if (val->type == FLOAT_LITERAL) {
        return LLVMConstReal(ty, val->value.float_val);
    } else if (val->type == BOOL_LITERAL) {
        return LLVMConstInt(ty, val->value.bool_val, 0);
    } else if (val->type == CHAR_LITERAL) {
        return LLVMConstInt(ty, (unsigned char)val->value.char_val, 0);
    } else if (val->type == STRING_LITERAL) {
        InternResult *res = val->value.string_val;
        Slice *s = (Slice*)res->key;
        char *str = malloc(s->len + 1);
        memcpy(str, s->ptr, s->len);
        str[s->len] = '\0';
        LLVMValueRef gstr = LLVMBuildGlobalStringPtr(ctx->builder, str, "str_lit");
        free(str);
        return gstr;
    }
    ICE("codegen_const_value: unrecognized constant type %d", val->type);
}

LLVMValueRef codegen_expr(CodegenContext *ctx, AstNode *expr) {
    if (!expr) return NULL;
    
    // Strict contract check: only value-producing nodes should be here.
    // Statements should be handled by codegen_statement.
    if (!expr->type) {
        codegen_statement(ctx, expr);
        return NULL;
    }

    if (expr->is_const_expr && expr->const_value.type != STRING_LITERAL) {
        if (expr->type && (expr->type->kind == TYPE_PRIMITIVE || expr->type->kind == TYPE_POINTER)) {
            return codegen_const_value(ctx, expr->type, &expr->const_value);
        }
    }

    switch (expr->node_type) {
        case AST_LITERAL:          return codegen_expr_literal(ctx, expr);
        case AST_IDENTIFIER:       return codegen_expr_ident(ctx, expr);
        case AST_MEMBER_EXPR:      return codegen_expr_member(ctx, expr);
        case AST_STRUCT_LITERAL:   return codegen_expr_struct_literal(ctx, expr);
        case AST_SUBSCRIPT_EXPR: {
            LLVMValueRef ptr = codegen_lvalue(ctx, expr);
            if (!ptr) return NULL;
            return codegen_load_value(ctx, ptr, expr->type);
        }
        case AST_CALL_EXPR:        return codegen_expr_call(ctx, expr);
        case AST_INTRINSIC:        return codegen_expr_intrinsic(ctx, expr);
        case AST_BINARY_EXPR: case AST_UNARY_EXPR: case AST_CAST: case AST_ASSIGNMENT_EXPR: return codegen_expr_ops(ctx, expr);
        case AST_INITIALIZER_LIST: return codegen_expr_initializer_list(ctx, expr);
        
        // Control flow and statements that don't produce values
        case AST_IF_STATEMENT:
        case AST_WHILE_STATEMENT:
        case AST_FOR_STATEMENT:
        case AST_BREAK_STATEMENT:
        case AST_CONTINUE_STATEMENT:
        case AST_BLOCK:
        case AST_RETURN_STATEMENT:
        case AST_VARIABLE_DECLARATION:
        case AST_EXPR_STATEMENT:
        case AST_DEFER_STATEMENT:
            codegen_statement(ctx, expr);
            return NULL;

        default: {
            ICE("Node type %d missing codegen implementation.", expr->node_type);
            return NULL;
        }
    }
}
