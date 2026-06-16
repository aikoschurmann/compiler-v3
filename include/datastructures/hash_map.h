#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "arena.h"
#include "core/utils.h"

/* -----------------------------
   HashMap API (Open Addressing)
   ----------------------------- */

typedef struct {
    void *key;
    void *value;
} KeyValue;

typedef struct {
    Arena *arena;          /* If NULL, uses malloc/free */
    KeyValue *entries;     /* Contiguous array of KeyValue pairs */
    size_t capacity;       /* Number of slots in entries */
    size_t size;           /* Number of active elements */
    size_t tombstones;     /* Number of deleted slots */
} HashMap;

/* Constructor / Destructor */
HashMap* hashmap_create(Arena *arena, size_t initial_capacity);

void hashmap_destroy(
    HashMap* map,
    void (*free_key)(void*),
    void (*free_value)(void*)
);

/* Insert or update */
bool hashmap_put(
    HashMap* map,
    void* key,
    void* value,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
);

/* Lookup */
void* hashmap_get(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
);

/* Remove */
bool hashmap_remove(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*),
    void (*free_key)(void*),
    void (*free_value)(void*)
);

/* Resize / Rehash */
bool hashmap_rehash(
    HashMap* map,
    size_t new_capacity,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
);

/* Utility */
size_t hashmap_size(HashMap* map);

void hashmap_foreach(
    HashMap* map,
    void (*func)(void* key, void* value)
);
