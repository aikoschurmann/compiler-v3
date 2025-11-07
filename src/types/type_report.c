#include <stdio.h>
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

void print_clean_type_internment_results(TypeChecker *tc, AstNode *program) {
    printf("\n" BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf(BOLD "                    TYPE INTERNMENT ANALYSIS" RESET "\n");
    printf(BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf("Total types interned: " YELLOW "%d" RESET "\n", tc->type_interner->dense_index_count);

    printf("\n" BOLD "Interned Types:" RESET "\n");
    for (int i = 0; i < tc->type_interner->dense_index_count; i++) {
        InternResult **result_ptr = (InternResult**)dynarray_get(tc->type_interner->dense_array, i);
        if (result_ptr && *result_ptr) {
            InternResult *result = *result_ptr;
            Slice *key_slice = (Slice*)result->key;
            Type *type = (Type*)key_slice->ptr;

            printf("  " YELLOW "[%d]" RESET " ", i);
            print_type_signature(type, 0);
            printf(" ");
            print_type_category_colored(type);
            printf("\n");
        }
    }

    if (!program || !program->data.program.decls) {
        printf("\n" DIM "No function declarations found." RESET "\n");
        return;
    }

    printf("\n" BOLD "Function Symbol Mapping:" RESET "\n");
    size_t func_count = program->data.program.decls->count;

    for (size_t i = 0; i < func_count; i++) {
        AstNode *func_decl = *(AstNode**)dynarray_get(program->data.program.decls, i);
        if (!func_decl || func_decl->node_type != AST_FUNCTION_DECLARATION) continue;

        const char *func_name = "(unknown)";
        if (func_decl->data.function_declaration.name_rec && 
            func_decl->data.function_declaration.name_rec->key) {
            func_name = (const char*)((Slice*)func_decl->data.function_declaration.name_rec->key)->ptr;
        }

        printf("\n  " CYAN "%s" RESET ":\n", func_name);

        if (func_decl->data.function_declaration.name_rec) {
            printf("    • Symbol ptr: " DIM "%p" RESET "\n", (void*)func_decl->data.function_declaration.name_rec);
            if (func_decl->data.function_declaration.name_rec->entry) {
                printf("    • Symbol Name Dense Index: " GREEN "[%d]" RESET "\n", 
                       func_decl->data.function_declaration.name_rec->entry->dense_index);
            } else {
                printf("    • Symbol Name Dense Index: " RED "none" RESET "\n");
            }
        }

        if (func_decl->type) {
            Slice slice = { .ptr = (const char*)func_decl->type, .len = sizeof(Type) };
            InternResult *result = intern_peek(tc->type_interner, &slice);
            int dense_index = result ? result->entry->dense_index : -1;

            printf("    • Type Index: " YELLOW "[%d]" RESET " → ", dense_index);
            print_type_signature(func_decl->type, 0);
            printf(" ");
            print_type_category_colored(func_decl->type);
            printf("\n");

            if (func_decl->type->kind == TY_FUNC) {
                printf("    • Parameters (%zu):\n", func_decl->type->u.func.param_count);

                for (size_t p = 0; p < func_decl->type->u.func.param_count; p++) {
                    Type *param_type = func_decl->type->u.func.params[p];
                    Slice param_slice = { .ptr = (const char*)param_type, .len = sizeof(Type) };
                    InternResult *param_result = intern(tc->type_interner, &param_slice, NULL);
                    int param_dense_index = param_result ? param_result->entry->dense_index : -1;

                    printf("      [%zu] ", p);
                    print_type_signature(param_type, 0);
                    printf(" " YELLOW "[%d]" RESET " ", param_dense_index);
                    print_type_category_colored(param_type);
                    printf("\n");
                }
                Type *return_type = func_decl->type->u.func.ret;
                if (return_type) {
                    Slice return_slice = { .ptr = (const char*)return_type, .len = sizeof(Type) };
                    InternResult *return_result = intern(tc->type_interner, &return_slice, NULL);
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
        } else {
            printf("    • Type: " RED "none" RESET "\n");
        }
    }
    printf("\n");
}
