#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Standard heap-backed init  */
void dynarray_init(DynArray *da, size_t elem_size) {
    if (!da) return;
    da->data = NULL;
    da->elem_size = elem_size;
    da->count = 0;
    da->capacity = 0;
    da->arena = NULL;
}

void dynarray_free(DynArray *da) {
    if (!da) return;
    if (da->arena == NULL) {
        /* heap-backed: free the buffer */
        free(da->data);
    } else {
        /* arena-backed: nothing to free; arena owns the memory */
        (void)da;
    }
    da->data = NULL;
    da->count = 0;
    da->capacity = 0;
    da->elem_size = 0;
    da->arena = NULL;
}

/* Reserve using heap-backed realloc (old behavior) */
int dynarray_reserve(DynArray *da, size_t min_capacity) {
    if (!da) return -1;
    if (da->capacity >= min_capacity) return 0;
    /* If this is an arena-backed DynArray, delegate to arena-reserve */
    if (da->arena) return dynarray_reserve_in_arena(da, min_capacity);

    size_t newcap = da->capacity ? da->capacity * 2 : 4;
    while (newcap < min_capacity) newcap *= 2;
    void *newbuf = realloc(da->data, newcap * da->elem_size);
    if (!newbuf) return -1;
    da->data = newbuf;
    da->capacity = newcap;
    return 0;
}

/* Reserve using arena allocations. Old buffers remain in arena. */
int dynarray_reserve_in_arena(DynArray *da, size_t min_capacity) {
    if (!da || !da->arena) return -1;
    if (da->capacity >= min_capacity) return 0;

    size_t newcap = da->capacity ? da->capacity * 2 : 8;
    while (newcap < min_capacity) newcap *= 2;

    void *newbuf = arena_alloc(da->arena, newcap * da->elem_size);
    if (!newbuf) return -1;

    if (da->data && da->count > 0) {
        memcpy(newbuf, da->data, da->count * da->elem_size);
    }

    da->data = newbuf;
    da->capacity = newcap;
    return 0;
}

/* push value (works for both modes) */
int dynarray_push_value(DynArray *da, const void *value) {
    if (!da) return -1;
    if (dynarray_reserve(da, da->count + 1) != 0) return -1;
    void *dst = (char*)da->data + da->count * da->elem_size;
    da->count += 1;
    if (value) {
        memcpy(dst, value, da->elem_size);
    } else {
        memset(dst, 0, da->elem_size);
    }
    return 0;
}

/* returns pointer to uninitialized slot (caller must fill) */
void *dynarray_push_uninit(DynArray *da) {
    if (!da) return NULL;
    if (dynarray_reserve(da, da->count + 1) != 0) return NULL;
    void *slot = (char*)da->data + da->count * da->elem_size;
    da->count += 1;
    return slot;
}

void dynarray_pop(DynArray *da) {
    if (!da) return;
    if (da->count == 0) return;
    da->count -= 1;
}

/* remove element by shifting later elements left */
void dynarray_remove(DynArray *da, size_t index) {
    if (!da) return;
    if (index >= da->count) return;
    if (index < da->count - 1) {
        void *dst = (char*)da->data + index * da->elem_size;
        void *src = (char*)da->data + (index + 1) * da->elem_size;
        size_t n = da->count - index - 1;
        memmove(dst, src, n * da->elem_size);
    }
    da->count -= 1;
}

void *dynarray_get(DynArray *da, size_t index) {
    if (!da) return NULL;
    if (index >= da->count) return NULL;
    return (char*)da->data + index * da->elem_size;
}

int dynarray_set(DynArray *da, size_t index, const void *value) {
    if (!da || !value) return -1;
    if (index >= da->count) return -1;
    void *dst = (char*)da->data + index * da->elem_size;
    memcpy(dst, value, da->elem_size);
    return 0;
}

/* arena-backed initializer */
void dynarray_init_in_arena(DynArray *da, Arena *arena, size_t elem_size, size_t initial_capacity) {
    if (!da) return;
    da->data = NULL;
    da->elem_size = elem_size;
    da->count = 0;
    da->capacity = 0;
    da->arena = arena;
    if (initial_capacity > 0) {
        /* this uses arena_alloc */
        dynarray_reserve_in_arena(da, initial_capacity);
    }
}
