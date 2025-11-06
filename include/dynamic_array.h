#pragma once
#include <stddef.h>

#include "arena.h"

/* dynarray: generic vector of elements of fixed size. Can be heap-backed (default)
 * or arena-backed (if arena != NULL). When arena-backed, internal buffers are
 * allocated from the arena and not freed by dynarray_free. */
typedef struct {
    void *data;         /* pointer to element buffer (heap or arena) */
    size_t elem_size;   /* bytes per element */
    size_t count;       /* number of elements stored */
    size_t capacity;    /* capacity in elements */
    Arena *arena;       /* if non-NULL use arena_alloc for buffers, otherwise use heap */
} DynArray;

/* heap-backed API (existing behavior) */
void dynarray_init(DynArray *da, size_t elem_size);
void dynarray_free(DynArray *da);
int dynarray_reserve(DynArray *da, size_t min_capacity);
int dynarray_push_value(DynArray *da, const void *value);
void *dynarray_push_uninit(DynArray *da);
void dynarray_pop(DynArray *da);
void dynarray_remove(DynArray *da, size_t index);
void *dynarray_get(DynArray *da, size_t index);
int dynarray_set(DynArray *da, size_t index, const void *value);

/* arena-backed initializers: call instead of dynarray_init to place backing
 * buffers in the provided arena. The DynArray struct itself can be allocated
 * in arena as well (optional). */
void dynarray_init_in_arena(DynArray *da, Arena *arena, size_t elem_size, size_t initial_capacity);

/* reserve for arena-backed arrays. Works like dynarray_reserve but uses arena_alloc. */
int dynarray_reserve_in_arena(DynArray *da, size_t min_capacity);

/* Convenience: push pointer value as element (if elem_size == sizeof(void*)) */
static inline void dynarray_push_ptr(DynArray *da, void *p) {
    dynarray_push_value(da, &p);
}
