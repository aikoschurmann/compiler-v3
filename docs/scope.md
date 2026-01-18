# Scope System

[← Back to docs index](./README.md)

## On this page
- [Overview](#overview)
- [Architecture](#architecture)
- [Scope Kinds](#scope-kinds)
- [Symbol Lookup Strategy](#symbol-lookup-strategy)
- [Data Structures](#data-structures)

## Overview

The Scope system is the backbone of semantic analysis. It is responsible for:
1.  **Mapping Names to MEANING**: Connecting a string (like `"x"` or `"i32"`) to a `Symbol`.
2.  **Tracking Visibility**: Ensuring variables are only accessible where they are declared.
3.  **Managing Lifetimes**: Handling the hierarchy from Global -> Function -> Block scopes.

Key File: [`include/datastructures/scope.h`](../include/datastructures/scope.h)

## Architecture

The compiler constructs a tree of Scope objects.

```
Global Scope (Root)
│
├── Function A Scope
│   └── Block Scope
│       └── Block Scope
│
└── Function B Scope
```

Each `Scope` contains a pointer to its `parent`. Lookup proceeds from the current scope upward to the root.

## Scope Kinds

The scope system deals with user-defined symbols.

```c
typedef enum {
    SCOPE_IDENTIFIERS, // Standard scopes (Global, Local)
    SCOPE_KEYWORDS     // Reserved for keyword-only scopes (currently unused)
} ScopeKind;
```

*   **SCOPE_IDENTIFIERS**: Stores user-defined symbols (variables, functions, custom types). The search key must be an Identifier.

## Primitives and Registry

Primitives are resolved via the **Primitive Registry** inside the `TypeStore`.

1.  **Registry**: A fast HashMap used by `resolve_ast_type` to map interner keys (like the pointer for `"i32"`) directly to Type objects.
2.  **Lookup Order**: Primitive resolution happens *before* scope lookup.

## Symbol Lookup Strategy

The function `scope_lookup_symbol(scope, key)` implements standard traversal.

When you ask for a symbol:
1.  It traverses the scope chain.
2.  For each scope, it checks: **Does this Scope's Kind match the Key's Kind?** (Currently mostly SCOPE_IDENTIFIERS).
3.  If found, returns the Symbol.

### Example: Looking up `x` (Identifier)
1.  Start at Local Scope (`SCOPE_IDENTIFIERS`). Match! Check table... found? Return.
2.  If not found, go to Parent (Global Scope, `SCOPE_IDENTIFIERS`). Match! Check table... found? Return.
3.  Parent is NULL. Symbol not found.

### Example: Looking up `i32`
1.  `resolve_ast_type` first checks `store->primitive_registry`.
2.  Since `"i32"` is in the registry, it returns the primitive type immediately.
3.  `scope_lookup_symbol` is NEVER CALLED for recognized primitives.

## Data Structures

### The Scope Struct
The scope uses a **Dense Array Map** strategy. Since identifiers are interned into the `DenseArenaInterner`, every unique identifier has a unique `dense_index`. We use this index to directly access the symbol array.

```c
struct Scope {
    Symbol **symbols;    // Array indexed by InternResult->dense_index
    size_t capacity;     // Size of the array
    Scope *parent;       // Link up the chain
    ScopeKind kind;      // IDENTIFIERS or KEYWORDS
};
```

This makes symbol lookup exceptionally fast (array access), avoiding a second hash computation during semantic analysis. The symbol array grows on demand when a new identifier index exceeds the current capacity.

### The Symbol Struct
The `Symbol` holds the semantic information.

```c
struct Symbol {
    InternResult *name_rec; // The name (key)
    Type *type;             // The resolved type
    SymbolValue kind;       // VALUE_TYPE, VALUE_FUNCTION, etc.
    // ...
};
```
