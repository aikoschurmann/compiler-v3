#include "type_report.h"
#include "type_print.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

#define COL_RESET   "\033[0m"
#define COL_RED     "\033[1;31m"
#define COL_GREEN   "\033[1;32m"
#define COL_YELLOW  "\033[1;33m"
#define COL_BLUE    "\033[1;34m"
#define COL_MAGENTA "\033[1;35m"
#define COL_CYAN    "\033[1;36m"
#define COL_WHITE   "\033[1;37m"
#define COL_BOLD    "\033[1m"
#define COL_DIM     "\033[2m"

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
    fprintf(stderr, "%s%s:%zu:%zu: %serror:%s ", 
        COL_BOLD, 
        err->filename ? err->filename : "<input>", 
        err->span.start_line, err->span.start_col, 
        COL_RED, COL_RESET);

    // 2. Message based on Kind
    switch (err->kind) {
        case TE_UNKNOWN_TYPE:
            fprintf(stderr, "Unknown type '%s%s%s'.\n", 
                COL_YELLOW, err->as.name.name, COL_RESET);
            break;
        case TE_REDECLARATION:
            fprintf(stderr, "Redefinition of symbol '%s%s%s'.\n", 
                COL_YELLOW, err->as.name.name, COL_RESET);
            break;
        case TE_UNDECLARED:
            fprintf(stderr, "Use of undeclared identifier '%s%s%s'.\n", 
                COL_YELLOW, err->as.name.name, COL_RESET);
            break;
        case TE_TYPE_MISMATCH:
            fprintf(stderr, "Type mismatch expected: ");
            type_print(stderr, err->as.mismatch.expected);
            fprintf(stderr, " but found: ");
            type_print(stderr, err->as.mismatch.actual);
            fprintf(stderr, "\n");
            break;
        case TE_RETURN_MISMATCH:
            fprintf(stderr, "Function return type mismatch expected: ");
            type_print(stderr, err->as.mismatch.expected);
            fprintf(stderr, " but found: ");
            type_print(stderr, err->as.mismatch.actual);
            fprintf(stderr, "\n");
            break;
        case TE_VARIABLE_TYPE_RESOLUTION_FAILED:
            fprintf(stderr, "Failed to resolve type for variable '%s%s%s'.\n",
                COL_YELLOW, err->as.name.name, COL_RESET);
            break;
        case TE_BINOP_MISMATCH:
            fprintf(stderr, "Invalid operands for binary operator '%s%s%s'. Left: ", 
                COL_MAGENTA, op_kind_to_str(err->as.binop.op), COL_RESET);
            type_print(stderr, err->as.binop.left);
            fprintf(stderr, " Right: ");
            type_print(stderr, err->as.binop.right);
            fprintf(stderr, "\n");
            break;
        case TE_UNOP_MISMATCH:
            fprintf(stderr, "Invalid operand for unary operator '%s%s%s'. Operand: ", 
                COL_MAGENTA, op_kind_to_str(err->as.unop.op), COL_RESET);
            type_print(stderr, err->as.unop.operand);
            fprintf(stderr, "\n");
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
                COL_YELLOW, err->as.name.name, COL_RESET);
            break;
        case TE_CONST_ASSIGN:
             fprintf(stderr, "Cannot assign to immutable variable/parameter.\n");
             break;
        case TE_ARG_COUNT_MISMATCH:
             fprintf(stderr, "Argument count mismatch. Expected %zu, found %zu.\n", 
                err->as.arg_count.expected, err->as.arg_count.actual);
             break;
        default:
            fprintf(stderr, "Unknown Semantic Error.\n");
            break;
    }

    // 3. Source Context
    if (err->filename && err->span.start_line > 0) {
        if (err->span.start_line == err->span.end_line && err->span.end_col > err->span.start_col) {
            print_source_excerpt_span(err->filename, err->span.start_line, err->span.start_col, err->span.end_col);
        } else {
            print_source_excerpt(err->filename, err->span.start_line, err->span.start_col);
        }
    }
}

