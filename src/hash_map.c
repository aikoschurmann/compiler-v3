// hash_map.c  -- corrected and defensive version

#include "hash_map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

HashMap* hashmap_create(size_t bucket_count) {
    if (bucket_count == 0) bucket_count = 64; // default
    HashMap *map = calloc(1, sizeof(HashMap));
    if (!map) return NULL;

    /* calloc so each DynArray struct is zeroed (safe for dynarray_init to run). */
    map->buckets = calloc(bucket_count, sizeof(DynArray));
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    for (size_t i = 0; i < bucket_count; i++) {
        /* initialize each bucket to hold KeyValue elements */
        dynarray_init(&map->buckets[i], sizeof(KeyValue));
    }

    map->bucket_count = bucket_count;
    map->size = 0;
    return map;
}

void hashmap_destroy(
    HashMap* map,
    void (*free_key)(void*),
    void (*free_value)(void*)
) {
    if (!map) return;

    for (size_t i = 0; i < map->bucket_count; i++) {
        DynArray *bucket = &map->buckets[i];
        /* protect against uninitialized bucket */
        if (!bucket) continue;
        for (size_t j = 0; j < bucket->count; j++) {
            KeyValue *kv = (KeyValue*)dynarray_get(bucket, j);
            if (!kv) continue;
            if (free_key) free_key(kv->key);
            if (free_value) free_value(kv->value);
        }
        dynarray_free(bucket);
    }
    free(map->buckets);
    free(map);
}

/* Helper: rehash into a newly allocated buckets array */
bool hashmap_rehash(
    HashMap* map,
    size_t new_bucket_count,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || new_bucket_count == 0 || !hash || !cmp) return false;

    DynArray *new_buckets = calloc(new_bucket_count, sizeof(DynArray));
    if (!new_buckets) return false;

    /* initialize new buckets */
    for (size_t i = 0; i < new_bucket_count; i++) {
        dynarray_init(&new_buckets[i], sizeof(KeyValue));
    }

    /* Reinsert all key-value pairs into new buckets (copy KeyValue values) */
    for (size_t i = 0; i < map->bucket_count; i++) {
        DynArray *bucket = &map->buckets[i];
        if (!bucket) continue;
        for (size_t j = 0; j < bucket->count; j++) {
            KeyValue *old_kv = (KeyValue*)dynarray_get(bucket, j);
            if (!old_kv) continue;

            /* copy the key/value pair (value is the pointer stored in old_kv->value) */
            KeyValue kv_copy;
            kv_copy.key = old_kv->key;
            kv_copy.value = old_kv->value;

            size_t new_index = hash(kv_copy.key) % new_bucket_count;
            if (dynarray_push_value(&new_buckets[new_index], &kv_copy) != 0) {
                /* Cleanup on failure */
                for (size_t k = 0; k < new_bucket_count; k++) {
                    dynarray_free(&new_buckets[k]);
                }
                free(new_buckets);
                return false; // OOM
            }
        }
    }

    /* Free old buckets */
    for (size_t i = 0; i < map->bucket_count; i++) {
        dynarray_free(&map->buckets[i]);
    }
    free(map->buckets);

    map->buckets = new_buckets;
    map->bucket_count = new_bucket_count;
    /* map->size remains the same (we copied all items) */
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

    /* Resize when load factor > 0.75 */
    if (map->size >= (map->bucket_count * 3) / 4) {
        size_t new_bucket_count = map->bucket_count * 2;
        if (!hashmap_rehash(map, new_bucket_count, hash, cmp)) {
            /* Rehash failed (OOM) — continue with current size but insertion may be slower */
        }
    }

    size_t bucket_index = hash(key) % map->bucket_count;
    DynArray *bucket = &map->buckets[bucket_index];

    /* Check if key already exists (cmp==0 means equal) */
    for (size_t i = 0; i < bucket->count; i++) {
        KeyValue *kv = (KeyValue*)dynarray_get(bucket, i);
        if (kv && cmp(kv->key, key) == 0) {
            /* Update existing value */
            kv->value = value;
            return true;
        }
    }

    /* Insert new key-value pair (copy struct into dynarray) */
    KeyValue kv = {key, value};
    if (dynarray_push_value(bucket, &kv) != 0) {
        return false; // OOM
    }

    map->size++;
    return true;
}

void* hashmap_get(
    HashMap* map,
    void* key,
    size_t (*hash)(void*),
    int (*cmp)(void*, void*)
) {
    if (!map || !key || !hash || !cmp) return NULL;

    size_t bucket_index = hash(key) % map->bucket_count;
    DynArray *bucket = &map->buckets[bucket_index];

    for (size_t i = 0; i < bucket->count; i++) {
        KeyValue *kv = (KeyValue*)dynarray_get(bucket, i);
        if (kv && cmp(kv->key, key) == 0) {
            return kv->value; // Found
        }
    }
    return NULL; // Not found
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

    size_t bucket_index = hash(key) % map->bucket_count;
    DynArray *bucket = &map->buckets[bucket_index];

    for (size_t i = 0; i < bucket->count; i++) {
        KeyValue *kv = (KeyValue*)dynarray_get(bucket, i);
        if (kv && cmp(kv->key, key) == 0) {
            if (free_key) free_key(kv->key);
            if (free_value) free_value(kv->value);

            dynarray_remove(bucket, i);
            map->size--;
            return true;
        }
    }
    return false;
}

void hashmap_foreach(
    HashMap* map,
    void (*callback)(void*, void*)
) {
    if (!map || !callback) return;

    for (size_t i = 0; i < map->bucket_count; i++) {
        DynArray *bucket = &map->buckets[i];
        for (size_t j = 0; j < bucket->count; j++) {
            KeyValue *kv = (KeyValue*)dynarray_get(bucket, j);
            if (kv) callback(kv->key, kv->value);
        }
    }
}

size_t hashmap_size(HashMap* map) {
    return map ? map->size : 0;
}
