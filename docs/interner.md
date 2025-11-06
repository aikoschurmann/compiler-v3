# Dense Arena Interner
## On this page
- [What it is](#what-it-is)
- [Why use it](#why-use-it)
- [Core data structures](#core-data-structures)
- [Core operations](#core-operations)
- [Typical usage](#typical-usage)
- [Why we need an interner](#why-we-need-an-interner)
	- [Lexing in more detail: keyword lookup](#lexing-in-more-detail-keyword-lookup)
	- [Parsing in more detail: identifiers and scopes](#parsing-in-more-detail-identifiers-and-scopes)
	- [Semantic analysis in more detail: types and promotion](#semantic-analysis-in-more-detail-types-and-promotion)
- [How it integrates](#how-it-integrates)
- [Invariants](#invariants)
## What it is
A Dense Arena Interner is a small layer that **stores one canonical copy** of each unique value and gives each one a **stable small integer index**. It sits on top of three underlying pieces:

- **Arena** — stores the canonical data so pointers stay stable.
- **HashMap** — checks whether a given value already exists (deduplication).
- **DynArray** — keeps all interned values in a dense 0..N-1 array for indexing.

You provide a temporary value (as a `Slice`: pointer + length).  
The interner returns:
- a **canonical pointer** (into the arena), and
- a **dense index** (small integer handle).

Identical values return the **same pointer and same index**.

### How it works (quick flow)
1. You give the interner a temporary `Slice` (does not need to be long-lived).
2. It hashes and compares the slice against existing entries via `hash_func` and `cmp_func`.
3. If an identical value **already exists**, the interner returns the existing canonical pointer and handle — **no allocation**.
4. If it **does not exist**:
   - `copy_func` copies the slice into the **arena**, producing the canonical version.
   - A new **Entry** is created with a new **dense index**.
   - An **InternResult** is pushed into the dense `DynArray`.
   - The canonical key is inserted into the `HashMap`.
   - The new pointer + handle are returned in the form of InternResult.

Result: **One unique, stable, interned copy per distinct value**, with **fast pointer/handle equality**.

## Why use it
| Need | Interner advantage |
|------|--------------------|
| Fast equality | Pointer compare instead of deep compare/strcmp |
| Deduplication | One canonical copy per unique value |
| Dense indexing | Direct array lookups (promotion matrix, symbol tables) |
| Stable lifetime | Arena guarantees immovable pointers |
| Pluggable types | Custom hash/copy/equality wrappers per domain |


## Why we need an interner
- Lexing: Identifiers & string literals interned once, so keyword detection and identifier equality become pointer comparisons instead of repeated strcmp + allocation.
- Parsing: AST nodes hold canonical names (and later, type names). Structural equality reduces to pointer equality; lifetime managed by arena.
- Semantic analysis: Types & symbols interned; type equality O(1), dense indices drive tables (promotion matrix, vtables, etc.).

### Lexing in more detail: keyword lookup
Instead of a manual chain of `strncmp` checks for every identifier, we intern the slice of source text and tag known keywords with metadata. Then any later occurrence of the same spelling hits the existing entry instantly.

Minimal pattern:
```c
// During lexer initialization
static struct { const char *kw; TokenType tt; } KW[] = {
	{"fn", TOK_FN}, {"if", TOK_IF}, {"else", TOK_ELSE}, {"while", TOK_WHILE},
	{"for", TOK_FOR}, {"return", TOK_RETURN}, {"break", TOK_BREAK}, {"continue", TOK_CONTINUE},
	{"const", TOK_CONST}, {"true", TOK_TRUE}, {"false", TOK_FALSE},
};

HashMap *kw_map = hashmap_create(64);
DenseArenaInterner *KW_I = intern_table_create(kw_map, arena, string_copy_func, slice_hash, slice_cmp);

for (size_t i = 0; i < sizeof(KW)/sizeof(KW[0]); ++i) {
	Slice s = { KW[i].kw, (uint32_t)strlen(KW[i].kw) };
	// Store TokenType as metadata (cast through pointer-sized integer if needed)
	intern(KW_I, &s, (void*)(uintptr_t)KW[i].tt);
}

// In the main lex loop when we scan an identifier span
Slice ident = { start_ptr, (uint32_t)(cur - start_ptr) };
InternResult *hit = intern_peek(KW_I, &ident);
Token tok;
tok.slice = ident; // points into source; stable during lexing
if (hit) {
	tok.type = (TokenType)(uintptr_t)hit->entry->meta; // keyword token
	tok.record = hit; // canonical keyword record
} else {
	// Not a keyword: intern into the general identifier table
	InternResult *id_rec = intern(ID_I, &ident, NULL); // ID_I another interner
	tok.type = TOK_IDENTIFIER;
	tok.record = id_rec;
}
```

#### Benefits
- Single hash+lookup per identifier vs many `strncmp` along a keyword list.
- Pointer equality for later symbol table operations (parser / semantic phases reuse `tok.record`).
- Metadata lets you attach TokenType or other flags without a separate map.

### Parsing in more detail: identifiers and scopes
Parser reuses the lexer's canonical record to avoid re-hashing names and to make symbol lookups trivial.

AST identifier node can store the canonical record:
```c
typedef struct {
	const InternResult *name; // canonical intern record from token
	Span span;
} AstIdent;

// When consuming an identifier token
AstIdent *make_ident(Token tok) {
	AstIdent *id = arena_alloc(ast_arena, sizeof *id);
	id->name = tok.record; // zero-copy, canonical
	id->span = tok.span;
	return id;
}
```


#### Notes
- No additional allocations: parser just threads canonical pointers through AST.


### Semantic analysis in more detail: types and promotion
Types are interned so equality is pointer equality, and dense indices power fast tables.

Interning a composite type (e.g., function type):
```c
// Build a Type prototype (binary snapshot) and intern it
Type proto = {0};
proto.kind = TY_FUNC;
proto.u.func.param_count = n;
proto.u.func.params = params_canonical_ptrs; // array of canonical Type*
proto.u.func.ret = ret_type_canonical;

Slice s = { (const char*)&proto, (uint32_t)sizeof(Type) };
InternResult *ir = intern(TYPE_I, &s, NULL);
Type *T = (Type*)((Slice*)ir->key)->ptr; // canonical Type*
int handle = ir->entry->dense_index;     // dense handle
```

Type checks reduce to pointer compares:
```c
bool same = (lhs_type_ptr == rhs_type_ptr);
```

Promotion/operation tables index by dense handles:
```c
// Example: binary op result via a promotion matrix
int a = lhs_type_handle; // e.g., from lhs_ir->entry->dense_index
int b = rhs_type_handle; // ...
int res_handle = PROMO[OP_ADD][a][b];
if (res_handle < 0) report_type_error(...);
Type *res_type = handle_to_type_ptr(res_handle);
```


Benefits:
- O(1) type equality and memoization of constructed types (e.g., repeated func signatures).
- Dense indices enable compact arrays for promotions and traits.
- Arena-backed canonical data stays valid throughout analysis without copies.



## Core data structures
```c
typedef struct {
	void *key;      // canonical arena copy (e.g. Slice* or Type*)
	Entry *entry;   // metadata + dense_index
} InternResult;

typedef struct {
	void *meta;     // optional user metadata
	int dense_index;// 0..N-1 stable handle
} Entry;

typedef struct DenseArenaInterner {
	Arena   *arena;        // backing allocations
	HashMap *hashmap;      // key -> InternResult (content hash)
	DynArray *dense_array; // InternResult* in insertion order
	int dense_index_count; // number of unique entries
	void *(*copy_func)(Arena*, const void*, size_t); // canonical copier
	size_t (*hash_func)(void*);                     // hashing wrapper
	int    (*cmp_func)(void*, void*);               // equality wrapper
} DenseArenaInterner;
```
### InternResult
- key: canonical, arena-owned representation (e.g., for strings a Slice* whose .ptr is a NUL-terminated char*; for type snapshots a Slice* over the canonical bytes).
- entry: pointer to Entry carrying metadata and the stable dense index.

### Entry
- dense_index: 0..N-1 handle; use as an array index in side tables (promotion matrix, attributes, etc.).
- meta: optional user payload (e.g., TokenType for keywords or flags).

### DenseArenaInterner
- arena: storage for canonical keys and interner records (stable for the pass).
- hashmap: deduplicates by content; maps canonical key -> InternResult.
- dense_array: maps dense_index -> InternResult (in insertion order).
- copy/hash/cmp: pluggable behavior; ensure cmp examines exactly the bytes hashed and the bytes produced by copy.

## Core operations
- `intern_table_create(hashmap, arena, copy_func, hash_func, cmp_func)` – construct.
- `intern(interner, slice, meta)` – insert or fetch existing; returns `InternResult*`.
- `intern_idx(interner, slice, meta)` – same but returns dense index (int).
- `intern_ptr(interner, slice, meta)` – returns canonical key pointer only.
- `intern_peek(interner, slice)` – lookup without insert (NULL if absent).
- `interner_foreach(interner, callback, user)` – iterate dense order.
- `interner_get_cstr(interner, idx)` – convenience for string keys.
- `intern_table_destroy(interner, free_key, free_value)` – teardown (arena free if desired).


### Function pointer roles
- `copy_func` – How to make the canonical key (e.g., `string_copy_func` NUL-terminates; `binary_copy_func` copies raw bytes).
- `hash_func` – Hashing of the key for the HashMap (must match what `cmp_func` compares).
- `cmp_func` – Equality/ordering for keys (must consider the same bytes `hash_func` used).

## Typical usage

### 1) Identifiers/strings (common case)
```c
// Create a string interner for identifiers (stores one canonical copy per spelling)
HashMap *id_map = hashmap_create(128);
DenseArenaInterner *ID_I = intern_table_create(id_map, arena, string_copy_func, slice_hash, slice_cmp);

// Given two slices into the source buffer for an identifier
Slice str1 = { start_ptr1, (uint32_t)len1 };
InternResult *ir1 = intern(ID_I, &str1, NULL);

Slice str2 = { start_ptr2, (uint32_t)len2 };
InternResult *ir2 = intern(ID_I, &str2, NULL);

// Use cases
int handle1 = ir1->entry->dense_index;            // compact handle for side tables
int handle2 = ir2->entry->dense_index;            // compact handle for side tables

bool eq = handle1 == handle2; // True if same string

const char *cstr = interner_get_cstr(ID_I, handle); // Gets string out of arena
// Pointer equality across the compiler via ir->key (canonical)
```

### 2) Types as binary snapshots (semantic analysis)
```c
// Create a type interner using binary snapshots (user-provided hash/cmp over the snapshot)
HashMap *type_map = hashmap_create(128);
DenseArenaInterner *TYPE_I = intern_table_create(type_map, arena, binary_copy_func, type_hash, type_cmp);
// type_hash/type_cmp: wrappers you implement that hash/compare the snapshot Slice contents

// Example: build and intern a pointer type to canonical T
Type ptr_proto = { .kind = TY_PTR, .u.ptr.target = T };
Slice s = { (const char*)&ptr_proto, (uint32_t)sizeof(Type) };
InternResult *r = intern(TYPE_I, &s, NULL);
Type *ptr_type = (Type*)((Slice*)r->key)->ptr; // canonical Type*
int ptr_handle = r->entry->dense_index;        // dense index for tables

// Equality reduces to pointer compare
bool same = (ptr_type == some_other_canonical_type_ptr);

// Dense-index side tables (e.g., promotion matrix, attributes)
// attrs[ptr_handle] = ...;
```

### 3) Lookup without insert (keywords)
```c
// Pre-seed a keyword interner with string_copy_func
HashMap *kw_map = hashmap_create(64);
DenseArenaInterner *KW_I = intern_table_create(kw_map, arena, string_copy_func, slice_hash, slice_cmp);
// ...intern each keyword once with meta = (void*)(uintptr_t)TokenType ...

// At lex time, check if an identifier is a keyword without allocating
Slice ident = { start_ptr, (uint32_t)len };
InternResult *hit = intern_peek(KW_I, &ident);
if (hit) {
	TokenType tt = (TokenType)(uintptr_t)hit->entry->meta; // recognized keyword
}
```

## How it integrates
- **[Arena](arena.md)**: All canonical keys stored in arena so pointer identity equals structural equality.
- **[HashMap](hashmap.md)**: Prevents duplicates; maps slices to existing canonical entry if present.
- **[DynArray](dynarray.md)**: Dense ordering for iteration, maps dense index to pointer in arena of InternResult.

## Invariants
- Canonical data immutable after copy.
- Each dense index maps to exactly one canonical key.
- `intern_peek` never allocates; other intern calls allocate only on first occurrence.
- No removal API (handles remain stable for lifetime of pass).