#include "codegen_internal.h"
#include "dynamic_array.h"

typedef struct {
    AstNode *body;
    LLVMBasicBlockRef bb;
} DeferInfo;

static LLVMValueRef coerce_to_bool(CodegenContext *ctx, LLVMValueRef val) {
    LLVMTypeRef ty = LLVMTypeOf(val);
    LLVMTypeKind kind = LLVMGetTypeKind(ty);

    if (kind == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(ty) == 1) {
        return val;
    }

    if (kind == LLVMPointerTypeKind) {
        return LLVMBuildICmp(ctx->builder, LLVMIntNE, val, LLVMConstNull(ty), "cond");
    } else if (kind == LLVMIntegerTypeKind) {
        return LLVMBuildICmp(ctx->builder, LLVMIntNE, val, LLVMConstInt(ty, 0, 0), "cond");
    } else if (kind == LLVMFloatTypeKind || kind == LLVMDoubleTypeKind) {
        return LLVMBuildFCmp(ctx->builder, LLVMRealUNE, val, LLVMConstNull(ty), "cond");
    }

    return val;
}

void codegen_statement(CodegenContext *ctx, AstNode *stmt) {
    if (!stmt) return;
    
    LLVMBasicBlockRef current_block = LLVMGetInsertBlock(ctx->builder);
    if (current_block && LLVMGetBasicBlockTerminator(current_block)) {
        return;
    }
    
    if (!stmt->type) {
        switch (stmt->node_type) {
            case AST_BLOCK:
            case AST_IF_STATEMENT:
            case AST_WHILE_STATEMENT:
            case AST_FOR_STATEMENT:
            case AST_RETURN_STATEMENT:
            case AST_BREAK_STATEMENT:
            case AST_CONTINUE_STATEMENT:
            case AST_DEFER_STATEMENT:
            case AST_EXPR_STATEMENT:
                break; // These are permitted to be untyped
            default:
                ICE_AT(stmt, "Statement node type %d missing type annotation.", stmt->node_type);
        }
    }

    switch (stmt->node_type) {
        case AST_BLOCK: {
            DynArray *stmts = stmt->data.block.statements;
            ctx->locals = codegen_map_create(ctx, ctx->locals);
            
            size_t previous_defer_count = ctx->deferred_actions->count;
            LLVMBasicBlockRef prev_cleanup = ctx->current_cleanup_bb;

            for (size_t i = 0; i < stmts->count; i++) {
                AstNode *s = *(AstNode**)dynarray_get(stmts, i);
                codegen_statement(ctx, s);
            }

            size_t current_defer_count = ctx->deferred_actions->count;

            if (current_defer_count > previous_defer_count) {
                LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
                LLVMBasicBlockRef after_cleanup_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "after_cleanup");

                current_block = LLVMGetInsertBlock(ctx->builder);
                if (current_block && !LLVMGetBasicBlockTerminator(current_block)) {
                    LLVMBuildStore(ctx->builder, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 3, 0), ctx->exit_dest_var);
                    LLVMBuildBr(ctx->builder, ctx->current_cleanup_bb);
                }

                for (int i = (int)current_defer_count - 1; i >= (int)previous_defer_count; i--) {
                    DeferInfo *info = *(DeferInfo**)dynarray_get(ctx->deferred_actions, i);
                    LLVMPositionBuilderAtEnd(ctx->builder, info->bb);

                    LLVMBasicBlockRef target_next = (i == (int)previous_defer_count) 
                                                  ? after_cleanup_bb 
                                                  : (*(DeferInfo**)dynarray_get(ctx->deferred_actions, i - 1))->bb;
                    
                    ctx->current_cleanup_bb = target_next;
                    codegen_statement(ctx, info->body);

                    LLVMBasicBlockRef curr_clean = LLVMGetInsertBlock(ctx->builder);
                    if (curr_clean && !LLVMGetBasicBlockTerminator(curr_clean)) {
                        LLVMBuildBr(ctx->builder, ctx->current_cleanup_bb);
                    }
                }

                LLVMPositionBuilderAtEnd(ctx->builder, after_cleanup_bb);
                LLVMValueRef dest = LLVMBuildLoad2(ctx->builder, LLVMInt32TypeInContext(ctx->context), ctx->exit_dest_var, "dest");
                LLVMBasicBlockRef natural_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "natural");
                LLVMValueRef sw = LLVMBuildSwitch(ctx->builder, dest, natural_bb, 3);

                if (prev_cleanup) {
                    LLVMAddCase(sw, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0), prev_cleanup);
                } else {
                    LLVMBasicBlockRef ret_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "ret");
                    LLVMAddCase(sw, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0), ret_bb);
                    LLVMPositionBuilderAtEnd(ctx->builder, ret_bb);

                    bool sret = type_is_indirect(ctx, ctx->current_func_type->as.func.return_type);
                    if (sret) {
                        LLVMBuildRetVoid(ctx->builder);
                    } else if (ctx->ret_val_var) {
                        LLVMValueRef final_ret = codegen_load_value(ctx, ctx->ret_val_var, ctx->current_func_type->as.func.return_type);
                        LLVMBuildRet(ctx->builder, final_ret);
                    } else {
                        LLVMBuildRetVoid(ctx->builder);
                    }
                }

                if (ctx->loop_end_bb) {
                    LLVMBasicBlockRef next_bb = prev_cleanup ? prev_cleanup : ctx->loop_end_bb;
                    LLVMAddCase(sw, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 1, 0), next_bb);
                }

                if (ctx->loop_cond_bb) {
                    LLVMBasicBlockRef next_bb = prev_cleanup ? prev_cleanup : ctx->loop_cond_bb;
                    LLVMAddCase(sw, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 2, 0), next_bb);
                }

                LLVMPositionBuilderAtEnd(ctx->builder, natural_bb);
                
                // Cleanup allocated DeferInfos for this block
                for (size_t i = previous_defer_count; i < current_defer_count; i++) {
                    free(*(DeferInfo**)dynarray_get(ctx->deferred_actions, i));
                }
                ctx->deferred_actions->count = previous_defer_count;

            } else {
                // No defers, just continue
            }

            ctx->current_cleanup_bb = prev_cleanup;
            CodegenMap *old = ctx->locals;
            ctx->locals = old->parent;
            codegen_map_destroy(old);
            break;
        }

        case AST_IF_STATEMENT: {
            AstIfStatement *ifs  = &stmt->data.if_statement;
            LLVMValueRef    cond = coerce_to_bool(ctx, codegen_expr(ctx, ifs->condition));

            LLVMValueRef     func     = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));
            LLVMBasicBlockRef then_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "then");
            LLVMBasicBlockRef else_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "else");
            LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "merge");

            LLVMBuildCondBr(ctx->builder, cond, then_bb, else_bb);

            LLVMPositionBuilderAtEnd(ctx->builder, then_bb);
            codegen_statement(ctx, ifs->then_branch);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, merge_bb);

            LLVMPositionBuilderAtEnd(ctx->builder, else_bb);
            if (ifs->else_branch) codegen_statement(ctx, ifs->else_branch);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, merge_bb);

            LLVMPositionBuilderAtEnd(ctx->builder, merge_bb);
            break;
        }

        case AST_WHILE_STATEMENT: {
            AstWhileStatement *whl = &stmt->data.while_statement;
            LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));

            LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.cond");
            LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "while.body");
            LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "while.end");

            LLVMBuildBr(ctx->builder, cond_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);

            LLVMValueRef cond = coerce_to_bool(ctx, codegen_expr(ctx, whl->condition));
            LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);

            LLVMBasicBlockRef old_cond = ctx->loop_cond_bb;
            LLVMBasicBlockRef old_end  = ctx->loop_end_bb;

            ctx->loop_cond_bb = cond_bb;
            ctx->loop_end_bb  = end_bb;

            LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
            codegen_statement(ctx, whl->body);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, cond_bb);

            ctx->loop_cond_bb = old_cond;
            ctx->loop_end_bb  = old_end;

            LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
            break;
        }

        case AST_FOR_STATEMENT: {
            AstForStatement *fst  = &stmt->data.for_statement;
            LLVMValueRef     func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder));

            ctx->locals = codegen_map_create(ctx, ctx->locals);
            if (fst->init) codegen_statement(ctx, fst->init);

            LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.cond");
            LLVMBasicBlockRef body_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.body");
            LLVMBasicBlockRef post_bb = LLVMAppendBasicBlockInContext(ctx->context, func, "for.post");
            LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlockInContext(ctx->context, func, "for.end");

            LLVMBuildBr(ctx->builder, cond_bb);
            LLVMPositionBuilderAtEnd(ctx->builder, cond_bb);

            if (fst->condition) {
                LLVMValueRef cond = coerce_to_bool(ctx, codegen_expr(ctx, fst->condition));
                LLVMBuildCondBr(ctx->builder, cond, body_bb, end_bb);
            } else {
                LLVMBuildBr(ctx->builder, body_bb);
            }

            LLVMBasicBlockRef old_cond = ctx->loop_cond_bb;
            LLVMBasicBlockRef old_end  = ctx->loop_end_bb;

            ctx->loop_cond_bb = post_bb;
            ctx->loop_end_bb  = end_bb;

            LLVMPositionBuilderAtEnd(ctx->builder, body_bb);
            codegen_statement(ctx, fst->body);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, post_bb);

            LLVMPositionBuilderAtEnd(ctx->builder, post_bb);
            if (fst->post) codegen_expr(ctx, fst->post);
            if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->builder)))
                LLVMBuildBr(ctx->builder, cond_bb);

            ctx->loop_cond_bb = old_cond;
            ctx->loop_end_bb  = old_end;

            LLVMPositionBuilderAtEnd(ctx->builder, end_bb);
            CodegenMap *old = ctx->locals;
            ctx->locals = old->parent;
            codegen_map_destroy(old);
            break;
        }

        case AST_RETURN_STATEMENT: {
            Type *fn_type = ctx->current_func_type;
            if (!fn_type) ICE("Return statement outside of function context.");
            
            LLVMValueRef retval = NULL;
            if (stmt->data.return_statement.expression) {
                retval = codegen_expr(ctx, stmt->data.return_statement.expression);
                if (!retval) {
                    LLVMTypeRef ty = get_llvm_type(ctx, stmt->data.return_statement.expression->type);
                    if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind)
                        retval = LLVMConstNull(ty);
                }
            }

            bool sret = type_is_indirect(ctx, fn_type->as.func.return_type);
            if (sret) {
                if (retval) LLVMBuildStore(ctx->builder, retval, ctx->sret_ptr);
            } else if (retval && ctx->ret_val_var) {
                LLVMBuildStore(ctx->builder, retval, ctx->ret_val_var);
            }

            LLVMBuildStore(ctx->builder, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0), ctx->exit_dest_var);

            if (ctx->current_cleanup_bb) {
                LLVMBuildBr(ctx->builder, ctx->current_cleanup_bb);
            } else {
                if (sret) {
                    LLVMBuildRetVoid(ctx->builder);
                } else if (retval) {
                    LLVMBuildRet(ctx->builder, retval);
                } else {
                    LLVMBuildRetVoid(ctx->builder);
                }
            }
            break;
        }

        case AST_BREAK_STATEMENT: {
            if (ctx->loop_end_bb) {
                LLVMBuildStore(ctx->builder, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 1, 0), ctx->exit_dest_var);
                if (ctx->current_cleanup_bb) {
                    LLVMBuildBr(ctx->builder, ctx->current_cleanup_bb);
                } else {
                    LLVMBuildBr(ctx->builder, ctx->loop_end_bb);
                }
            }
            break;
        }

        case AST_CONTINUE_STATEMENT: {
            if (ctx->loop_cond_bb) {
                LLVMBuildStore(ctx->builder, LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 2, 0), ctx->exit_dest_var);
                if (ctx->current_cleanup_bb) {
                    LLVMBuildBr(ctx->builder, ctx->current_cleanup_bb);
                } else {
                    LLVMBuildBr(ctx->builder, ctx->loop_cond_bb);
                }
            }
            break;
        }

        case AST_VARIABLE_DECLARATION: {
            AstVariableDeclaration *vdecl = &stmt->data.variable_declaration;
            if (!stmt->type) ICE_AT(stmt, "Variable declaration missing type.");

            LLVMTypeRef  ty    = get_llvm_type(ctx, stmt->type);
            LLVMValueRef alloca = create_entry_block_alloca(ctx, ty, "var");

            if (vdecl->intern_result) {
                void *key = (void*)(intptr_t)(vdecl->intern_result->entry->dense_index + 1);
                codegen_map_put(ctx->locals, key, alloca);
            }
            if (vdecl->initializer) {
                LLVMValueRef init_val = codegen_expr(ctx, vdecl->initializer);
                if (init_val) LLVMBuildStore(ctx->builder, init_val, alloca);
            }
            break;
        }

        case AST_EXPR_STATEMENT: {
            codegen_expr(ctx, stmt->data.expr_statement.expression);
            break;
        }

        case AST_DEFER_STATEMENT: {
            DeferInfo *info = xmalloc(sizeof(DeferInfo));
            info->body = stmt->data.defer_statement.body;
            info->bb = LLVMAppendBasicBlockInContext(ctx->context, LLVMGetBasicBlockParent(LLVMGetInsertBlock(ctx->builder)), "defer_bb");
            
            dynarray_push_value(ctx->deferred_actions, &info);
            ctx->current_cleanup_bb = info->bb;
            break;
        }

        default:
            ICE_AT(stmt, "Unhandled statement type %d in codegen.", stmt->node_type);
    }
}
