#include "type_print.h"
#include "type.h"
#include "ast.h"         // for AstNode
#include "dense_arena_interner.h" 
#include "dynamic_array.h"
#include <string.h>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"

// Detailed Syntax Highlighting
#define COL_PRIM    RESET        // White
#define COL_PTR     "\033[31m"   // Red
#define COL_ARR     "\033[33m"   // Yellow
#define COL_NUM     RESET        // White
#define COL_FUNC    RESET        // White/Default for punctuators
#define COL_STRUCT  RESET        // White
#define COL_KEYWORD RESET        // White
#define COL_INDEX   "\033[33m"   // Yellow for [0], [1]
#define COL_KIND_PRIM "\033[34m" // Blue for (primitive)
#define COL_KIND_PTR  "\033[31m" // Red for (pointer)
#define COL_KIND_ARR  "\033[33m" // Yellow for (array)
#define COL_KIND_FUNC "\033[35m" // Magenta for (function)
#define COL_KIND_OTHER "\033[2m" // Dim for others


static const char* get_primitive_name(PrimitiveKind kind) {
    switch (kind) {
        case PRIM_I8:   return "i8";
        case PRIM_I16:  return "i16";
        case PRIM_I32:  return "i32";
        case PRIM_I64:  return "i64";
        case PRIM_U8:   return "u8";
        case PRIM_U16:  return "u16";
        case PRIM_U32:  return "u32";
        case PRIM_U64:  return "u64";
        case PRIM_F32:  return "f32";
        case PRIM_F64:  return "f64";
        case PRIM_BOOL: return "bool";
        case PRIM_CHAR: return "char";
        case PRIM_VOID: return "void";
        default:        return "unknown_prim";
    }
}

// Recursive implementation
static void type_print_internal(FILE *f, const Type *type) {
    if (!type) { fprintf(f, "null"); return; }

    switch (type->kind) {
        case TYPE_PRIMITIVE:
            fprintf(f, "%s%s" RESET, COL_PRIM, get_primitive_name(type->as.primitive));
            break;

        case TYPE_POINTER:
            type_print_internal(f, type->as.ptr.base);
            fprintf(f, "%s*" RESET, COL_PTR);
            break;

        case TYPE_ARRAY:
            type_print_internal(f, type->as.array.base);
            fprintf(f, "%s[" RESET, COL_ARR);
            if (type->as.array.size_known) {
                fprintf(f, "%s%lld" RESET, COL_NUM, (long long)type->as.array.size);
            }
            fprintf(f, "%s]" RESET, COL_ARR);
            break;
            
        case TYPE_FUNCTION:
            fprintf(f, "%s(" RESET, COL_FUNC);
            for (size_t i = 0; i < type->as.func.param_count; i++) {
                if (i > 0) fprintf(f, ", ");
                type_print_internal(f, type->as.func.params[i]);
            }

            fprintf(f, "%s) -> " RESET, COL_FUNC);
            if (type->as.func.return_type) {
                type_print_internal(f, type->as.func.return_type);
            } else {
                fprintf(f, "err");
            }
            break;

        case TYPE_STRUCT:
             fprintf(f, "%sstruct %s%s" RESET, COL_KEYWORD, COL_STRUCT, type->as.user.name ? type->as.user.name : "anonymous");
             break;
        
        default:
            fprintf(f, "unknown");
            break;
    }
}

void type_print(FILE *f, const Type *type) {
    type_print_internal(f, type);
}

void type_print_signature(const Type *type) {
    type_print_internal(stdout, type);
}

// ----------------------------------------------------------------------------
// Dump Routines
// ----------------------------------------------------------------------------

// Internal helper for usage of "Interned Types" listing
static const char* get_kind_name(const Type *type) {
    if (!type) return "unknown";
    switch (type->kind) {
        case TYPE_PRIMITIVE: return "primitive";
        case TYPE_POINTER:   return "pointer";
        case TYPE_ARRAY:     return "array";
        case TYPE_FUNCTION:  return "function";
        case TYPE_STRUCT:    return "struct";
        default:             return "unknown";
    }
}

// Internal helper for usage of "Interned Types" listing
static const char* get_kind_color(const Type *type) {
    if (!type) return RESET;
    switch (type->kind) {
        case TYPE_PRIMITIVE: return COL_KIND_PRIM;
        case TYPE_POINTER:   return COL_KIND_PTR;
        case TYPE_ARRAY:     return COL_KIND_ARR;
        case TYPE_FUNCTION:  return COL_KIND_FUNC;
        default:             return COL_KIND_OTHER;
    }
}

static void print_header(void) {
    printf("\n" BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf(BOLD "                    TYPE INTERNMENT ANALYSIS" RESET "\n");
    printf(BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
}

static void print_interned_type_line(int index, Type *type) {
    printf("  " COL_INDEX "[%d]" RESET " ", index);
    type_print_internal(stdout, type);
    printf(" %s(%s)" RESET "\n", get_kind_color(type), get_kind_name(type));
}

static const char *safe_symbol_name(InternResult *name_rec) {
    if (!name_rec || !name_rec->key) return "(unknown)";
    return (const char *)((Slice *)name_rec->key)->ptr;
}

static void print_symbol_info(AstNode *func_decl) {
    InternResult *intern_result = func_decl->data.function_declaration.intern_result;
    const char *func_name = safe_symbol_name(intern_result);

    printf("  " COL_STRUCT "%s" RESET ":\n", func_name);

    if (intern_result) {
        printf("    • Symbol ptr: " COL_INDEX "%p" RESET "\n", (void *)intern_result);
        if (intern_result->entry) {
            printf("    • Symbol Name Dense Index: " COL_INDEX "[%d]" RESET "\n",
                   intern_result->entry->dense_index);
        } else {
            printf("    • Symbol Name Dense Index: " COL_PTR "none" RESET "\n");
        }
    } else {
        printf("    • Symbol record: " COL_PTR "none" RESET "\n");
    }
}

static void print_function_type_info(TypeStore *store, AstNode *func_decl) {
    if (!func_decl->type) {
        printf("    • Type: " COL_PTR "none" RESET "\n");
        return;
    }

    /* Peek — do not intern new entries while printing */
    Slice slice = { .ptr = (const char *)func_decl->type, .len = sizeof(Type) };
    InternResult *intern_result = intern_peek(store->type_interner, &slice);
    int dense_index = intern_result && intern_result->entry ? intern_result->entry->dense_index : -1;

    printf("    • Type Index: " COL_INDEX "[%d] " RESET , dense_index);
    type_print_internal(stdout, func_decl->type);
    printf(" %s(%s)" RESET "\n", get_kind_color(func_decl->type), get_kind_name(func_decl->type));

    if (func_decl->type->kind != TYPE_FUNCTION) return;

    size_t param_count = func_decl->type->as.func.param_count;
    printf("    • Parameters (%zu):\n", param_count);

    for (size_t p = 0; p < param_count; p++) {
        Type *param_type = func_decl->type->as.func.params[p];
        Slice param_slice = { .ptr = (const char *)param_type, .len = sizeof(Type) };
        InternResult *param_result = intern_peek(store->type_interner, &param_slice);
        int param_dense_index = param_result && param_result->entry ? param_result->entry->dense_index : -1;

        printf("       " COL_INDEX "[%d] " RESET, param_dense_index);
        type_print_internal(stdout, param_type);
        printf(" %s(%s)" RESET "\n", get_kind_color(param_type), get_kind_name(param_type));
    }

    Type *return_type = func_decl->type->as.func.return_type;
    if (return_type) {
        Slice return_slice = { .ptr = (const char *)return_type, .len = sizeof(Type) };
        InternResult *return_result = intern_peek(store->type_interner, &return_slice);
        int return_dense_index = return_result && return_result->entry ? return_result->entry->dense_index : -1;

        printf("    • Return Type: " COL_INDEX "[%d]" RESET " ", return_dense_index);
        type_print_internal(stdout, return_type);
        printf(" %s(%s)" RESET "\n", get_kind_color(return_type), get_kind_name(return_type));
    } else {
        printf("    • Return Type: " COL_PTR "none" RESET "\n");
    }
}

void type_print_store_dump(TypeStore *store, AstNode *program) {
    if (!store || !store->type_interner) return; /* nothing to show */

    print_header();

    printf("Total types interned: " COL_NUM "%d" RESET "\n",
           store->type_interner->dense_index_count);

    /* Interned types list */
    printf("\n" BOLD "Interned Types:" RESET "\n");

    int count = store->type_interner->dense_index_count;
    if (count <= 0) {
        printf(" " DIM "(none)" RESET "\n");
    } else {
        for (int i = 0; i < count; i++) {
            InternResult **result_ptr = (InternResult **)dynarray_get(store->type_interner->dense_array, i);
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
        print_function_type_info(store, func_decl);
        printf("\n");
    }

    printf("\n");
}
