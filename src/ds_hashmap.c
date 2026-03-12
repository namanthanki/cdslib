#include "ds/ds_hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DS_HASHMAP_INITIAL_CAPACITY 16
#define DS_HASHMAP_LOAD_FACTOR 0.75

typedef struct ds_hashmap_node {
    struct ds_hashmap_node *next;
    char data[];
} ds_hashmap_node_t;

struct ds_hashmap {
    ds_hashmap_node_t **buckets;
    size_t size;
    size_t capacity;
    size_t key_size;
    size_t value_size;

    ds_hash_fn hash_fn;
    ds_cmp_fn cmp_fn;

    void (*key_destructor)(void *);
    void (*value_destructor)(void *);
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_hashmap_t *ds_hashmap_create(
    size_t key_size,
    size_t value_size,
    ds_hash_fn hash_fn,
    ds_cmp_fn cmp_fn,
    void (*key_destructor)(void *),
    void (*value_destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    if (key_size == 0 || value_size == 0 || !hash_fn || !cmp_fn) return NULL;

    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_hashmap_t *map = (ds_hashmap_t *)alloc(sizeof(ds_hashmap_t));
    if (!map) return NULL;

    map->buckets = (ds_hashmap_node_t **)alloc(DS_HASHMAP_INITIAL_CAPACITY * sizeof(ds_hashmap_node_t *));
    if (!map->buckets) {
        dealloc(map);
        return NULL;
    }
    memset(map->buckets, 0, DS_HASHMAP_INITIAL_CAPACITY * sizeof(ds_hashmap_node_t *));

    map->size = 0;
    map->capacity = DS_HASHMAP_INITIAL_CAPACITY;
    map->key_size = key_size;
    map->value_size = value_size;
    map->hash_fn = hash_fn;
    map->cmp_fn = cmp_fn;
    map->key_destructor = key_destructor;
    map->value_destructor = value_destructor;
    map->allocator = alloc;
    map->deallocator = dealloc;

    return map;
}

void ds_hashmap_destroy(ds_hashmap_t *map) {
    if (!map) return;
    ds_hashmap_clear(map);
    map->deallocator(map->buckets);
    map->deallocator(map);
}

static ds_error_t ds_hashmap_rehash(ds_hashmap_t *map) {
    size_t new_capacity = map->capacity * 2;
    
    // Prevent integer overflow during allocation
    if (new_capacity > SIZE_MAX / sizeof(ds_hashmap_node_t *)) {
        return DS_ERR_OUT_OF_RANGE;
    }

    ds_hashmap_node_t **new_buckets = (ds_hashmap_node_t **)map->allocator(new_capacity * sizeof(ds_hashmap_node_t *));
    if (!new_buckets) return DS_ERR_ALLOC;
    memset(new_buckets, 0, new_capacity * sizeof(ds_hashmap_node_t *));

    for (size_t i = 0; i < map->capacity; i++) {
        ds_hashmap_node_t *curr = map->buckets[i];
        while (curr) {
            ds_hashmap_node_t *next = curr->next;
            size_t hash = map->hash_fn(curr->data) % new_capacity;
            curr->next = new_buckets[hash];
            new_buckets[hash] = curr;
            curr = next;
        }
    }

    map->deallocator(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
    return DS_SUCCESS;
}

ds_error_t ds_hashmap_insert(ds_hashmap_t *map, const void *key, const void *value) {
    if (!map || !key || !value) return DS_ERR_INVALID_ARG;

    if ((float)map->size / map->capacity >= DS_HASHMAP_LOAD_FACTOR) {
        ds_error_t err = ds_hashmap_rehash(map);
        if (err != DS_SUCCESS) return err;
    }

    size_t hash = map->hash_fn(key) % map->capacity;
    ds_hashmap_node_t *curr = map->buckets[hash];

    while (curr) {
        if (map->cmp_fn(curr->data, key) == 0) {
            if (map->value_destructor) {
                map->value_destructor(curr->data + map->key_size);
            }
            memcpy(curr->data + map->key_size, value, map->value_size);
            return DS_SUCCESS;
        }
        curr = curr->next;
    }

    ds_hashmap_node_t *new_node = (ds_hashmap_node_t *)map->allocator(sizeof(ds_hashmap_node_t) + map->key_size + map->value_size);
    if (!new_node) return DS_ERR_ALLOC;

    memcpy(new_node->data, key, map->key_size);
    memcpy(new_node->data + map->key_size, value, map->value_size);
    new_node->next = map->buckets[hash];
    map->buckets[hash] = new_node;
    map->size++;

    return DS_SUCCESS;
}

ds_error_t ds_hashmap_remove(ds_hashmap_t *map, const void *key, void *out_value) {
    if (!map || !key) return DS_ERR_INVALID_ARG;

    size_t hash = map->hash_fn(key) % map->capacity;
    ds_hashmap_node_t *curr = map->buckets[hash];
    ds_hashmap_node_t *prev = NULL;

    while (curr) {
        if (map->cmp_fn(curr->data, key) == 0) {
            if (prev) {
                prev->next = curr->next;
            } else {
                map->buckets[hash] = curr->next;
            }

            if (out_value) {
                memcpy(out_value, curr->data + map->key_size, map->value_size);
            } else if (map->value_destructor) {
                map->value_destructor(curr->data + map->key_size);
            }

            if (map->key_destructor) {
                map->key_destructor(curr->data);
            }

            map->deallocator(curr);
            map->size--;
            return DS_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
    }

    return DS_ERR_OUT_OF_RANGE;
}

ds_error_t ds_hashmap_get(const ds_hashmap_t *map, const void *key, void *out_value) {
    if (!map || !key || !out_value) return DS_ERR_INVALID_ARG;

    size_t hash = map->hash_fn(key) % map->capacity;
    ds_hashmap_node_t *curr = map->buckets[hash];

    while (curr) {
        if (map->cmp_fn(curr->data, key) == 0) {
            memcpy(out_value, curr->data + map->key_size, map->value_size);
            return DS_SUCCESS;
        }
        curr = curr->next;
    }

    return DS_ERR_OUT_OF_RANGE;
}

bool ds_hashmap_contains(const ds_hashmap_t *map, const void *key) {
    if (!map || !key) return false;

    size_t hash = map->hash_fn(key) % map->capacity;
    ds_hashmap_node_t *curr = map->buckets[hash];

    while (curr) {
        if (map->cmp_fn(curr->data, key) == 0) {
            return true;
        }
        curr = curr->next;
    }

    return false;
}

size_t ds_hashmap_size(const ds_hashmap_t *map) {
    return map ? map->size : 0;
}

void ds_hashmap_clear(ds_hashmap_t *map) {
    if (!map) return;

    for (size_t i = 0; i < map->capacity; i++) {
        ds_hashmap_node_t *curr = map->buckets[i];
        while (curr) {
            ds_hashmap_node_t *next = curr->next;
            if (map->key_destructor) {
                map->key_destructor(curr->data);
            }
            if (map->value_destructor) {
                map->value_destructor(curr->data + map->key_size);
            }
            map->deallocator(curr);
            curr = next;
        }
        map->buckets[i] = NULL;
    }
    map->size = 0;
}
