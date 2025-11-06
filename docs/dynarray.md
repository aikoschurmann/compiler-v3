# DynArray

## What it is
Generic resizable array (vector) for fixed-size elements. Supports two allocation modes:
- Heap-backed (default): internal buffer grown via realloc.
- [Arena](arena.md)-backed: internal buffer allocated once (or grown) using `arena_alloc`; never individually freed.

## Core data structure
```c
typedef struct {
	void *data;        // element storage (heap or arena)
	size_t elem_size;  // bytes per element
	size_t count;      // current number of elements
	size_t capacity;   // allocated element capacity
	Arena *arena;      // non-NULL => arena-backed
} DynArray;
```

## Core operations
Heap-backed:
- `dynarray_init(da, elem_size)`
- `dynarray_reserve(da, min_capacity)`
- `dynarray_push_value(da, &value)` / `dynarray_push_uninit(da)`
- `dynarray_get(da, index)` / `dynarray_set(da, index, &value)`
- `dynarray_remove(da, index)` / `dynarray_pop(da)`
- `dynarray_free(da)` (frees buffer when heap-backed)

[Arena](arena.md)-backed:
- `dynarray_init_in_arena(da, arena, elem_size, initial_capacity)`
- `dynarray_reserve_in_arena(da, min_capacity)` (allocates new larger block; previous block not reclaimed until arena reset)


## Why use it
| Need | DynArray advantage |
|------|--------------------|
| Dynamic growth | Automatically expands capacity |
| Cache locality | Contiguous memory layout |
| Arena integration | Zero cost bulk free and reuse |


## Typical usage
Heap-backed example:
```c
DynArray arr; 
dynarray_init(&arr, sizeof(int));

// Option A: push by value (copies sizeof(int) bytes from &val)
for (int i = 0; i < 100; ++i) {
	int val = i;
	dynarray_push_value(&arr, &val); // OK: bytes are copied into the array
}

// Option B: push_uninit + write directly (avoids taking address of a loop var)
int *slot = dynarray_push_uninit(&arr);
if (slot) *slot = 1234;

int *p = dynarray_get(&arr, 10);
dynarray_free(&arr);
```

Struct elements example:
```c
typedef struct { int x, y; } Pt;
DynArray pts; dynarray_init(&pts, sizeof(Pt));
for (int i = 0; i < 3; ++i) {
	Pt *p = dynarray_push_uninit(&pts); // returns a writable slot
	p->x = i; p->y = i*i;
}
dynarray_free(&pts);
```

[Arena](arena.md)-backed example:
```c
Arena *A = arena_create(1<<20);
DynArray nodes; dynarray_init_in_arena(&nodes, A, sizeof(Node*), 32);
Node *n = make_node(A);
dynarray_push_ptr(&nodes, n);
// no dynarray_free needed; arena_destroy(A) cleans all
```

## Complexity
| Operation | Amortized |
|-----------|-----------|
| push | O(1) |
| get/set | O(1) |
| remove (unordered) | O(n) |
| reserve | O(n) when growing |

## Memory behavior
- Capacity grows (typically doubling) to keep amortized O(1) push.
- Arena-backed growth leaks old buffers until arena reset (acceptable for whole-pass lifetime).
- No per-element allocation overhead.


## Integration with other modules
- HashMap buckets are `DynArray` of `KeyValue` for collision chains.
- Interner dense array stores `InternResult*` pointers in a `DynArray` enabling direct index access.
- Parser stores lists (tokens, params, declarations) without writing separate list logic per element type.


## Cross reference
- `arena.md` for allocator semantics.
- `hashmap.md` for usage as bucket container.
- `interner.md` for storing canonical entries densely.
