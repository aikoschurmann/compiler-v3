#include "codegen_internal.h"

LLVMValueRef codegen_expr_ops(CodegenContext *ctx, AstNode *expr) {
    if (expr->node_type == AST_CAST) {
        AstCastExpr *cast_node = &expr->data.cast_expr;
        LLVMValueRef val    = codegen_expr(ctx, cast_node->expr);
        LLVMTypeRef  dst_ty = get_llvm_type(ctx, cast_node->target_type);
        if (!val || !dst_ty) return val;

        LLVMTypeRef  src_ty = LLVMTypeOf(val);
        LLVMTypeKind src_k  = LLVMGetTypeKind(src_ty);
        LLVMTypeKind dst_k  = LLVMGetTypeKind(dst_ty);

        if (src_k == dst_k) {
            if (src_k == LLVMIntegerTypeKind) {
                unsigned src_w = LLVMGetIntTypeWidth(src_ty);
                unsigned dst_w = LLVMGetIntTypeWidth(dst_ty);
                if (src_w == dst_w) return val;
                if (src_w > dst_w)  return LLVMBuildTrunc(ctx->builder, val, dst_ty, "trunc");
                return LLVMBuildSExt(ctx->builder, val, dst_ty, "sext");
            }
        } else {
            if (src_k == LLVMPointerTypeKind && dst_k == LLVMIntegerTypeKind)
                return LLVMBuildPtrToInt(ctx->builder, val, dst_ty, "ptrtoint");
            if (src_k == LLVMIntegerTypeKind && dst_k == LLVMPointerTypeKind)
                return LLVMBuildIntToPtr(ctx->builder, val, dst_ty, "inttoptr");
            if (src_k == LLVMIntegerTypeKind &&
                (dst_k == LLVMFloatTypeKind || dst_k == LLVMDoubleTypeKind))
                return LLVMBuildSIToFP(ctx->builder, val, dst_ty, "sitofp");
            if ((src_k == LLVMFloatTypeKind || src_k == LLVMDoubleTypeKind) &&
                dst_k == LLVMIntegerTypeKind)
                return LLVMBuildFPToSI(ctx->builder, val, dst_ty, "fptosi");
        }
        return LLVMBuildBitCast(ctx->builder, val, dst_ty, "bitcast");
    }

    if (expr->node_type == AST_BINARY_EXPR) {
        LLVMValueRef L = codegen_expr(ctx, expr->data.binary_expr.left);
        LLVMValueRef R = codegen_expr(ctx, expr->data.binary_expr.right);
        if (!L || !R) return NULL;

        Type *ltype    = expr->data.binary_expr.left->type;
        int   is_float = (ltype && ltype->kind == TYPE_PRIMITIVE &&
                          (ltype->as.primitive == PRIM_F32 ||
                           ltype->as.primitive == PRIM_F64));

        switch (expr->data.binary_expr.op) {
            case OP_ADD:  return is_float ? LLVMBuildFAdd(ctx->builder, L, R, "addtmp") : LLVMBuildAdd(ctx->builder, L, R, "addtmp");
            case OP_SUB:  return is_float ? LLVMBuildFSub(ctx->builder, L, R, "subtmp") : LLVMBuildSub(ctx->builder, L, R, "subtmp");
            case OP_MUL:  return is_float ? LLVMBuildFMul(ctx->builder, L, R, "multmp") : LLVMBuildMul(ctx->builder, L, R, "multmp");
            case OP_DIV:  return is_float ? LLVMBuildFDiv(ctx->builder, L, R, "divtmp") : LLVMBuildSDiv(ctx->builder, L, R, "divtmp");
            case OP_MOD:  return is_float ? LLVMBuildFRem(ctx->builder, L, R, "modtmp") : LLVMBuildSRem(ctx->builder, L, R, "modtmp");
            case OP_EQ:   return is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOEQ, L, R, "eqtmp")  : LLVMBuildICmp(ctx->builder, LLVMIntEQ,  L, R, "eqtmp");
            case OP_NEQ:  return is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealONE, L, R, "neqtmp") : LLVMBuildICmp(ctx->builder, LLVMIntNE,  L, R, "neqtmp");
            case OP_LT:   return is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOLT, L, R, "lttmp") : LLVMBuildICmp(ctx->builder, LLVMIntSLT, L, R, "lttmp");
            case OP_GT:   return is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOGT, L, R, "gttmp") : LLVMBuildICmp(ctx->builder, LLVMIntSGT, L, R, "gttmp");
            case OP_LE:   return is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOLE, L, R, "letmp") : LLVMBuildICmp(ctx->builder, LLVMIntSLE, L, R, "letmp");
            case OP_GE:   return is_float ? LLVMBuildFCmp(ctx->builder, LLVMRealOGE, L, R, "getmp") : LLVMBuildICmp(ctx->builder, LLVMIntSGE, L, R, "getmp");
            case OP_AND:  return LLVMBuildAnd(ctx->builder, L, R, "andtmp");
            case OP_OR:   return LLVMBuildOr(ctx->builder, L, R, "ortmp");
            default: {
                LLVMTypeRef ty = get_llvm_type(ctx, expr->type);
                if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind) return LLVMConstNull(ty);
                return NULL;
            }
        }
    }

    if (expr->node_type == AST_ASSIGNMENT_EXPR) {
        AstAssignmentExpr *assign = &expr->data.assignment_expr;
        LLVMValueRef ptr  = codegen_lvalue(ctx, assign->lvalue);
        LLVMValueRef rval = codegen_expr(ctx, assign->rvalue);
        if (!ptr || !rval) return NULL;

        if (assign->op == OP_ASSIGN) {
            LLVMBuildStore(ctx->builder, rval, ptr);
            return rval;
        }

        LLVMTypeRef  ty   = get_llvm_type(ctx, assign->lvalue->type);
        LLVMValueRef lval = LLVMBuildLoad2(ctx->builder, ty, ptr, "loadtmp");
        LLVMValueRef res  = NULL;

        Type *ltype    = assign->lvalue->type;
        int   is_float = (ltype && ltype->kind == TYPE_PRIMITIVE &&
                          (ltype->as.primitive == PRIM_F32 ||
                           ltype->as.primitive == PRIM_F64));

        switch (assign->op) {
            case OP_PLUS_EQ:  res = is_float ? LLVMBuildFAdd(ctx->builder, lval, rval, "addtmp") : LLVMBuildAdd(ctx->builder, lval, rval, "addtmp"); break;
            case OP_MINUS_EQ: res = is_float ? LLVMBuildFSub(ctx->builder, lval, rval, "subtmp") : LLVMBuildSub(ctx->builder, lval, rval, "subtmp"); break;
            case OP_MUL_EQ:   res = is_float ? LLVMBuildFMul(ctx->builder, lval, rval, "multmp") : LLVMBuildMul(ctx->builder, lval, rval, "multmp"); break;
            case OP_DIV_EQ:   res = is_float ? LLVMBuildFDiv(ctx->builder, lval, rval, "divtmp") : LLVMBuildSDiv(ctx->builder, lval, rval, "divtmp"); break;
            case OP_MOD_EQ:   res = is_float ? LLVMBuildFRem(ctx->builder, lval, rval, "modtmp") : LLVMBuildSRem(ctx->builder, lval, rval, "modtmp"); break;
            default:           res = rval; break;
        }
        if (res) LLVMBuildStore(ctx->builder, res, ptr);
        return res;
    }

    if (expr->node_type == AST_UNARY_EXPR) {
        AstUnaryExpr *ue = &expr->data.unary_expr;

        if (ue->op == OP_ADRESS) {
            return codegen_lvalue(ctx, ue->expr);
        } else if (ue->op == OP_DEREF) {
            LLVMValueRef ptr = codegen_expr(ctx, ue->expr);
            return LLVMBuildLoad2(ctx->builder, get_llvm_type(ctx, expr->type), ptr, "loadtmp");
        } else if (ue->op == OP_SUB) {
            LLVMValueRef val = codegen_expr(ctx, ue->expr);
            LLVMTypeRef  ty  = LLVMTypeOf(val);
            if (LLVMGetTypeKind(ty) == LLVMIntegerTypeKind)
                return LLVMBuildNeg(ctx->builder, val, "negtmp");
            return LLVMBuildFNeg(ctx->builder, val, "fnegtmp");
        } else if (ue->op == OP_NOT) {
            LLVMValueRef val = codegen_expr(ctx, ue->expr);
            return LLVMBuildNot(ctx->builder, val, "nottmp");
        } else if (ue->op == OP_POST_INC || ue->op == OP_POST_DEC ||
                   ue->op == OP_PRE_INC  || ue->op == OP_PRE_DEC) {
            LLVMValueRef ptr = codegen_lvalue(ctx, ue->expr);
            LLVMTypeRef  ty  = get_llvm_type(ctx, ue->expr->type);
            if (LLVMGetTypeKind(ty) == LLVMVoidTypeKind) return NULL;

            LLVMValueRef val     = LLVMBuildLoad2(ctx->builder, ty, ptr, "loadtmp");
            LLVMValueRef new_val = NULL;
            int is_float = (LLVMGetTypeKind(ty) == LLVMFloatTypeKind ||
                            LLVMGetTypeKind(ty) == LLVMDoubleTypeKind);

            if (!is_float) {
                if (ue->op == OP_POST_INC || ue->op == OP_PRE_INC)
                    new_val = LLVMBuildAdd(ctx->builder, val, LLVMConstInt(ty, 1, 0), "inc");
                else
                    new_val = LLVMBuildSub(ctx->builder, val, LLVMConstInt(ty, 1, 0), "dec");
            } else {
                if (ue->op == OP_POST_INC || ue->op == OP_PRE_INC)
                    new_val = LLVMBuildFAdd(ctx->builder, val, LLVMConstReal(ty, 1.0), "inc");
                else
                    new_val = LLVMBuildFSub(ctx->builder, val, LLVMConstReal(ty, 1.0), "dec");
            }
            if (new_val) LLVMBuildStore(ctx->builder, new_val, ptr);
            return (ue->op == OP_POST_INC || ue->op == OP_POST_DEC) ? val : new_val;
        }
    }

    return NULL;
}
