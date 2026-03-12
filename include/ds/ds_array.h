#ifndef DS_ARRAY_H
#define DS_ARRAY_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_array ds_array_t;

ds_array_t *ds_array_create(
    size_t capacity,
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_array_destroy(ds_array_t *arr);

ds_error_t ds_array_get(const ds_array_t *arr, size_t index, void *out_value);
ds_error_t ds_array_set(ds_array_t *arr, size_t index, const void *value);

size_t ds_array_capacity(const ds_array_t *arr);
void *ds_array_data(const ds_array_t *arr);

#define DS_ARRAY_DEFINE_TYPE(TYPE, SUFFIX)                      \
static inline ds_error_t                                        \
ds_array_get_##SUFFIX(const ds_array_t *arr, size_t index, TYPE *out_value) { \
    return ds_array_get(arr, index, out_value);                 \
}                                                               \
static inline ds_error_t                                        \
ds_array_set_##SUFFIX(ds_array_t *arr, size_t index, TYPE value) { \
    return ds_array_set(arr, index, &value);                    \
}

#endif /* DS_ARRAY_H */
