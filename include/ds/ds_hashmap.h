#ifndef DS_HASHMAP_H
#define DS_HASHMAP_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_hashmap ds_hashmap_t;

typedef size_t (*ds_hash_fn)(const void *key);
typedef int (*ds_cmp_fn)(const void *key1, const void *key2);

ds_hashmap_t *ds_hashmap_create(
    size_t key_size,
    size_t value_size,
    ds_hash_fn hash_fn,
    ds_cmp_fn cmp_fn,
    void (*key_destructor)(void *),
    void (*value_destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_hashmap_destroy(ds_hashmap_t *map);

ds_error_t ds_hashmap_insert(ds_hashmap_t *map, const void *key, const void *value);
ds_error_t ds_hashmap_remove(ds_hashmap_t *map, const void *key, void *out_value);
ds_error_t ds_hashmap_get(const ds_hashmap_t *map, const void *key, void *out_value);
bool ds_hashmap_contains(const ds_hashmap_t *map, const void *key);

size_t ds_hashmap_size(const ds_hashmap_t *map);
void ds_hashmap_clear(ds_hashmap_t *map);

#define DS_HASHMAP_DEFINE_TYPE(KEY_TYPE, VAL_TYPE, SUFFIX)      \
static inline ds_error_t                                        \
ds_hashmap_insert_##SUFFIX(ds_hashmap_t *map, KEY_TYPE key, VAL_TYPE value) { \
    return ds_hashmap_insert(map, &key, &value);                \
}                                                               \
static inline ds_error_t                                        \
ds_hashmap_remove_##SUFFIX(ds_hashmap_t *map, KEY_TYPE key, VAL_TYPE *out_value) { \
    return ds_hashmap_remove(map, &key, out_value);             \
}                                                               \
static inline ds_error_t                                        \
ds_hashmap_get_##SUFFIX(const ds_hashmap_t *map, KEY_TYPE key, VAL_TYPE *out_value) { \
    return ds_hashmap_get(map, &key, out_value);                \
}                                                               \
static inline bool                                              \
ds_hashmap_contains_##SUFFIX(const ds_hashmap_t *map, KEY_TYPE key) { \
    return ds_hashmap_contains(map, &key);                      \
}

#endif /* DS_HASHMAP_H */
