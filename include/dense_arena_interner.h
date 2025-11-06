#pragma once

#include "arena.h"
#include "hash_map.h"
#include "dynamic_array.h"
#include "utils.h"

typedef struct {
    Arena *arena;
    HashMap *hashmap;
    DynArray *dense_array;
    int dense_index_count;
    
    // Generic copy function for data
    void* (*copy_func)(Arena *arena, const void *data, size_t len);
    
    // Hash and comparison functions for this interner
    size_t (*hash_func)(void *key);
    int (*cmp_func)(void *a, void *b);
} DenseArenaInterner;

typedef struct {
    void* meta;
    int dense_index;
} Entry;

typedef struct {
    void *key;       // canonical pointer (arena copy)
    Entry *entry;    // metadata + dense_index
} InternResult;


// Copy function signature - returns arena-allocated canonical copy
typedef void* (*CopyFunc)(Arena *arena, const void *data, size_t len);

// Predefined copy functions
void* string_copy_func(Arena *arena, const void *data, size_t len);  // null-terminate
void* binary_copy_func(Arena *arena, const void *data, size_t len);  // exact copy

DenseArenaInterner* intern_table_create(HashMap *hashmap, Arena *arena, CopyFunc copy_func, 
                                       size_t (*hash_func)(void*), int (*cmp_func)(void*, void*));
void intern_table_destroy(DenseArenaInterner *interner, void (*free_key)(void*), void (*free_value)(void*));
InternResult *intern(DenseArenaInterner *interner, Slice *slice, void* meta);

void *intern_ptr(DenseArenaInterner *interner, Slice *slice, void* meta);
int  intern_idx(DenseArenaInterner *interner, Slice *slice, void* meta);

/* Lookup without inserting — returns existing InternResult* or NULL */
InternResult* intern_peek(DenseArenaInterner *interner, Slice *slice);

/* Convenience: wraps default slice_hash/slice_cmp - DEPRECATED, use intern_idx instead */
int intern_or_get_idx(DenseArenaInterner *I, Slice *s, void *meta);

/* --- Accessors --- */
/* Return canonical C string (null-terminated) for dense index, or NULL if invalid */
const char *interner_get_cstr(DenseArenaInterner *I, int idx);


/* Iterate over all interned entries in dense order. 
 * Callback receives:
 *   idx   : dense index
 *   key   : canonical Slice* (arena-owned, stable pointer)
 *   meta  : user metadata
 *   user  : user-supplied context pointer
 */
typedef void (*InternerIterFn)(int idx, const Slice *key, void *meta, void *user);

void interner_foreach(const DenseArenaInterner *I,
                      InternerIterFn cb,
                      void *user);