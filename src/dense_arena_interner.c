// dense_arena_interner.c (optimized: single-block arena allocations)
#include "dense_arena_interner.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "dynamic_array.h"


/* Predefined copy functions */
void* string_copy_func(Arena *arena, const void *data, size_t len) {
    char *buf = arena_alloc(arena, len + 1);
    if (!buf) return NULL;
    memcpy(buf, data, len);
    buf[len] = '\0';  // null-terminate for strings
    return buf;
}

void* binary_copy_func(Arena *arena, const void *data, size_t len) {
    void *buf = arena_alloc(arena, len);
    if (!buf) return NULL;
    memcpy(buf, data, len);  // exact copy, no null termination
    return buf;
}

/* Create interner stored in arena. */
DenseArenaInterner* intern_table_create(HashMap *hashmap, Arena *arena, CopyFunc copy_func,
                                       size_t (*hash_func)(void*), int (*cmp_func)(void*, void*)){
    if (!hashmap || !arena || !copy_func || !hash_func || !cmp_func) return NULL;

    DenseArenaInterner *interner = arena_alloc(arena, sizeof(DenseArenaInterner));
    if (!interner) return NULL;

    interner->arena = arena;
    interner->hashmap = hashmap;
    interner->dense_index_count = 0;
    interner->copy_func = copy_func;
    interner->hash_func = hash_func;
    interner->cmp_func = cmp_func;

    /* allocate the DynArray struct itself in the arena */
    interner->dense_array = arena_alloc(arena, sizeof(DynArray));
    if (!interner->dense_array) {
        return NULL;
    }

    /* initialize to store InternResult* pointers in arena-backed buffer. */
    dynarray_init_in_arena(interner->dense_array, arena, sizeof(InternResult*), 0);

    return interner;
}

void intern_table_destroy(DenseArenaInterner *interner, void (*free_key)(void*), void (*free_value)(void*)) {
    if (!interner) return;

    hashmap_destroy(interner->hashmap, free_key, free_value);

    /* dynarray_free with arena-backed arrays is a noop for buffer free (defensive). */
    if (interner->dense_array) {
        dynarray_free(interner->dense_array);
        interner->dense_array = NULL;
    }
}

/* --- Generic intern function (returns InternResult* on success) --- */
InternResult* intern(DenseArenaInterner *interner,
                     Slice *slice,
                     void *meta)
{
    if (!interner || !slice || !slice->ptr || slice->len == 0) return NULL;

    /* Lookup existing entry */
    InternResult *found = hashmap_get(interner->hashmap, slice, interner->hash_func, interner->cmp_func);
    if (found) return found;

    /* Allocate each component separately to ensure proper alignment */
    Slice *key_slice = arena_alloc(interner->arena, sizeof(Slice));
    if (!key_slice) return NULL;
    
    InternResult *res = arena_alloc(interner->arena, sizeof(InternResult));
    if (!res) return NULL;
    
    Entry *ent = arena_alloc(interner->arena, sizeof(Entry));
    if (!ent) return NULL;

    /* Use the copy function to create canonical copy */
    void *canonical_data = interner->copy_func(interner->arena, slice->ptr, slice->len);
    if (!canonical_data) return NULL;

    key_slice->ptr = canonical_data;
    key_slice->len = slice->len;

    ent->meta = meta;
    ent->dense_index = interner->dense_index_count;

    res->entry = ent;
    res->key = key_slice;

    /* Insert into hashmap using the arena-allocated key_slice */
    hashmap_put(interner->hashmap, key_slice, res, interner->hash_func, interner->cmp_func);

    /* Push pointer to InternResult* into dense array */
    InternResult *res_ptr = res;
    if (dynarray_push_value(interner->dense_array, &res_ptr) != 0) {
        /* push failed; can't free arena allocations, return error */
        return NULL;
    }

    interner->dense_index_count++;
    return res;
}

/* Return canonical key pointer (here: Slice*) or NULL */
void* intern_ptr(DenseArenaInterner *I, Slice* slice, void *meta) {
    InternResult *r = intern(I, slice, meta);
    if (!r) return NULL;
    return r->key;
}

/* Return dense index or -1 on error */
int intern_idx(DenseArenaInterner *I, Slice* slice, void *meta) {
    InternResult *r = intern(I, slice, meta);
    if (!r) return -1;
    return r->entry->dense_index;
}

InternResult* intern_peek(DenseArenaInterner *interner, Slice *slice)
{
    if (!interner || !slice || !slice->ptr || slice->len == 0) return NULL;

    /* Lookup existing entry without inserting */
    return hashmap_get(interner->hashmap, slice, interner->hash_func, interner->cmp_func);
}

/* Return dense index for slice, or -1 on error. DEPRECATED - use intern_idx instead */
int intern_or_get_idx(DenseArenaInterner *I, Slice *s, void *meta) {
    if (!I || !s) return -1;
    return intern_idx(I, s, meta);
}

/* Return canonical C string for a dense index (for printing). Returns NULL for invalid idx. */
const char *interner_get_cstr(DenseArenaInterner *I, int idx) {
    if (!I) return NULL;
    if (idx < 0 || idx >= I->dense_index_count) return NULL;
    if (!I->dense_array) return NULL;

    size_t count = I->dense_array->count;
    if ((size_t)idx >= count) return NULL;

    void *elem_ptr = dynarray_get(I->dense_array, (size_t)idx);
    if (!elem_ptr) return NULL;

    InternResult *res = *(InternResult **)elem_ptr;
    if (!res || !res->key) return NULL;

    Slice *ks = (Slice *)res->key;
    return ks->ptr;
}

void interner_foreach(const DenseArenaInterner *I,
                      InternerIterFn cb,
                      void *user)
{
    if (!I || !cb) return;
    for (size_t i = 0; i < I->dense_array->count; i++) {
        InternResult *res = *(InternResult**)dynarray_get(I->dense_array, i);
        cb(res->entry->dense_index, res->key, res->entry->meta, user);
    }
}
