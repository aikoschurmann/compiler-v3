#include "type_report.h"
#include "type_print.h"
#include <stdio.h>
#include <stdlib.h>

#define COL_RESET   "\033[0m"
#define COL_RED     "\033[1;31m"
#define COL_BOLD    "\033[1m"
#define COL_CYAN    "\033[36m"

static const char* op_kind_to_str(OpKind op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_EQ:  return "==";
        case OP_NEQ: return "!=";
        case OP_LT:  return "<";
        case OP_GT:  return ">";
        case OP_LE:  return "<=";
        case OP_GE:  return ">=";
        case OP_AND: return "&&";
        case OP_OR:  return "||";
        case OP_NOT: return "!";
        case OP_ASSIGN: return "=";
        default: return "?";
    }
}

void print_type_error(TypeError *err) {
    if (!err) return;

    // 1. Header: "file:line:col: Error: ..."
    fprintf(stderr, "%s%s:%zu:%zu: %sError:%s ", 
        COL_BOLD, 
        err->filename ? err->filename : "<input>", 
        err->span.start_line, err->span.start_col, 
        COL_RED, COL_RESET);

    // 2. Message based on Kind
    switch (err->kind) {
        case TE_UNKNOWN_TYPE:
            fprintf(stderr, "Unknown type '%s%s%s'.\n", 
                COL_CYAN, err->as.name.name, COL_RESET);
            break;
            
        case TE_REDECLARATION:
            fprintf(stderr, "Redefinition of symbol '%s%s%s'.\n", 
                COL_CYAN, err->as.name.name, COL_RESET);
            break;
            
        case TE_UNDECLARED:
            fprintf(stderr, "Use of undeclared identifier '%s%s%s'.\n", 
                COL_CYAN, err->as.name.name, COL_RESET);
            break;
            
        case TE_TYPE_MISMATCH:
            fprintf(stderr, "Type mismatch. Expected '");
            type_print(stderr, err->as.mismatch.expected);
            fprintf(stderr, "', found '");
            type_print(stderr, err->as.mismatch.actual);
            fprintf(stderr, "'.\n");
            break;

        case TE_RETURN_MISMATCH:
            fprintf(stderr, "Function return type mismatch. Declared '");
            type_print(stderr, err->as.mismatch.expected);
            fprintf(stderr, "', but body returns '");
            type_print(stderr, err->as.mismatch.actual);
            fprintf(stderr, "'.\n");
            break;

        case TE_BINOP_MISMATCH:
            fprintf(stderr, "Invalid operands for binary operator '%s': '", op_kind_to_str(err->as.binop.op));
            type_print(stderr, err->as.binop.left);
            fprintf(stderr, "' and '");
            type_print(stderr, err->as.binop.right);
            fprintf(stderr, "'.\n");
            break;

        case TE_UNOP_MISMATCH:
            fprintf(stderr, "Invalid operand for unary operator '%s': '", op_kind_to_str(err->as.unop.op));
            type_print(stderr, err->as.unop.operand);
            fprintf(stderr, "'.\n");
            break;

        case TE_NOT_CALLABLE:
            fprintf(stderr, "Expression of type '");
            type_print(stderr, err->as.bad_usage.actual);
            fprintf(stderr, "' is not callable.\n");
            break;

        case TE_NOT_INDEXABLE:
            fprintf(stderr, "Expression of type '");
            type_print(stderr, err->as.bad_usage.actual);
            fprintf(stderr, "' is not indexable (must be array or pointer).\n");
            break;
        
        case TE_FIELD_ACCESS:
            fprintf(stderr, "Type has no field named '%s%s%s'.\n", 
                COL_CYAN, err->as.name.name, COL_RESET);
            break;

        case TE_CONST_ASSIGN:
             fprintf(stderr, "Cannot assign to immutable variable/parameter.\n");
             break;

        default:
            fprintf(stderr, "Unknown Semantic Error.\n");
            break;
    }
}
