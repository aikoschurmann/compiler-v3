#include "codegen_internal.h"

LLVMValueRef codegen_expr_flow(CodegenContext *ctx, AstNode *expr) {
    if (expr->node_type == AST_IF_STATEMENT) {
        AstIfStatement *ifs  = &expr->data.if_statement;
        LLVMValueRef    cond = codegen_expr(ctx, ifs->condition);
        LLVMTypeRef cond_ty  = LLVMTypeOf(cond);

        if (LLVMGetTypeKind(cond_ty) == LLVMPointerTypeKind) {
            cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstNull(cond_ty), "cond");
        } else if (LLVMGetTypeKind(cond_ty) == LLVMIntegerTypeKind &&
                   LLVMGetIntTypeWidth(cond_ty) > 1) {
            cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstInt(cond_ty, 0, 0), "cond");
        } else if (LLVMGetTypeKind(cond_ty) == LLVMFloatTypeKind ||
                   LLVMGetTypeKind(cond_ty) == LLVMDoubleTypeKind) {
            cond = LLVMBuildFCmp(ctx->builder, LLVMRealUNE, cond, LLVMConstNull(cond_ty), "cond");
        }

        LLVMValueRef     func     = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
        LLVMBasicBlockRef then_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "then");
        LLVMBasicBlockRef else_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "else");
        LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "merge");

        LLVMBuildCondBr(ctx->builder, cond, then_bb, else_bb);

        LLVMPositionBuilderAtEnd(ctx->builder, then_bb);
        codegen_expr(ctx, ifs->then_branch);
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
            LLVMBuildBr(ctx->builder, merge_bb);

        LLVMPositionBuilderAtEnd(ctx->builder, else_bb);
        if (ifs->else_branch) codegen_expr(ctx, ifs->else_branch);
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
            LLVMBuildBr(ctx->builder, merge_bb);

        LLVMPositionBuilderAtEnd(ctx->builder, merge_bb);
        return NULL;
    }

    if (expr->node_type == AST_WHILE_STATEMENT) {
        AstWhileStatement *whl = &expr->data.while_statement;
        LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));

        LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.cond");
        LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.body");
        LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "while.end");

        LLVMBuildBr(ctx->builder, cond_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);

        LLVMValueRef cond    = codegen_expr(ctx, whl->condition);
        LLVMTypeRef  cond_ty = LLVMTypeOf(cond);

        if (LLVMGetTypeKind(cond_ty) == LLVMPointerTypeKind) {
            cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstNull(cond_ty), "cond");
        } else if (LLVMGetTypeKind(cond_ty) == LLVMIntegerTypeKind &&
                   LLVMGetIntTypeWidth(cond_ty) > 1) {
            cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstInt(cond_ty, 0, 0), "cond");
        } else if (LLVMGetTypeKind(cond_ty) == LLVMFloatTypeKind ||
                   LLVMGetTypeKind(cond_ty) == LLVMDoubleTypeKind) {
            cond = LLVMBuildFCmp(ctx->builder, LLVMRealUNE, cond, LLVMConstNull(cond_ty), "cond");
        }
        LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);

        LLVMBasicBlockRef old_cond = ctx->loop_cond_bb;
        LLVMBasicBlockRef old_end  = ctx->loop_end_bb;
        size_t old_loop_defer      = ctx->loop_defer_count;

        ctx->loop_cond_bb = cond_bb;
        ctx->loop_end_bb  = end_bb;
        ctx->loop_defer_count = ctx->deferred_actions->count;

        LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
        codegen_expr(ctx, whl->body);
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
            LLVMBuildBr(ctx->builder, cond_bb);

        ctx->loop_cond_bb = old_cond;
        ctx->loop_end_bb  = old_end;
        ctx->loop_defer_count = old_loop_defer;

        LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
        return NULL;
    }

    if (expr->node_type == AST_FOR_STATEMENT) {
        AstForStatement *fst  = &expr->data.for_statement;
        LLVMValueRef     func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));

        ctx->locals = codegen_map_create(ctx, ctx->locals);
        if (fst->init) codegen_expr(ctx, fst->init);

        LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.cond");
        LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.body");
        LLVMBasicBlockRef post_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.post");
        LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "for.end");

        LLVMBuildBr(ctx->builder, cond_bb);
        LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);

        if (fst->condition) {
            LLVMValueRef cond    = codegen_expr(ctx, fst->condition);
            LLVMTypeRef  cond_ty = LLVMTypeOf(cond);
            if (LLVMGetTypeKind(cond_ty) == LLVMPointerTypeKind) {
                cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstNull(cond_ty), "cond");
            } else if (LLVMGetTypeKind(cond_ty) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(cond_ty) > 1) {
                cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstInt(cond_ty, 0, 0), "cond");
            } else if (LLVMGetTypeKind(cond_ty) == LLVMFloatTypeKind || LLVMGetTypeKind(cond_ty) == LLVMDoubleTypeKind) {
                cond = LLVMBuildFCmp(ctx->builder, LLVMRealUNE, cond, LLVMConstNull(cond_ty), "cond");
            }
            LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);
        } else {
            LLVMBuildBr(ctx->builder, body_bb);
        }

        LLVMBasicBlockRef old_cond = ctx->loop_cond_bb;
        LLVMBasicBlockRef old_end  = ctx->loop_end_bb;
        size_t old_loop_defer      = ctx->loop_defer_count;

        ctx->loop_cond_bb = post_bb;
        ctx->loop_end_bb  = end_bb;
        ctx->loop_defer_count = ctx->deferred_actions->count;

        LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
        codegen_expr(ctx, fst->body);
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
            LLVMBuildBr(ctx->builder, post_bb);

        LLVMPositionBuilderAtEnd(ctx->builder, post_bb);
        if (fst->post) codegen_expr(ctx, fst->post);
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
            LLVMBuildBr(ctx->builder, cond_bb);

        ctx->loop_cond_bb = old_cond;
        ctx->loop_end_bb  = old_end;
        ctx->loop_defer_count = old_loop_defer;

        LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
        CodegenMap *old = ctx->locals;
        ctx->locals = old->parent;
        codegen_map_destroy(old);

        return NULL;
    }

    if (expr->node_type == AST_BREAK_STATEMENT) {
        if (ctx->loop_end_bb) {
            for (int i = (int)ctx->deferred_actions->count - 1; i >= (int)ctx->loop_defer_count; i--) {
                AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
                codegen_expr_stmt(ctx, body);
            }
            LLVMBuildBr(ctx->builder, ctx->loop_end_bb);
        }
        return NULL;
    }

    if (expr->node_type == AST_CONTINUE_STATEMENT) {
        if (ctx->loop_cond_bb) {
            for (int i = (int)ctx->deferred_actions->count - 1; i >= (int)ctx->loop_defer_count; i--) {
                AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
                codegen_expr_stmt(ctx, body);
            }
            LLVMBuildBr(ctx->builder, ctx->loop_cond_bb);
        }
        return NULL;
    }

    return NULL;
}