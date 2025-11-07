# HashMap

[← Back to docs index](./README.md)

## What it is
A separate-chaining hash map backed by dynamic arrays:
- `bucket_count` buckets; each bucket is a `DynArray` of `KeyValue` pairs.
- Caller supplies `hash(void*)` and `cmp(void*, void*)` for arbitrary key types.
- No automatic resizing; call `hashmap_rehash` when you decide to grow.

## Core data structures
```c
typedef struct { void *key; void *value; } KeyValue;
typedef struct {
	DynArray *buckets;     // array of buckets; each bucket is a DynArray of KeyValue
	size_t bucket_count;   // number of buckets
	size_t size;           // total key-value pairs
} HashMap;
```

## Core operations
- `hashmap_create(bucket_count)` – allocate buckets.
- `hashmap_put(map, key, value, hash, cmp)` – insert or update.
- `hashmap_get(map, key, hash, cmp)` – lookup returns value or NULL.
- `hashmap_remove(map, key, hash, cmp, free_key, free_value)` – delete a key.
- `hashmap_rehash(map, new_bucket_count, hash, cmp)` – resize & redistribute.
- `hashmap_foreach(map, fn)` – iterate all pairs.
- `hashmap_size(map)` – number of stored entries.
- `hashmap_destroy(map, free_key, free_value)` – free buckets + run destructors.

## Why use it
| Need | HashMap advantage |
|------|--------------------|
| Fast average lookup | O(1) expected with decent hash spread |
| Flexible keys | User-provided hash + cmp functions |
| Low overhead buckets | Buckets are dynamic arrays (contiguous) |
| Controlled resizing | Rehash only when you decide |
| Integration | Used as backing for [dense arena interner](interner.md) hashing |

## Typical usage
```c
HashMap *map = hashmap_create(64);

// Keys must be stable while in the map (e.g., allocated in an arena or interned)
extern size_t slice_hash(void*);
extern int slice_cmp(void*, void*);

Slice *k = arena_alloc(A, sizeof *k);
*k = (Slice){ .ptr = name_ptr, .len = (uint32_t)name_len };
hashmap_put(map, k, value_ptr, slice_hash, slice_cmp);
void *val = hashmap_get(map, k, slice_hash, slice_cmp);


// Destruction: pass destructors if the map owns keys/values; otherwise NULLs
hashmap_destroy(map, /*free_key*/NULL, /*free_value*/NULL);
```

## Complexity characteristics
| Operation | Average | Worst (pathological hashing) |
|-----------|---------|-------------------------------|
| put/get/remove | O(1) | O(n) in a single bucket |
| rehash | O(n) | O(n) |

## Memory behavior
- Each bucket is a [DynArray](dynarray.md) that grows when full.
- No per-entry malloc beyond dynarray growth; keys/values lifetimes are caller-managed.
- Rehash allocates a new buckets array and reinserts all pairs.


## When to rehash
Trigger a rehash when `size / bucket_count` (load factor) exceeds ~0.75 for performance. A simple check is `if (size * 4 >= 3 * bucket_count) rehash(...)`. Policy is left to the caller.

## Limitations
- No automatic growth (caller must call `hashmap_rehash`).
- Keys assumed stable (no mutation affecting their hash while stored).
- If the map owns keys/values, provide destructors to `hashmap_destroy`; otherwise pass NULLs.
