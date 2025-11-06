# Dense Arena Interner

## What it is
Canonicalization + indexing layer built on top of:
- [Arena allocator](arena.md) for stable storage & bulk lifetime.
- [HashMap](hashmap.md) for fast content-based lookup.
- [DynArray](dynarray.md) for dense ordered list of interned entries.

You provide a prototype (wrapped as `Slice`); the interner returns a canonical pointer and a small integer handle. Identical content is deduplicated.

# Why we need an interner
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

Benefits:
- Single hash+lookup per identifier vs many `strncmp` along a keyword list.
- Pointer equality for later symbol table operations (parser / semantic phases reuse `tok.record`).
- Metadata lets you attach TokenType or other flags without a separate map.



## Core data structures (conceptual)
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

## Core operations
- `intern_table_create(hashmap, arena, copy_func, hash_func, cmp_func)` – construct.
- `intern(interner, slice, meta)` – insert or fetch existing; returns `InternResult*`.
- `intern_idx(interner, slice, meta)` – same but returns dense index (int).
- `intern_ptr(interner, slice, meta)` – returns canonical key pointer only.
- `intern_peek(interner, slice)` – lookup without insert (NULL if absent).
- `interner_foreach(interner, callback, user)` – iterate dense order.
- `interner_get_cstr(interner, idx)` – convenience for string keys.
- `intern_table_destroy(interner, free_key, free_value)` – teardown (arena free if desired).

## Why use it
| Need | Interner advantage |
|------|--------------------|
| Fast equality | Pointer compare instead of deep compare/strcmp |
| Deduplication | One canonical copy per unique value |
| Dense indexing | Direct array lookups (promotion matrix, symbol tables) |
| Stable lifetime | Arena guarantees immovable pointers |
| Pluggable types | Custom hash/copy/equality wrappers per domain |

## Typical usage
```c
// Prepare interner for Types
HashMap *type_map = hashmap_create(64);
DenseArenaInterner *TI = intern_table_create(type_map, arena, type_copy_func, type_hash_wrapper, type_cmp_wrapper);

Type proto = { .kind = TY_PTR, .u.ptr.target = some_other_type };
Slice s = { .ptr = (const char*)&proto, .len = sizeof(Type) };
InternResult *r = intern(TI, &s, NULL);
Type *canonical = (Type*)((Slice*)r->key)->ptr; // canonical, stable
int handle = r->entry->dense_index;             // small integer handle
```

## How it integrates
- **Arena**: All canonical keys stored in arena so pointer identity equals structural equality.
- **HashMap**: Prevents duplicates; maps slices to existing canonical entry if present.
- **DynArray**: Dense ordering for iteration, maps dense index to pointer in arena of InternResult.

## Invariants
- Canonical data immutable after copy.
- Each dense index maps to exactly one canonical key.
- `intern_peek` never allocates; other intern calls allocate only on first occurrence.
- No removal API (handles remain stable for lifetime of pass).