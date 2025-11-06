# HashMap

## What it is
An open-address style abstraction built with separate chaining using dynamic arrays:
- `bucket_count` buckets; each bucket is a small dynamic array of `KeyValue` pairs.
- User supplies `hash(void*)` and `cmp(void*, void*)` so map works with arbitrary key types.
- No automatic resizing unless you call `hashmap_rehash`.

## Core data structures
```c
typedef struct { void *key; void *value; } KeyValue;
typedef struct {
	DynArray *buckets;     // array of DynArray* buckets
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
size_t str_hash(void *k) { /* FNV or similar */ }
int str_cmp(void *a, void *b) { return strcmp(a, b); }

HashMap *map = hashmap_create(64);
hashmap_put(map, key, value, str_hash, str_cmp);
void *val = hashmap_get(map, key, str_hash, str_cmp);
hashmap_destroy(map, NULL, NULL); // if keys/values owned elsewhere
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
Trigger a rehash when `size / bucket_count` (load factor) exceeds ~0.75 for performance. The project currently leaves policy to the caller.

## Limitations
- No automatic growth (caller must call `hashmap_rehash`).
- Keys assumed stable (no mutation affecting their hash while stored).
- Requires explicit memory management for key/value if they were separately allocated destructors must be provided upon destroy of map.
