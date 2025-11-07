#include "file.h"

#include "type.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>
#include "scope.h"
#include "dense_arena_interner.h"

/* ANSI color codes used for error printing */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

/* Canonical primitive Type* globals (defined here, declared in type.h) */
Type *INT32_TYPE_PTR = NULL;
Type *INT64_TYPE_PTR = NULL;
Type *FLOAT32_TYPE_PTR = NULL;
Type *FLOAT64_TYPE_PTR = NULL;
Type *BOOL_TYPE_PTR = NULL;
Type *CHAR_TYPE_PTR = NULL;
Type *STRING_TYPE_PTR = NULL;

// Hash utility functions
uint64_t hash64(uint64_t x) {
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;
    return x;
}

const char *type_kind_to_string(TypeKind kind) {
    switch (kind) {
        case TY_NAMED: return "Named";
        case TY_PTR: return "Pointer";
        case TY_ARRAY: return "Array";
        case TY_FUNC: return "Function";
        default: return "Unknown";
    }
}

uint64_t hash_combine(uint64_t a, uint64_t b) {
    return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
}

// Forward declarations
void *type_copy_func(Arena *arena, const void *data, size_t len);
uint64_t type_hash(const Type *t);
bool type_equals(const Type *a, const Type *b);

/*
 * Wrapper functions for interner API compatibility.
 * The interner stores keys as Slice* objects, so these wrappers
 * extract the actual Type* from the Slice before calling the 
 * type system's hash and comparison functions.
 */
size_t type_hash_wrapper(void *ptr) {
    // ptr is a Slice*, extract the Type* from it
    Slice *slice = (Slice*)ptr;
    Type *type = (Type*)slice->ptr;
    return (size_t)type_hash((const Type*)type);
}

int type_cmp_wrapper(void *a, void *b) {
    // a and b are Slice*, extract the Type* from them


    Slice *slice_a = (Slice*)a;
    Slice *slice_b = (Slice*)b;
    Type *type_a = (Type*)slice_a->ptr;
    Type *type_b = (Type*)slice_b->ptr;
    return type_equals((const Type*)type_a, (const Type*)type_b) ? 0 : 1;
}

/* Utility: fetch a specific line from file for type error excerpts */
/* Use shared excerpt printing helpers */
#include "file.h"

TypeChecker *typecheck_create(Arena *arena, const char *filename) {
    if (!arena) return NULL;

    TypeChecker *tc = arena_alloc(arena, sizeof(TypeChecker));
    if (!tc) return NULL;

    tc->filename = filename;

    tc->arena = arena;

    // Create interner for type canonicalization
    HashMap *type_map = hashmap_create(64);
    if (!type_map) {
        return NULL;
    }
    tc->type_hashmap = type_map;
    tc->type_interner = intern_table_create(type_map, arena, type_copy_func, type_hash_wrapper, type_cmp_wrapper);
    if (!tc->type_interner) {
        return NULL;
    }

    tc->keyword_offset = TOK_I32 - 1; // -1 because PRIM_NONE is 0 used for mapping from 

    return tc;
}

/*
 * type_copy_func: Deep copy callback for the interner.
 * Creates a canonical copy of a Type in the arena, including
 * deep copying of function parameter arrays.
 */
void *type_copy_func(Arena *arena, const void *data, size_t len) {
    if (!arena || !data || len != sizeof(Type)) return NULL;
    
    const Type *src = (const Type*)data;
    Type *copy = arena_alloc(arena, sizeof(Type));
    if (!copy) return NULL;
    
    // Copy the basic structure
    memcpy(copy, data, sizeof(Type));
    
    // For function types, deep copy the parameter array
    if (src->kind == TY_FUNC && src->u.func.param_count > 0 && src->u.func.params) {
        size_t params_size = sizeof(Type*) * src->u.func.param_count;
        Type **params_copy = arena_alloc(arena, params_size);
        if (!params_copy) return NULL;
        
        // Copy the parameter type pointers
        memcpy(params_copy, src->u.func.params, params_size);
        copy->u.func.params = params_copy;
    }
    
    return (void*)copy;
}

/*
 * intern_type: Canonicalize a Type prototype using the interner.
 * Returns the canonical Type* (pointer owned by the interner/arena).
 * Identical types will return the same canonical pointer.
 */
InternResult *intern_type(TypeChecker *tc, Type *prototype) {
    if (!tc || !prototype) return NULL;

    Slice slice = { .ptr = (const char*)prototype, .len = sizeof(Type) };
    InternResult *result = intern(tc->type_interner, &slice, NULL);
    if (!result) return NULL;

    return result;
}

/* hash helper - structural hash based on content, not pointers */
uint64_t type_hash(const Type *t) {
    if (!t) return 0;
    
    uint64_t h = hash64((uint64_t)t->kind);

    switch (t->kind) {
        case TY_NAMED: {
            /* Use dense_index if available for stable hashing */
            uint64_t id = 0;
            if (t->u.named.name_rec && t->u.named.name_rec->entry) {
                id = (uint64_t)t->u.named.name_rec->entry->dense_index;
            } else if (t->u.named.name_rec) {
                /* Fallback to pointer if no dense index yet */
                id = (uint64_t)(uintptr_t)t->u.named.name_rec;
            }
            h = hash_combine(h, id);
            break;
        }

        case TY_PTR:
            /* Recursively hash the target type's content */
            h = hash_combine(h, type_hash(t->u.ptr.target));
            break;

        case TY_ARRAY:
            /* Recursively hash the element type's content */
            h = hash_combine(h, type_hash(t->u.array.elem));
            h = hash_combine(h, (uint64_t)t->u.array.size);
            h = hash_combine(h, (uint64_t)t->u.array.size_known);
            break;

        case TY_FUNC:
            h = hash_combine(h, (uint64_t)t->u.func.param_count);
            for (size_t i = 0; i < t->u.func.param_count; i++) {
                h = hash_combine(h, type_hash(t->u.func.params[i]));
            }
            h = hash_combine(h, type_hash(t->u.func.ret));
            break;
    }

    return h;
}

/* strict structural equality */
bool type_equals(const Type *a, const Type *b) {
    if (a == b) return true;              // pointer equal = same canonical type
    if (!a || !b) return false;
    if (a->kind != b->kind) return false;

    switch (a->kind) {
        case TY_NAMED:
            return a->u.named.name_rec == b->u.named.name_rec;

        case TY_PTR:
            return type_equals(a->u.ptr.target, b->u.ptr.target);

        case TY_ARRAY:
            if (a->u.array.size_known != b->u.array.size_known) return false;
            if (a->u.array.size_known && a->u.array.size != b->u.array.size) return false;
            return type_equals(a->u.array.elem, b->u.array.elem);

        case TY_FUNC:
            if (a->u.func.param_count != b->u.func.param_count) return false;
            for (size_t i = 0; i < a->u.func.param_count; i++) {
                if (!type_equals(a->u.func.params[i], b->u.func.params[i]))
                    return false;
            }
            return type_equals(a->u.func.ret, b->u.func.ret);
    }

    return false;
}

/* total ordering comparator (returns -1, 0, 1) useful for ordered maps/printing */
int type_cmp(const Type *a, const Type *b) {
    if (a == b) return 0;
    if (!a) return -1;
    if (!b) return 1;

    if (a->kind != b->kind)
        return (a->kind < b->kind) ? -1 : 1;

    switch (a->kind) {
        case TY_NAMED: {
            uintptr_t A = (uintptr_t)a->u.named.name_rec;
            uintptr_t B = (uintptr_t)b->u.named.name_rec;
            if (A == B) return 0;
            return (A < B) ? -1 : 1;
        }

        case TY_PTR:
            return type_cmp(a->u.ptr.target, b->u.ptr.target);

        case TY_ARRAY:
            if (a->u.array.size_known != b->u.array.size_known)
                return a->u.array.size_known ? 1 : -1;
            if (a->u.array.size_known && a->u.array.size != b->u.array.size)
                return (a->u.array.size < b->u.array.size) ? -1 : 1;
            return type_cmp(a->u.array.elem, b->u.array.elem);

        case TY_FUNC:
            if (a->u.func.param_count != b->u.func.param_count)
                return (a->u.func.param_count < b->u.func.param_count) ? -1 : 1;
            for (size_t i = 0; i < a->u.func.param_count; i++) {
                int c = type_cmp(a->u.func.params[i], b->u.func.params[i]);
                if (c != 0) return c;
            }
            return type_cmp(a->u.func.ret, b->u.func.ret);
    }

    return 0;
}

/* --- resolve_ast_type: fixes and improvements --- */
Type *resolve_ast_type(TypeChecker *tc, AstNode *ast_type) {
    if (!tc || !ast_type || ast_type->node_type != AST_TYPE) {
        return NULL;
    }

    AstType *ast_ty = &ast_type->data.ast_type;

    switch (ast_ty->kind) {
        case AST_TYPE_NAME: {
            if (!ast_ty->u.base.rec) return NULL;

            Type proto = {0};
            proto.kind = TY_NAMED;
            proto.u.named.name_rec = ast_ty->u.base.rec;

            InternResult *res = intern_type(tc, &proto);
            if (!res) return NULL;
            Type *canonical = (Type*)((Slice*)res->key)->ptr;
            return canonical;
        }

        case AST_TYPE_PTR: {
            Type *target_type = resolve_ast_type(tc, ast_ty->u.ptr.target);
            if (!target_type) return NULL;

            Type proto = {0};
            proto.kind = TY_PTR;
            proto.u.ptr.target = target_type;

            InternResult *res = intern_type(tc, &proto);
            if (!res) return NULL;
            Type *canonical = (Type*)((Slice*)res->key)->ptr;
            return canonical;
        }

        case AST_TYPE_ARRAY: {
            Type *elem_type = resolve_ast_type(tc, ast_ty->u.array.elem);
            if (!elem_type) return NULL;

            Type proto = {0};
            proto.kind = TY_ARRAY;
            proto.u.array.elem = elem_type;
            proto.u.array.size_known = false;
            proto.u.array.size = -1;

            if (ast_ty->u.array.size_expr) {
                // simple optimization: accept integer literal sizes here
                if (ast_ty->u.array.size_expr->node_type == AST_LITERAL) {
                    AstLiteral *lit = &ast_ty->u.array.size_expr->data.literal;
                    if (lit->type == INT_LITERAL) {
                        proto.u.array.size = lit->value.v.int_val;
                        proto.u.array.size_known = true;
                    }
                } else {
                    // TODO: evaluate const expr; for now return NULL or set unknown
                }
            }

            InternResult *res = intern_type(tc, &proto);
            if (!res) return NULL;
            Type *canonical = (Type*)((Slice*)res->key)->ptr;
            if (!canonical) return NULL;
            return canonical;
        }

        case AST_TYPE_FUNC: {
            Type proto = {0};
            proto.kind = TY_FUNC;

            // params
            size_t param_count = 0;
            if (ast_ty->u.func.param_types) param_count = ast_ty->u.func.param_types->count;
            proto.u.func.param_count = param_count;
            if (param_count > 0) {
                proto.u.func.params = arena_alloc(tc->arena, sizeof(Type*) * param_count);
                if (!proto.u.func.params) return NULL;
                for (size_t i = 0; i < param_count; ++i) {
                    AstNode *p_ast = *(AstNode**)dynarray_get(ast_ty->u.func.param_types, i);
                    Type *pt = resolve_ast_type(tc, p_ast);
                    if (!pt) return NULL;
                    proto.u.func.params[i] = pt;
                }
            } else {
                proto.u.func.params = NULL;
            }

            // return type (default to void pointer NULL or a dedicated void type if you have one)
            if (ast_ty->u.func.return_type) {
                proto.u.func.ret = resolve_ast_type(tc, ast_ty->u.func.return_type);
                if (!proto.u.func.ret) return NULL;
            } else {
                proto.u.func.ret = NULL; // or tc->type_void if defined
            }

            InternResult *res = intern_type(tc, &proto);
            if (!res) return NULL;
            Type *canonical = (Type*)((Slice*)res->key)->ptr;
            return canonical;
        }

        default:
            return NULL;
    }
}

Type *resolve_function_declaration(TypeChecker *tc, AstNode *ast_func_decl) {
    if (!tc || !ast_func_decl || ast_func_decl->node_type != AST_FUNCTION_DECLARATION) {
        return NULL;
    }

    AstFunctionDeclaration *ast_decl = &ast_func_decl->data.function_declaration;

    Type proto = {0};
    proto.kind = TY_FUNC;

    // Resolve parameter types (support NULL or empty parameter lists)
    size_t param_count = ast_decl->params ? ast_decl->params->count : 0;
    proto.u.func.param_count = param_count;

    if (param_count > 0) {
        proto.u.func.params = arena_alloc(tc->arena, sizeof(Type*) * param_count);
        if (!proto.u.func.params) {
            return NULL;
        }

        for (size_t i = 0; i < param_count; ++i) {
            AstNode *param = *(AstNode**)dynarray_get(ast_decl->params, i);
            if (!param || param->node_type != AST_PARAM) {
                return NULL;
            }

            // Get the type node from the parameter
            AstParam *ast_param = &param->data.param;

            Type *param_type = resolve_ast_type(tc, ast_param->type);
            if (!param_type) {
                return NULL;
            }
            proto.u.func.params[i] = param_type;
        }
    } else {
        proto.u.func.params = NULL;
    }

    // Resolve return type
    if (ast_decl->return_type) {
        proto.u.func.ret = resolve_ast_type(tc, ast_decl->return_type);
        if (!proto.u.func.ret) {
            return NULL;
        }
    } else {
        // No explicit return type - use NULL
        proto.u.func.ret = NULL;
    }

    InternResult *res = intern_type(tc, &proto);
    if (!res) return NULL;
    Type *canonical = (Type*)((Slice*)res->key)->ptr;
    return canonical;
}

/*
 * intern_function_types: Process all function declarations in a program,
 * resolve their types, intern them for canonicalization, and add them to scope.
 * Returns 0 on success, -1 on failure.
 */
int intern_function_types(TypeChecker *tc, Scope *scope, AstNode *program, TypeError *err) {
    if (!tc || !scope || !program) {
        return -1;
    }

    // Iterate over all function declarations in the program
    size_t func_count = program->data.program.decls->count;
    
    for (size_t i = 0; i < func_count; i++) {
        AstNode *func_decl = *(AstNode**)dynarray_get(program->data.program.decls, i);
        if (!func_decl || func_decl->node_type != AST_FUNCTION_DECLARATION) {
            continue;
        }
        
            Type *func_type = resolve_function_declaration(tc, func_decl);
            if (!func_type) {
                if (err) create_type_error(err, tc->arena, "failed to resolve function type", NULL, tc->filename);
                return -1;
            }

            // resolve_function_declaration already returns the canonical Type*;
            // avoid redundant re-interning and assign directly.
            func_decl->type = func_type;

        // Add function to scope
    Symbol *symbol_result = scope_define_symbol(scope, 
                           func_decl->data.function_declaration.name_rec, 
                           func_type, 
                           SYMBOL_VALUE_FUNCTION);
        if (!symbol_result) {
            return -1;
        }
    }

    return 0;
}


void create_type_error(TypeError *err_out, Arena *arena, const char *message, const Span *span, const char *filename) {
    if (!err_out || !arena || !message) return;
    err_out->kind = TEK_GENERIC;
    err_out->message = (char*)arena_alloc(arena, strlen(message) + 1);
    if (err_out->message) strcpy(err_out->message, message);
    err_out->span = span;
    err_out->filename = filename;
}

/* print_type_error: implemented later with kind-specific details */
void print_type_error(TypeError *err);

/* Map OpKind to a printable operator string */
static const char *opkind_to_string(OpKind op) {
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
        default: return "<op>";
    }
}

/* Write a human-readable type signature into buf (buf_size bytes). */
static void format_type_signature_into(char *buf, size_t buf_size, Type *t) {
    if (!buf || buf_size == 0) return;
    if (!t) { snprintf(buf, buf_size, "<null>"); return; }

    switch (t->kind) {
        case TY_NAMED: {
            if (t->u.named.name_rec && t->u.named.name_rec->key) {
                Slice *s = (Slice*)t->u.named.name_rec->key;
                const char *p = (const char*)s->ptr;
                if (p) {
                    /* assume interned strings are NUL-terminated */
                    snprintf(buf, buf_size, "%s", p);
                    return;
                }
            }
            snprintf(buf, buf_size, "<named>");
            return;
        }
        case TY_PTR: {
            char inner[256]; format_type_signature_into(inner, sizeof(inner), t->u.ptr.target);
            snprintf(buf, buf_size, "%s*", inner);
            return;
        }
        case TY_ARRAY: {
            char inner[256]; format_type_signature_into(inner, sizeof(inner), t->u.array.elem);
            if (t->u.array.size_known) snprintf(buf, buf_size, "%s[%lld]", inner, (long long)t->u.array.size);
            else snprintf(buf, buf_size, "%s[]", inner);
            return;
        }
        case TY_FUNC: {
            /* (p1, p2) -> ret */
            size_t off = 0;
            off += snprintf(buf + off, (off < buf_size) ? buf_size - off : 0, "(");
            for (size_t i = 0; i < t->u.func.param_count; ++i) {
                char pbuf[256]; format_type_signature_into(pbuf, sizeof(pbuf), t->u.func.params[i]);
                if (i) off += snprintf(buf + off, (off < buf_size) ? buf_size - off : 0, ", ");
                off += snprintf(buf + off, (off < buf_size) ? buf_size - off : 0, "%s", pbuf);
                if (off >= buf_size) break;
            }
            off += snprintf(buf + off, (off < buf_size) ? buf_size - off : 0, ") -> ");
            if (t->u.func.ret) {
                char rbuf[256]; format_type_signature_into(rbuf, sizeof(rbuf), t->u.func.ret);
                snprintf(buf + off, (off < buf_size) ? buf_size - off : 0, "%s", rbuf);
            } else {
                snprintf(buf + off, (off < buf_size) ? buf_size - off : 0, "<null>");
            }
            return;
        }
        default:
            snprintf(buf, buf_size, "<unknown>");
            return;
    }
}

/* Enhanced error printing with kind-specific details */
void print_type_error(TypeError *err) {
    if (!err || !err->message) return;
    const char *fn = err->filename ? err->filename : "<unknown>";
    /* Header */
    fprintf(stderr, RED "type error:" RESET " %s\n", err->message);

    /* Location and excerpt if available */
    if (err->span && err->span->start_line > 0) {
        fprintf(stderr, "  %s:%zu:%zu\n", fn, err->span->start_line, err->span->start_col);
        print_source_excerpt(fn, err->span->start_line, err->span->start_col);
    }

    /* Kind-specific details */
    switch (err->kind) {
        case TEK_BINOP: {
            char leftbuf[256], rightbuf[256];
            format_type_signature_into(leftbuf, sizeof(leftbuf), err->info.binop.left);
            format_type_signature_into(rightbuf, sizeof(rightbuf), err->info.binop.right);
            const char *opstr = opkind_to_string(err->info.binop.op);
            fprintf(stderr, "  operator: %s\n", opstr);
            fprintf(stderr, "  left:  %s\n", leftbuf);
            fprintf(stderr, "  right: %s\n", rightbuf);
            break;
        }
        case TEK_PROMOTION: {
            char srcbuf[256], dstbuf[256];
            format_type_signature_into(srcbuf, sizeof(srcbuf), err->info.promo.src);
            format_type_signature_into(dstbuf, sizeof(dstbuf), err->info.promo.dst);
            fprintf(stderr, "  cannot promote %s (handle=%d) to %s (handle=%d)\n",
                    srcbuf, err->info.promo.src_handle, dstbuf, err->info.promo.dst_handle);
            break;
        }
        case TEK_ASSIGNMENT: {
            char foundbuf[256], expectbuf[256];
            format_type_signature_into(foundbuf, sizeof(foundbuf), err->info.assign.found);
            format_type_signature_into(expectbuf, sizeof(expectbuf), err->info.assign.expected);
            fprintf(stderr, "  cannot assign %s to %s\n", foundbuf, expectbuf);
            break;
        }
        default:
            /* generic already printed */
            break;
    }
}

void create_type_error_promotion(TypeError *err_out, Arena *arena, const Span *span, const char *filename, struct Type *src, int src_handle, struct Type *dst, int dst_handle) {
    if (!err_out || !arena) return;
    err_out->kind = TEK_PROMOTION;
    err_out->message = (char*)arena_alloc(arena, 128);
    if (err_out->message) {
        snprintf(err_out->message, 128, "cannot promote type (handle=%d) to target (handle=%d)", src_handle, dst_handle);
    }
    err_out->span = span;
    err_out->filename = filename;
    err_out->info.promo.src = src;
    err_out->info.promo.dst = dst;
    err_out->info.promo.src_handle = src_handle;
    err_out->info.promo.dst_handle = dst_handle;
}

void create_type_error_assignment(TypeError *err_out, Arena *arena, const Span *span, const char *filename, struct Type *found, struct Type *expected) {
    if (!err_out || !arena) return;
    err_out->kind = TEK_ASSIGNMENT;
    err_out->message = (char*)arena_alloc(arena, 128);
    if (err_out->message) {
        snprintf(err_out->message, 128, "cannot assign value of given type to target type");
    }
    err_out->span = span;
    err_out->filename = filename;
    err_out->info.assign.found = found;
    err_out->info.assign.expected = expected;
}

void create_type_error_binop(TypeError *err_out, Arena *arena, const Span *span, const char *filename, OpKind op, struct Type *left, struct Type *right) {
    if (!err_out || !arena) return;
    err_out->kind = TEK_BINOP;
    err_out->message = (char*)arena_alloc(arena, 128);
    if (err_out->message) {
        snprintf(err_out->message, 128, "invalid operands to binary operator");
    }
    err_out->span = span;
    err_out->filename = filename;
    err_out->info.binop.op = op;
    err_out->info.binop.left = left;
    err_out->info.binop.right = right;
}

int intern_type_handles(TypeChecker *tc, DenseArenaInterner *keywords) {
    if (!tc) return -1;

    // intern slice
    Slice int32_slice = { .ptr = "i32", .len = 3 };
    Type int32_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &int32_slice) };

    Slice int64_slice = { .ptr = "i64", .len = 3 };
    Type int64_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &int64_slice) };

    Slice float32_slice = { .ptr = "f32", .len = 3 };
    Type float32_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &float32_slice) };

    Slice float64_slice = { .ptr = "f64", .len = 3 };
    Type float64_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &float64_slice) };

    Slice bool_slice = { .ptr = "bool", .len = 4 };
    Type bool_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &bool_slice) };

    Slice char_slice = { .ptr = "char", .len = 4 };
    Type char_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &char_slice) };

    Slice string_slice = { .ptr = "str", .len = 3 };
    Type string_type = { .kind = TY_NAMED, .u.named.name_rec = intern_peek(keywords, &string_slice) };

    // Intern each type handle
    /* Intern the canonical Type objects and fetch dense indices via intern_idx */
    Slice s1 = { .ptr = (const char*)&int32_type, .len = sizeof(Type) };
    Slice s2 = { .ptr = (const char*)&int64_type, .len = sizeof(Type) };
    Slice s3 = { .ptr = (const char*)&float32_type, .len = sizeof(Type) };
    Slice s4 = { .ptr = (const char*)&float64_type, .len = sizeof(Type) };
    Slice s5 = { .ptr = (const char*)&bool_type, .len = sizeof(Type) };
    Slice s6 = { .ptr = (const char*)&char_type, .len = sizeof(Type) };
    Slice s7 = { .ptr = (const char*)&string_type, .len = sizeof(Type) };

    INT32_TYPE_HANDLE = intern_idx(tc->type_interner, &s1, NULL);
    INT64_TYPE_HANDLE = intern_idx(tc->type_interner, &s2, NULL);
    FLOAT32_TYPE_HANDLE = intern_idx(tc->type_interner, &s3, NULL);
    FLOAT64_TYPE_HANDLE = intern_idx(tc->type_interner, &s4, NULL);
    BOOL_TYPE_HANDLE = intern_idx(tc->type_interner, &s5, NULL);
    CHAR_TYPE_HANDLE = intern_idx(tc->type_interner, &s6, NULL);
    STRING_TYPE_HANDLE = intern_idx(tc->type_interner, &s7, NULL);

    /* Save Type* for convenience */
    INT32_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s1, NULL)->key)->ptr;
    INT64_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s2, NULL)->key)->ptr;
    FLOAT32_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s3, NULL)->key)->ptr;
    FLOAT64_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s4, NULL)->key)->ptr;
    BOOL_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s5, NULL)->key)->ptr;
    CHAR_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s6, NULL)->key)->ptr;
    STRING_TYPE_PTR = (Type*)((Slice*)intern(tc->type_interner, &s7, NULL)->key)->ptr;

    return 0;
}

void init_promotion_matrix(void) {
    for (int i = 0; i < NUM_TYPE_KINDS; ++i) {
        for (int j = 0; j < NUM_TYPE_KINDS; ++j) {
            promotion_matrix[i][j] = -1;
        }
    }

    #define SET_PROMOTE(A, B, R) do { promotion_matrix[(A)][(B)] = (R); promotion_matrix[(B)][(A)] = (R); } while (0)

    // Identity: T + T => T
    for (int t = 0; t < NUM_TYPE_KINDS; ++t) {
        promotion_matrix[t][t] = t;
    }

    SET_PROMOTE(INT32_TYPE_HANDLE, INT64_TYPE_HANDLE, INT64_TYPE_HANDLE);

    SET_PROMOTE(INT32_TYPE_HANDLE, FLOAT32_TYPE_HANDLE, FLOAT32_TYPE_HANDLE);

    SET_PROMOTE(INT32_TYPE_HANDLE, FLOAT64_TYPE_HANDLE, FLOAT64_TYPE_HANDLE);

    SET_PROMOTE(INT64_TYPE_HANDLE, FLOAT32_TYPE_HANDLE, FLOAT64_TYPE_HANDLE);

    SET_PROMOTE(INT64_TYPE_HANDLE, FLOAT64_TYPE_HANDLE, FLOAT64_TYPE_HANDLE);

    SET_PROMOTE(FLOAT32_TYPE_HANDLE, FLOAT64_TYPE_HANDLE, FLOAT64_TYPE_HANDLE);

    #undef SET_PROMOTE
}

/* Map a dense type handle back to its canonical Type* via interner's dense array. */
Type *type_handle_to_type_ptr(int handle) {
    /* We don't have a direct accessor; callers typically track Type* directly. */
    /* This stub can be filled if we add an access-by-index API on the interner. */
    return NULL;
}

// Assumes PromotionPlan is:
// typedef struct {
//     int promote_left;    // -1 = no, else type
//     int promote_right;   // -1 = no, else type
//     int result;          // -1 = no promotion / invalid, else final type
// } PromotionPlan;

static inline int is_integer_type_handle(int t) {
    return (t == INT32_TYPE_HANDLE || t == INT64_TYPE_HANDLE /* add other integer handles here */);
}
static inline int is_floating_type_handle(int t) {
    return (t == FLOAT32_TYPE_HANDLE || t == FLOAT64_TYPE_HANDLE /* add other float handles here */);
}

/* Return the dense-index handle for a canonical Type*, interning if needed. */
static inline int get_type_handle(TypeChecker *tc, Type *t) {
    if (!tc || !t) return -1;
    Slice s = { .ptr = (const char*)t, .len = sizeof(Type) };
    return intern_idx(tc->type_interner, &s, NULL);
}

/*
 * Infer the result type for a binary operation and fill 'plan'.
 * Returns the resulting type handle (>=0) or -1 on error/incompatible types.
 */
int infer_binary_result_type(Type *left, Type *right, OpKind op, PromotionPlan *plan, TypeChecker *tc, TypeError *err) {
    if (!plan){
    if (err) create_type_error(err, tc->arena, "internal error: NULL promotion plan", NULL, tc->filename);
        return -1;
    }
    
    if (!left || !right) {
    if (err) create_type_error(err, tc->arena, "type error: NULL operand", NULL, tc->filename);
        return -1;
    }

    /* Only handle primitive named types for arithmetic/promotions */
    if (left->kind != TY_NAMED || right->kind != TY_NAMED) {
        if (err) create_type_error_binop(err, tc->arena, NULL, tc->filename, op, left, right);
        plan->promote_left = plan->promote_right = plan->result = -1;
        return -1;
    }

    /* Extract dense indices (type handles) */
    int left_t  = left->u.named.name_rec && left->u.named.name_rec->entry ? left->u.named.name_rec->entry->dense_index : -1;
    int right_t = right->u.named.name_rec && right->u.named.name_rec->entry ? right->u.named.name_rec->entry->dense_index : -1;

    /* Basic bounds safety */
    if (left_t < 0 || left_t >= NUM_TYPE_KINDS || right_t < 0 || right_t >= NUM_TYPE_KINDS) {
        plan->promote_left = plan->promote_right = plan->result = -1;
    if (err) create_type_error(err, tc->arena, "type error: operand type out of bounds", NULL, tc->filename);
        return -1;
    }

    /* Lookup promotion/common type for arithmetic/comparable ops */
    int promotion = promotion_matrix[left_t][right_t];

    /* Fill promotion plan fields using YOUR -1 semantics */
    plan->promote_left  = (left_t  != promotion) ? promotion : -1;
    plan->promote_right = (right_t != promotion) ? promotion : -1;
    plan->result = -1; /* set below based on op */

    /* Decide result type by operation kind */
    switch (op) {
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV: {
            if (promotion == -1) {
                plan->promote_left = plan->promote_right = plan->result = -1;
                if (err) create_type_error_promotion(err, tc->arena, NULL, tc->filename, left, left_t, right, right_t);
                return -1;
            }
            /* Arithmetic: result is the promoted/common type */
            plan->result = promotion;
            return plan->result;
        }

        case OP_MOD: {
            if (promotion == -1) {
                plan->promote_left = plan->promote_right = plan->result = -1;
                if (err) create_type_error_promotion(err, tc->arena, NULL, tc->filename, left, left_t, right, right_t);
                return -1;
            }
            /* Modulo only valid for integers */
            if (is_integer_type_handle(promotion)) {
                plan->result = promotion;
                return plan->result;
            } else {
                plan->result = -1;
                if (err) create_type_error_binop(err, tc->arena, NULL, tc->filename, OP_MOD, left, right);
                return -1;
            }
        }

        case OP_EQ:
        case OP_NEQ: {
            /* Equality: require identical or promotable */
            if (left_t == right_t || promotion != -1) {
                plan->result = BOOL_TYPE_HANDLE;
                /* no need to promote bool result */
                plan->promote_left  = (left_t  != right_t) ? promotion : -1;
                plan->promote_right = (right_t != left_t) ? promotion : -1;
                return plan->result;
            }
            plan->promote_left = plan->promote_right = plan->result = -1;
            if (err) create_type_error_binop(err, tc->arena, NULL, tc->filename, op, left, right);
            return -1;
        }

        case OP_LT:
        case OP_GT:
        case OP_LE:
        case OP_GE: {
            /* Relational comparisons: require numeric promotion */
            if (promotion != -1 && (is_integer_type_handle(promotion) || is_floating_type_handle(promotion))) {
                plan->result = BOOL_TYPE_HANDLE;
                return plan->result;
            } else {
                plan->result = -1;
                if (err) create_type_error_binop(err, tc->arena, NULL, tc->filename, op, left, right);
                return -1;
            }
        }

        case OP_AND:
        case OP_OR: {
            /* Logical operators require boolean operands */
            if (left_t == BOOL_TYPE_HANDLE && right_t == BOOL_TYPE_HANDLE) {
                plan->promote_left = plan->promote_right = -1;
                plan->result = BOOL_TYPE_HANDLE;
                return plan->result;
            }
            plan->promote_left = plan->promote_right = plan->result = -1;
            if (err) create_type_error_binop(err, tc->arena, NULL, tc->filename, op, left, right);
            return -1;
        }

        default:
            /* Unsupported op */
            plan->result = -1;
            return -1;
    }
}

int infer_unary_result_type(Type *operand, OpKind op, TypeChecker *tc, TypeError *err) {
    if (!operand) {
        if (err) create_type_error(err, tc->arena, "type error: NULL operand", NULL, tc->filename);
        return -1;
    }

    //if (operand->kind != TY_NAMED) {
    //    if (err) create_type_error(err, tc->arena, "type error: unsupported operand type", NULL, tc->filename);
    //    return -1;
    //}

    /* For named primitives we can use dense index directly; for composite types we will intern as needed. */
    int operand_dense_idx = -1;
    if (operand->kind == TY_NAMED && operand->u.named.name_rec && operand->u.named.name_rec->entry) {
        operand_dense_idx = operand->u.named.name_rec->entry->dense_index;
    } else {
        operand_dense_idx = get_type_handle(tc, operand);
    }

    switch (op) {
        case OP_SUB: // unary minus
        case OP_ADD: // unary plus (no-op)
            if (is_integer_type_handle(operand_dense_idx) || is_floating_type_handle(operand_dense_idx)) {
                return operand_dense_idx; // result type is same as operand
            } else {
                if (err) create_type_error(err, tc->arena, "type error: invalid operand type for unary minus", NULL, tc->filename);
                return -1;
            }

        case OP_NOT: // logical NOT
            if (operand_dense_idx == BOOL_TYPE_HANDLE) {
                return BOOL_TYPE_HANDLE; // result is bool
            } else {
                if (err) create_type_error(err, tc->arena, "type error: invalid operand type for logical NOT", NULL, tc->filename);
                return -1;
            }
        case OP_DEREF: {
            if (operand->kind != TY_PTR || !operand->u.ptr.target) {
                if (err) create_type_error(err, tc->arena, "type error: cannot dereference non-pointer", NULL, tc->filename);
                return -1;
            }
            /* Result is the target type's handle; intern if needed */
            return get_type_handle(tc, operand->u.ptr.target);
        }

        case OP_ADRESS: {
            /* Result is a pointer to the operand's type; create proto and intern */
            Type proto = {0};
            proto.kind = TY_PTR;
            proto.u.ptr.target = operand;
            Slice s = { .ptr = (const char*)&proto, .len = sizeof(Type) };
            return intern_idx(tc->type_interner, &s, NULL);
        }

        default:
            if (err) create_type_error(err, tc->arena, "type error: unsupported unary operator", NULL, tc->filename);
            return -1;
    }
}