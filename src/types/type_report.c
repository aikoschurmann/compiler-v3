#include <stdio.h>
#include <stdbool.h>
#include "type_report.h"
#include "dense_arena_interner.h"
#include "dynamic_array.h"
#include "utils.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

/*
 * Refactored, consistent, and slightly safer pretty-printer for
 * the type interner and function symbol/type mapping.
 *
 * Improvements made:
 *  - Extracted small helper functions to remove repetition and make
 *    formatting consistent.
 *  - Use intern_peek when possible to avoid mutating the interner while
 *    printing. (Only peek; do not intern new entries during reporting.)
 *  - Consistent bulleting, alignment and fallbacks when data is missing.
 *  - Fewer casts sprinkled around; clearer intent comments.
 *
 * Notes: this keeps the original signature so you can drop it in place.
 */

static void print_header(void) {
    printf("\n" BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf(BOLD "                    TYPE INTERNMENT ANALYSIS" RESET "\n");
    printf(BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
}

static void print_interned_type_line(int index, Type *type) {
    printf("  " YELLOW "[%d]" RESET " ", index);
    print_type_signature(type, 0);
    printf(" ");
    print_type_category_colored(type);
    printf("\n");
}

static const char *safe_symbol_name(InternResult *name_rec) {
    if (!name_rec || !name_rec->key) return "(unknown)";
    return (const char *)((Slice *)name_rec->key)->ptr;
}

static void print_symbol_info(AstNode *func_decl) {
    InternResult *name_rec = func_decl->data.function_declaration.name_rec;
    const char *func_name = safe_symbol_name(name_rec);

    printf("\n  " CYAN "%s" RESET ":\n", func_name);

    if (name_rec) {
        printf("    • Symbol ptr: " DIM "%p" RESET "\n", (void *)name_rec);
        if (name_rec->entry) {
            printf("    • Symbol Name Dense Index: " GREEN "[%d]" RESET "\n",
                   name_rec->entry->dense_index);
        } else {
            printf("    • Symbol Name Dense Index: " RED "none" RESET "\n");
        }
    } else {
        printf("    • Symbol record: " RED "none" RESET "\n");
    }
}

static void print_function_type_info(TypeChecker *tc, AstNode *func_decl) {
    if (!func_decl->type) {
        printf("    • Type: " RED "none" RESET "\n");
        return;
    }

    /* Peek — do not intern new entries while printing */
    Slice slice = { .ptr = (const char *)func_decl->type, .len = sizeof(Type) };
    InternResult *result = intern_peek(tc->type_interner, &slice);
    int dense_index = result ? result->entry->dense_index : -1;

    printf("    • Type Index: " YELLOW "[%d] " RESET , dense_index);
    print_type_signature(func_decl->type, 0);
    printf(" ");
    print_type_category_colored(func_decl->type);
    printf("\n");

    if (func_decl->type->kind != TY_FUNC) return;

    size_t param_count = func_decl->type->u.func.param_count;
    printf("    • Parameters (%zu):\n", param_count);

    for (size_t p = 0; p < param_count; p++) {
        Type *param_type = func_decl->type->u.func.params[p];
        Slice param_slice = { .ptr = (const char *)param_type, .len = sizeof(Type) };
        InternResult *param_result = intern_peek(tc->type_interner, &param_slice);
        int param_dense_index = param_result ? param_result->entry->dense_index : -1;

        printf("       " YELLOW "[%d] " RESET, param_dense_index);
        print_type_signature(param_type, 0);
        printf(" ");
        print_type_category_colored(param_type);
        printf("\n");
    }

    Type *return_type = func_decl->type->u.func.ret;
    if (return_type) {
        Slice return_slice = { .ptr = (const char *)return_type, .len = sizeof(Type) };
        InternResult *return_result = intern_peek(tc->type_interner, &return_slice);
        int return_dense_index = return_result ? return_result->entry->dense_index : -1;

        printf("    • Return Type: " YELLOW "[%d]" RESET " → ", return_dense_index);
        print_type_signature(return_type, 0);
        printf(" ");
        print_type_category_colored(return_type);
        printf("\n");
    } else {
        printf("    • Return Type: " RED "none" RESET "\n");
    }
}

void print_clean_type_internment_results(TypeChecker *tc, AstNode *program) {
    if (!tc || !tc->type_interner) return; /* nothing to show */

    print_header();

    printf("Total types interned: " YELLOW "%d" RESET "\n",
           tc->type_interner->dense_index_count);

    /* Interned types list */
    printf("\n" BOLD "Interned Types:" RESET "\n");

    int count = tc->type_interner->dense_index_count;
    if (count <= 0) {
        printf(" " DIM "(none)" RESET "\n");
    } else {
        for (int i = 0; i < count; i++) {
            InternResult **result_ptr = (InternResult **)dynarray_get(tc->type_interner->dense_array, i);
            if (!result_ptr || !*result_ptr) continue;
            InternResult *result = *result_ptr;
            Slice *key_slice = (Slice *)result->key;
            if (!key_slice || !key_slice->ptr) continue;
            Type *type = (Type *)key_slice->ptr;
            print_interned_type_line(i, type);
        }
    }

    /* Function symbol mapping */
    if (!program || !program->data.program.decls || program->data.program.decls->count == 0) {
        printf("\n" DIM "No function declarations found." RESET "\n");
        return;
    }

    printf("\n" BOLD "Function Symbol Mapping:" RESET "\n");

    size_t func_count = program->data.program.decls->count;
    for (size_t i = 0; i < func_count; i++) {
        AstNode *func_decl = *(AstNode **)dynarray_get(program->data.program.decls, i);
        if (!func_decl || func_decl->node_type != AST_FUNCTION_DECLARATION) continue;

        print_symbol_info(func_decl);
        print_function_type_info(tc, func_decl);
    }

    printf("\n");
}
