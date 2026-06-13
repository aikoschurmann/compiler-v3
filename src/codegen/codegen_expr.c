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
    if (!expr->type) ICE("Literal node missing type.");
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
    if (!expr->type) ICE_AT(expr, "Identifier '%s' missing type.", ((Slice*)expr->data.identifier.intern_result->key)->ptr);
    
    LLVMValueRef ptr = codegen_lvalue(ctx, expr);
    return codegen_load_value(ctx, ptr, expr->type);
}

LLVMValueRef codegen_expr_member(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE("Member expression missing type.");
    
    AstMemberExpr *mem_expr = &expr->data.member_expr;
    Type *target_type = mem_expr->target->type;
    if (!target_type) ICE("Member expression target missing type.");

    if (target_type->kind == TYPE_ARRAY && target_type->as.array.size_known) return LLVMConstInt(LLVMInt64TypeInContext(ctx->context), target_type->as.array.size, 0);
    
    LLVMValueRef target_lvalue = codegen_lvalue(ctx, mem_expr->target);
    
    // If target was a pointer, we need to load it first to get the struct pointer
    if (target_type->kind == TYPE_POINTER) {
        LLVMTypeRef ptr_ty = get_llvm_type(ctx, target_type);
        target_lvalue = LLVMBuildLoad2(ctx->builder, ptr_ty, target_lvalue, "deref_ptr");
    }

    Type *underlying = target_type->kind == TYPE_POINTER ? target_type->as.ptr.base : target_type;
    LLVMValueRef field_ptr = LLVMBuildStructGEP2(ctx->builder, get_llvm_type(ctx, underlying), target_lvalue, mem_expr->field_index, "field_gep");
    
    return codegen_load_value(ctx, field_ptr, expr->type);
}

LLVMValueRef codegen_expr_struct_literal(CodegenContext *ctx, AstNode *expr) {
    if (!expr->type) ICE("Struct literal missing type.");
    
    AstStructLiteral *lit = &expr->data.struct_literal;
    LLVMTypeRef struct_ty = get_llvm_type(ctx, expr->type);
    LLVMValueRef alloca = LLVMBuildAlloca(ctx->builder, struct_ty, "struct_lit");
    for (size_t i = 0; i < (lit->fields ? lit->fields->count : 0); i++) {
        AstFieldInit *init = (AstFieldInit*)dynarray_get(lit->fields, i);
        LLVMBuildStore(ctx->builder, codegen_expr(ctx, init->expr), LLVMBuildStructGEP2(ctx->builder, struct_ty, alloca, (unsigned int)init->field_index, "field_ptr"));
    }
    return LLVMBuildLoad2(ctx->builder, struct_ty, alloca, "struct_val");
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
    
    // If we have a constant value from semantic analysis, use it.
    // However, string literals still need LLVMBuildGlobalStringPtr which requires a builder.
    // For global initializers, we might need a different approach for strings.
    if (expr->is_const_expr && expr->const_value.type != STRING_LITERAL) {
        return codegen_const_value(ctx, expr->type, &expr->const_value);
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
        case AST_IF_STATEMENT: case AST_WHILE_STATEMENT: case AST_FOR_STATEMENT: case AST_BREAK_STATEMENT: case AST_CONTINUE_STATEMENT: return codegen_expr_flow(ctx, expr);
        case AST_BLOCK: case AST_RETURN_STATEMENT: case AST_VARIABLE_DECLARATION: case AST_INITIALIZER_LIST: case AST_EXPR_STATEMENT: return codegen_expr_stmt(ctx, expr);
        default: {
            ICE("Node type %d missing codegen implementation.", expr->node_type);
            return NULL;
        }
    }
}