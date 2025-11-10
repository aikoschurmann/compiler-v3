#pragma once    

#include "arena.h"
#include "dense_arena_interner.h"
#include "hash_map.h"
#include "dynamic_array.h"
#include "utils.h"
#include "ast.h"

#define NUM_TYPE_KINDS 7

typedef struct {
    Arena *arena;
    HashMap *type_hashmap;               // for interner
    DenseArenaInterner *type_interner;
    int keyword_offset;
    const char *filename; // filename pointer (arena-owned)
} TypeChecker;


// code snippet: semantic type representation

typedef enum {
    TY_NAMED, 
    TY_PTR,
    TY_ARRAY,
    TY_FUNC,
} TypeKind;

// Declare type_handles
extern int INT32_TYPE_HANDLE;
extern int INT64_TYPE_HANDLE;
extern int FLOAT32_TYPE_HANDLE;
extern int FLOAT64_TYPE_HANDLE;
extern int BOOL_TYPE_HANDLE;
extern int CHAR_TYPE_HANDLE;
extern int STRING_TYPE_HANDLE;

// Canonical primitive Type* pointers (set during intern_type_handles)
extern struct Type *INT32_TYPE_PTR;
extern struct Type *INT64_TYPE_PTR;
extern struct Type *FLOAT32_TYPE_PTR;
extern struct Type *FLOAT64_TYPE_PTR;
extern struct Type *BOOL_TYPE_PTR;
extern struct Type *CHAR_TYPE_PTR;
extern struct Type *STRING_TYPE_PTR;

// 2D int promotion array
int promotion_matrix[NUM_TYPE_KINDS][NUM_TYPE_KINDS];


typedef struct Type {
    TypeKind kind;

    union {
        // TY_PTR
        struct { struct Type *target; } ptr;

        // TY_ARRAY
        struct { struct Type *elem; int64_t size; bool size_known; } array;

        // TY_FUNC
        struct { struct Type **params; size_t param_count; struct Type *ret; } func;

        // TY_NAMED
        struct { InternResult *name_rec; } named;

    } u;
} Type;

typedef struct {
    int promote_left;    // -1 = no, else type
    int promote_right;   // -1 = no, else type
    int result;          // -1 = no promotion, else final type
} PromotionPlan;

typedef struct Scope Scope;
TypeChecker *typecheck_create(Arena *arena, const char *filename);
InternResult *intern_type(TypeChecker *tc, Type *prototype);
Type *resolve_ast_type(TypeChecker *tc, AstNode *ast_type);
Type *resolve_function_declaration(TypeChecker *tc, AstNode *ast_func_decl);

/* Type error support (rich, span-aware) */

typedef enum {
    TEK_GENERIC,
    TEK_PROMOTION,
    TEK_ASSIGNMENT,
    TEK_BINOP,
    TEK_UNARY,
    TEK_SUBSCRIPT
} TypeErrorKind;

typedef struct {
    TypeErrorKind kind;
    char *message;   /* arena-owned message */
    const Span *span;      /* pointer to location in source (owned by AST/token) */
    const char *filename;  /* filename pointer (arena-owned) */
    union {
        struct { OpKind op; struct Type *left; struct Type *right; } binop;
        struct { struct Type *found; struct Type *expected; } assign;
        struct { struct Type *src; struct Type *dst; int src_handle; int dst_handle; } promo;
    } info;
} TypeError;

/* Generic error */
void create_type_error(TypeError *err_out, Arena *arena, const char *message, const Span *span, const char *filename);
/* Specialized creators */
void create_type_error_promotion(TypeError *err_out, Arena *arena, const Span *span, const char *filename, struct Type *src, int src_handle, struct Type *dst, int dst_handle);
void create_type_error_assignment(TypeError *err_out, Arena *arena, const Span *span, const char *filename, struct Type *found, struct Type *expected);
void create_type_error_binop(TypeError *err_out, Arena *arena, const Span *span, const char *filename, OpKind op, struct Type *left, struct Type *right);
void print_type_error(TypeError *err);

// Utility functions
const char *type_kind_to_string(TypeKind kind);
int intern_function_types(TypeChecker *tc, Scope *scope, AstNode *program, TypeError *err);
int intern_type_handles(TypeChecker *tc, DenseArenaInterner *keywords);
void init_promotion_matrix(void);

// Inference helpers
int infer_binary_result_type(struct Type *left, struct Type *right, OpKind op, PromotionPlan *plan, TypeChecker *tc, TypeError *err);
int infer_unary_result_type(struct Type *operand, OpKind op, TypeChecker *tc, TypeError *err);
struct Type *type_handle_to_type_ptr(int handle);
