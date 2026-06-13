#include "codegen_internal.h"

LLVMValueRef codegen_expr_stmt(CodegenContext *ctx, AstNode *expr) {
    if (expr->node_type == AST_BLOCK) {
        DynArray *stmts = expr->data.block.statements;
        LLVMValueRef last_val = NULL;

        ctx->locals = codegen_map_create(ctx, ctx->locals);
        
        // 1. Remember how many deferred actions existed before this block
        size_t previous_defer_count = ctx->deferred_actions->count;

        for (size_t i = 0; i < stmts->count; i++) {
            AstNode *stmt = *(AstNode**)dynarray_get(stmts, i);
            last_val = codegen_expr(ctx, stmt);
        }

        // 2. Execute any deferred actions added DURING this block (in LIFO order)
        for (int i = (int)ctx->deferred_actions->count - 1; i >= (int)previous_defer_count; i--) {
            AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
            codegen_expr_stmt(ctx, body);
        }
        
        // 3. Shrink the array back to its previous size
        ctx->deferred_actions->count = previous_defer_count;

        CodegenMap *old = ctx->locals;
        ctx->locals = old->parent;
        codegen_map_destroy(old);

        return last_val;
    }

    if (expr->node_type == AST_RETURN_STATEMENT) {
        // Execute deferred actions first
        for (int i = (int)ctx->deferred_actions->count - 1; i >= 0; i--) {
            AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
            codegen_expr_stmt(ctx, body);
        }

        Type *fn_type = ctx->current_func_type;
        bool sret = type_is_indirect(ctx, fn_type->as.func.return_type);
        
        if (expr->data.return_statement.expression) {
            LLVMValueRef retval = codegen_expr(ctx, expr->data.return_statement.expression);
            if (!retval) {
                LLVMTypeRef ty = get_llvm_type(ctx, expr->data.return_statement.expression->type);
                if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind)
                    retval = LLVMConstNull(ty);
            }
            if (sret) {
                LLVMBuildStore(ctx->builder, retval, ctx->sret_ptr);
                return LLVMBuildRetVoid(ctx->builder);
            } else if (retval) {
                return LLVMBuildRet(ctx->builder, retval);
            }
        }
        return LLVMBuildRetVoid(ctx->builder);
    }

    if (expr->node_type == AST_VARIABLE_DECLARATION) {
        AstVariableDeclaration *vdecl = &expr->data.variable_declaration;
        LLVMTypeRef  ty    = get_llvm_type(ctx, expr->type);
        LLVMValueRef alloca = create_entry_block_alloca(ctx, ty, "var");

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

    if (expr->node_type == AST_EXPR_STATEMENT) {
        return codegen_expr(ctx, expr->data.expr_statement.expression);
    }

    if (expr->node_type == AST_DEFER_STATEMENT) {
        dynarray_push_value(ctx->deferred_actions, &expr->data.defer_statement.body);
        return NULL;
    }

    return NULL;
}
