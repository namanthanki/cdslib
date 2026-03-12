#ifndef DS_VECTOR_H
#define DS_VECTOR_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_vector ds_vector_t;

ds_vector_t *ds_vector_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_vector_destroy(ds_vector_t *v);

ds_error_t ds_vector_push_back(ds_vector_t *v, const void *value);
ds_error_t ds_vector_pop_back(ds_vector_t *v, void *out_value);
ds_error_t ds_vector_insert(ds_vector_t *v, size_t index, const void *value);
ds_error_t ds_vector_remove(ds_vector_t *v, size_t index, void *out_value);
ds_error_t ds_vector_get(const ds_vector_t *v, size_t index, void *out_value);
ds_error_t ds_vector_set(ds_vector_t *v, size_t index, const void *value);

size_t ds_vector_size(const ds_vector_t *v);
size_t ds_vector_capacity(const ds_vector_t *v);
bool ds_vector_is_empty(const ds_vector_t *v);

void ds_vector_clear(ds_vector_t *v);
ds_error_t ds_vector_reserve(ds_vector_t *v, size_t new_capacity);
ds_error_t ds_vector_shrink_to_fit(ds_vector_t *v);
void *ds_vector_data(const ds_vector_t *v);

#define DS_VECTOR_DEFINE_TYPE(TYPE, SUFFIX)                     \
static inline ds_error_t                                        \
ds_vector_push_back_##SUFFIX(ds_vector_t *v, TYPE value) {      \
    return ds_vector_push_back(v, &value);                      \
}                                                               \
static inline ds_error_t                                        \
ds_vector_pop_back_##SUFFIX(ds_vector_t *v, TYPE *out_value) {  \
    return ds_vector_pop_back(v, out_value);                    \
}                                                               \
static inline ds_error_t                                        \
ds_vector_get_##SUFFIX(const ds_vector_t *v, size_t index, TYPE *out_value) { \
    return ds_vector_get(v, index, out_value);                  \
}                                                               \
static inline ds_error_t                                        \
ds_vector_set_##SUFFIX(ds_vector_t *v, size_t index, TYPE value) { \
    return ds_vector_set(v, index, &value);                     \
}

#endif /* DS_VECTOR_H */
