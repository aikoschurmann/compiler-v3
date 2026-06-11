#include "codegen_internal.h"

LLVMValueRef codegen_expr_stmt(CodegenContext *ctx, AstNode *expr) {
    if (expr->node_type == AST_BLOCK) {
        DynArray *stmts = expr->data.block.statements;
        LLVMValueRef last_val = NULL;

        ctx->locals = codegen_map_create(ctx->locals);

        for (size_t i = 0; i < stmts->count; i++) {
            AstNode *stmt = *(AstNode**)dynarray_get(stmts, i);
            last_val = codegen_expr(ctx, stmt);
        }

        CodegenMap *old = ctx->locals;
        ctx->locals = old->parent;
        codegen_map_destroy(old);

        return last_val;
    }

    if (expr->node_type == AST_RETURN_STATEMENT) {
        if (expr->data.return_statement.expression) {
            LLVMValueRef retval = codegen_expr(ctx, expr->data.return_statement.expression);
            if (!retval) {
                LLVMTypeRef ty = get_llvm_type(ctx, expr->data.return_statement.expression->type);
                if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind)
                    retval = LLVMConstNull(ty);
            }
            if (retval) return LLVMBuildRet(ctx->builder, retval);
        }
        return LLVMBuildRetVoid(ctx->builder);
    }

    if (expr->node_type == AST_VARIABLE_DECLARATION) {
        AstVariableDeclaration *vdecl = &expr->data.variable_declaration;
        LLVMTypeRef  ty    = get_llvm_type(ctx, expr->type);
        LLVMValueRef alloca = LLVMBuildAlloca(ctx->builder, ty, "var");

        if (vdecl->intern_result) {
            void *key = (void*)(intptr_t)vdecl->intern_result->entry->dense_index;
            codegen_map_put(ctx->locals, key, alloca);
        }
        if (vdecl->initializer) {
            LLVMValueRef init_val = codegen_expr(ctx, vdecl->initializer);
            if (init_val) LLVMBuildStore(ctx->builder, init_val, alloca);
        }
        return alloca;
    }

    if (expr->node_type == AST_INITIALIZER_LIST) {
        AstInitializeList *init  = &expr->data.initializer_list;
        size_t             count = init->elements->count;
        LLVMValueRef *vals = malloc(sizeof(LLVMValueRef) * count);

        for (size_t i = 0; i < count; i++) {
            vals[i] = codegen_expr(ctx, *(AstNode**)dynarray_get(init->elements, i));
        }

        LLVMTypeRef  ty  = get_llvm_type(ctx, expr->type);
        LLVMValueRef res = NULL;

        if (LLVMGetTypeKind(ty) == LLVMArrayTypeKind) {
            LLVMTypeRef elem_ty = LLVMGetElementType(ty);
            res = LLVMConstArray(elem_ty, vals, count);
        }
        free(vals);
        return res;
    }

    if (expr->node_type == AST_EXPR_STATEMENT) {
        return codegen_expr(ctx, expr->data.expr_statement.expression);
    }

    return NULL;
}
