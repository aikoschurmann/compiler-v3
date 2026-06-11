#include "codegen_internal.h"

LLVMValueRef codegen_lvalue(CodegenContext *ctx, AstNode *expr) {
    if (!expr) return NULL;

    if (expr->node_type == AST_IDENTIFIER) {
        AstIdentifier *ident = &expr->data.identifier;
        LLVMValueRef val = NULL;
        if (ident->intern_result) {
            void *key = (void*)(intptr_t)ident->intern_result->entry->dense_index;
            val = codegen_map_get(ctx->locals, key);
            if (!val) val = hashmap_get(ctx->globals, key, ptr_hash, ptr_cmp);
            if (!val) {
                Slice *s = (Slice*)ident->intern_result->key;
                char *alloc_name = strndup(s->ptr, s->len);
                val = LLVMGetNamedFunction(ctx->module, alloc_name);
                free(alloc_name);
            }
        }
        return val;
    }

    if (expr->node_type == AST_SUBSCRIPT_EXPR) {
        AstSubscriptExpr *sub = &expr->data.subscript_expr;
        LLVMValueRef target = NULL;
        Type *target_type = sub->target->type;

        if (target_type && target_type->kind == TYPE_ARRAY) {
            target = codegen_lvalue(ctx, sub->target);
        } else {
            target = codegen_expr(ctx, sub->target);
        }

        LLVMValueRef idx    = codegen_expr(ctx, sub->index);
        if (!target || !idx) return NULL;

        if (target_type && target_type->kind == TYPE_ARRAY && target_type->as.array.size_known) {
            LLVMTypeRef arr_ty = get_llvm_type(ctx, target_type);
            LLVMValueRef indices[] = {
                LLVMConstInt(LLVMInt32TypeInContext(ctx->context), 0, 0),
                idx
            };
            return LLVMBuildGEP2(ctx->builder, arr_ty, target, indices, 2, "arrayidx");
        }

        /* Pointer / unsized-array: single-index GEP over element type. */
        LLVMTypeRef elem_ty = NULL;
        if (target_type && target_type->kind == TYPE_POINTER) {
            elem_ty = get_llvm_type(ctx, target_type->as.ptr.base);
        } else {
            elem_ty = LLVMInt32TypeInContext(ctx->context);
        }
        LLVMValueRef indices[] = { idx };
        return LLVMBuildGEP2(ctx->builder, elem_ty, target, indices, 1, "arrayidx");
    }

    if (expr->node_type == AST_UNARY_EXPR && expr->data.unary_expr.op == OP_DEREF) {
        return codegen_expr(ctx, expr->data.unary_expr.expr);
    }

    return NULL;
}
