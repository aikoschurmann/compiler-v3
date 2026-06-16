#include "datastructures/hash_map.h"
#include <stdlib.h>
#include <string.h>

#define TOMBSTONE ((void*)-1)

HashMap* hashmap_create(Arena *arena, size_t initial_capacity) {
    if (initial_capacity < 8) initial_capacity = 8;
    
    HashMap *map;
    if (arena) {
        map = arena_alloc(arena, sizeof(HashMap));
    } else {
        map = calloc(1, sizeof(HashMap));
    }
    if (!map) return NULL;

    map->arena = arena;
    map->capacity = initial_capacity;
    map->size = 0;
    map->tombstones = 0;

    if (arena) {
        map->entries = arena_calloc(arena, sizeof(KeyValue) * initial_capacity);
    } else {
        map->entries = calloc(initial_capacity, sizeof(KeyValue));
    }

    if (!map->entries) {
        if (!arena) free(map);
        return NULL;
    }

    return map;
}

void hashmap_destroy(
    HashMap* map,
    void (*free_key)(void*),
    void (*free_value)(void*)
) {
    if (!map) return;

    if (free_key || free_value) {
        for (size_t i = 0; i < map->capacity; i++) {
            void *k = map->entries[i].key;
            if (k != NULL && k != TOMBSTONE) {
                if (free_key) free_key(k);
                if (free_value && map->entries[i].value) free_value(map->entries[i].value);
            }
        }
    }

    if (!map->arena) {
        free(map->entries);
        free(map);
    }
}

bool hashmap_rehash(
    HashMap* map,
    size_t new_capacity,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || new_capacity == 0 || !hash || !cmp) return false;

    KeyValue *new_entries;
    if (map->arena) {
        new_entries = arena_calloc(map->arena, sizeof(KeyValue) * new_capacity);
    } else {
        new_entries = calloc(new_capacity, sizeof(KeyValue));
    }
    if (!new_entries) return false;

    for (size_t i = 0; i < map->capacity; i++) {
        void *k = map->entries[i].key;
        if (k != NULL && k != TOMBSTONE) {
            size_t h = hash(k);
            size_t index = h % new_capacity;
            
            while (new_entries[index].key != NULL) {
                index = (index + 1) % new_capacity;
            }
            new_entries[index] = map->entries[i];
        }
    }

    if (!map->arena) {
        free(map->entries);
    }

    map->entries = new_entries;
    map->capacity = new_capacity;
    map->tombstones = 0;
    return true;
}

bool hashmap_put(
    HashMap* map,
    void* key,
    void* value,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || !key || !hash || !cmp) return false;

    // Resize if load factor > 0.75 (counting tombstones as used)
    if (map->size + map->tombstones >= (map->capacity * 3) / 4) {
        size_t new_cap = map->capacity * 2;
        hashmap_rehash(map, new_cap, hash, cmp);
    }

    size_t h = hash(key);
    size_t index = h % map->capacity;
    size_t first_tombstone = (size_t)-1;

    for (size_t i = 0; i < map->capacity; i++) {
        void *k = map->entries[index].key;
        if (k == NULL) {
            // Found empty slot
            if (first_tombstone != (size_t)-1) {
                index = first_tombstone;
                map->tombstones--;
            }
            map->entries[index].key = key;
            map->entries[index].value = value;
            map->size++;
            return true;
        } else if (k == TOMBSTONE) {
            if (first_tombstone == (size_t)-1) {
                first_tombstone = index;
            }
        } else if (cmp(k, key) == 0) {
            // Update existing
            map->entries[index].value = value;
            return true;
        }
        index = (index + 1) % map->capacity;
    }

    // Should never reach here if resizing correctly
    return false;
}

void* hashmap_get(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || !key || !hash || !cmp) return NULL;

    size_t h = hash(key);
    size_t index = h % map->capacity;

    for (size_t i = 0; i < map->capacity; i++) {
        void *k = map->entries[index].key;
        if (k == NULL) {
            return NULL;
        } else if (k != TOMBSTONE && cmp(k, key) == 0) {
            return map->entries[index].value;
        }
        index = (index + 1) % map->capacity;
    }

    return NULL;
}

bool hashmap_remove(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*),
    void (*free_key)(void*),
    void (*free_value)(void*)
) {
    if (!map || !key || !hash || !cmp) return false;

    size_t h = hash(key);
    size_t index = h % map->capacity;

    for (size_t i = 0; i < map->capacity; i++) {
        void *k = map->entries[index].key;
        if (k == NULL) {
            return false;
        } else if (k != TOMBSTONE && cmp(k, key) == 0) {
            if (free_key) free_key(k);
            if (free_value && map->entries[index].value) free_value(map->entries[index].value);
            
            map->entries[index].key = TOMBSTONE;
            map->entries[index].value = NULL;
            map->size--;
            map->tombstones++;
            return true;
        }
        index = (index + 1) % map->capacity;
    }

    return false;
}

void hashmap_foreach(
    HashMap* map,
    void (*callback)(void*, void*)
) {
    if (!map || !callback) return;

    for (size_t i = 0; i < map->capacity; i++) {
        void *k = map->entries[i].key;
        if (k != NULL && k != TOMBSTONE) {
            callback(k, map->entries[i].value);
        }
    }
}

size_t hashmap_size(HashMap* map) {
    return map ? map->size : 0;
}
