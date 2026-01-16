#pragma once

#include "dense_arena_interner.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct Type Type;
typedef struct Symbol Symbol; // Forward declaration for structs/typedefs

typedef enum {
    TYPE_VOID,
    TYPE_PRIMITIVE, // i32, f64, bool, etc.
    TYPE_POINTER,
    TYPE_ARRAY,
    TYPE_FUNCTION,
    TYPE_STRUCT,    // User defined (not yet implemented)
    TYPE_ENUM       // User defined (not yet implemented)
} TypeKind;

typedef enum {
    PRIM_I8, PRIM_I16, PRIM_I32, PRIM_I64,
    PRIM_U8, PRIM_U16, PRIM_U32, PRIM_U64,
    PRIM_F32, PRIM_F64,
    PRIM_BOOL,
    PRIM_CHAR,
    PRIM_VOID
} PrimitiveKind;

struct Type {
    TypeKind kind;
    uint64_t cached_hash; // Stored hash for memoization

    union {
        // TYPE_PRIMITIVE
        PrimitiveKind primitive;

        // TYPE_POINTER
        struct {
            Type *base;
        } ptr;

        // TYPE_ARRAY
        struct {
            Type *base;
            int64_t size;     // Count of elements
            bool size_known;  // false for type[]
        } array;

        // TYPE_FUNCTION
        struct {
            Type *return_type;
            Type **params;
            size_t param_count;

        } func;

        // TYPE_STRUCT / TYPE_ENUM
        struct {
            char *name;       // Debug name
            Symbol *decl_node; // Link back to the AST/Symbol table for fields
        } user;
    } as;
};

// The Container
typedef struct TypeStore {
    Arena *arena;

    DenseArenaInterner *type_interner; // For interning complex types
    
    // The "Registry" for primitives
    // Key:   void* (The interned key from your identifiers interner)
    // Value: Type*
    HashMap *primitive_registry; 

    // Fast access to common primitives so we don't need to look them up constantly
    Type *t_void;
    Type *t_i8, *t_i16, *t_i32, *t_i64;
    Type *t_u8, *t_u16, *t_u32, *t_u64;
    Type *t_f32, *t_f64;
    Type *t_bool;
    Type *t_char;
} TypeStore;

TypeStore *typestore_create(Arena *arena, DenseArenaInterner *identifiers, DenseArenaInterner *keywords);
InternResult *intern_type(TypeStore *ts, Type *prototype);
