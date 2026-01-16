# Semantics & Types

[← Back to docs index](./README.md)

## On this page
- [Overview](#overview)
- [Type Representation](#type-representation)
- [Scope System](#scope-system)
- [The Universe Scope](#the-universe-scope)
- [Type Resolution](#type-resolution)
- [Cross references](#cross-references)

## Overview
The semantic analysis phase is responsible for attaching meaning to the syntactic structure (AST). This involves:
1.  **Scope Management**: Tracking visibility of symbols (variables, functions, types).
2.  **Type Resolution**: Recursively determining the `Type*` for AST nodes.
3.  **Correctness**: Ensuring identifiers are declared before use and types match interactions.

## Type Representation
Types are structural and interned. Two identical types (e.g., `i32` and `i32`, or `(i32) -> void` and `(i32) -> void`) will share the same pointer address.

Defined in [`include/sema/type.h`](../include/sema/type.h):

```c
typedef enum {
    TYPE_VOID,
    TYPE_PRIMITIVE, // i32, f64, bool, etc.
    TYPE_POINTER,
    TYPE_ARRAY,
    TYPE_FUNCTION,
    TYPE_STRUCT
} TypeKind;

struct Type {
    TypeKind kind;
    uint64_t cached_hash;
    union {
        PrimitiveKind primitive;
        struct { Type *base; } ptr;
        struct { Type *base; int64_t size; } array;
        struct { Type *return_type; Type **params; size_t param_count; } func;
        // ... struct/enum details
    } as;
};
```

### TypeStore
The `TypeStore` acts as the global context for all types. It holds:
- The **Arena** where type memory is allocated.
- The **Dense Interner** for deduplicating complex types (arrays, functions, pointers).
- Pre-allocated pointers to primitive singletons (`t_i32`, `t_void`, etc.) for fast access.

## Scope System
The compiler uses a hierarchical scope system to look up symbols (identifiers).

> **Deep Dive**: See [docs/scope.md](./scope.md) for the full architectural details of Scope Kinds and the Identifier/Keyword distinction.

Defined in [`include/datastructures/scope.h`](../include/datastructures/scope.h):

```c
typedef struct Scope {
    Symbol **symbols;    // Dense array mapping InterResult index -> Symbol*
    size_t capacity;
    Scope *parent;       // Parent scope (NULL for Universe)
    /* ... see scope.md for details on ScopeKind ... */
} Scope;
```

### Hierarchy (Summary)
1.  **Global Scope**: File level. Contains functions/globals. (Type: `SCOPE_IDENTIFIERS`)
2.  **Local Scopes**: Blocks. Contains local variables. (Type: `SCOPE_IDENTIFIERS`)

## Primitive Registry (TypeStore)
Primitive types are no longer stored in a "Universe Scope". Instead, they are registered directly in the `TypeStore`'s `primitive_registry` HashMap.

- When the `TypeStore` is created, it populates `primitive_registry` with `Type*` for `i32`, `f64`, etc.
- The registry keys are the canonical pointers from the `Identifiers` (and `Keywords`) interner.
- This allows O(1) checking using pointer identity during resolution.

## Type Resolution
Resolution is performed by traversing the AST and linking nodes to `Type*` pointers from the `TypeStore`. This is a recursive process that turns syntactic descriptions of types (AST) into semantic type objects.

Key function: `resolve_ast_type(TypeStore *store, Scope *scope, AstNode *node)`

### How it works
The resolver switches on the `AstType` kind:

1.  **Primitive / Named Types** (`AST_TYPE_PRIMITIVE`): 
    *   The most common case. The AST has an `InternResult` for the name (e.g., "i32" or "MyStruct").
    *   **Registry Check**: First, we check if the name's key pointer exists in `store->primitive_registry`. If so, we return the primitive type immediately.
    *   **Scope Lookup**: If not in the registry, we call `scope_lookup_symbol(scope, name)` to find user-defined types (structs/typedefs) in the scope chain.

2.  **Pointer Types** (`AST_TYPE_PTR`):
    *   We recursively call `resolve_ast_type` for the base type (e.g., resolve "i32" inside "i32*").
    *   We ask the **TypeStore** to intern a `TYPE_POINTER` that points to that base.
    *   *Result*: Providing a canonical pointer to `i32*`.

3.  **Array Types** (`AST_TYPE_ARRAY`):
    *   Resolve element type.
    *   Evaluate the size expression (if present) to a constant integer.
    *   Ask **TypeStore** to intern `TYPE_ARRAY`.

4.  **Function Types** (`AST_TYPE_FUNC`):
    *   Resolve return type.
    *   Resolve all parameter types.
    *   Ask **TypeStore** to intern `TYPE_FUNCTION`.

### The TypeStore Role
The `TypeStore` ensures that types are **canonical**. 
*   If you declare `fn a(x: i32*)` and `fn b(y: i32*)`, both function signatures point to the exact same memory address for the `Type` object representing `i32*`.
*   This allows type equality checking to be a simple pointer comparison: `if (type_a == type_b)`.

```c
// Example: Resolving "i32*"
// 1. Resolve "i32" -> t_i32 (via Scope lookup)
// 2. Construct Type{ .kind = TYPE_POINTER, .base = t_i32 }
// 3. Intern(new_type) -> return canonical pointer
```


## Cross references
- [Interner](./interner.md): Explains how strings and types are deduplicated.
- [Parsing](./parsing.md): How the AST structure is built before resolution.
