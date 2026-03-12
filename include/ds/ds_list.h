#ifndef DS_LIST_H
#define DS_LIST_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_list ds_list_t;
typedef struct ds_list_node ds_list_node_t;

ds_list_t *ds_list_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_list_destroy(ds_list_t *l);

ds_error_t ds_list_push_front(ds_list_t *l, const void *value);
ds_error_t ds_list_push_back(ds_list_t *l, const void *value);
ds_error_t ds_list_pop_front(ds_list_t *l, void *out_value);
ds_error_t ds_list_pop_back(ds_list_t *l, void *out_value);

ds_list_node_t *ds_list_begin(const ds_list_t *l);
ds_list_node_t *ds_list_end(const ds_list_t *l);
ds_list_node_t *ds_list_next(const ds_list_node_t *node);
ds_list_node_t *ds_list_prev(const ds_list_node_t *node);

void *ds_list_node_data(ds_list_node_t *node);

ds_error_t ds_list_insert_after(ds_list_t *l, ds_list_node_t *node, const void *value);
ds_error_t ds_list_remove(ds_list_t *l, ds_list_node_t *node, void *out_value);

size_t ds_list_size(const ds_list_t *l);
bool ds_list_is_empty(const ds_list_t *l);
void ds_list_clear(ds_list_t *l);

#define DS_LIST_DEFINE_TYPE(TYPE, SUFFIX)                       \
static inline ds_error_t                                        \
ds_list_push_front_##SUFFIX(ds_list_t *l, TYPE value) {         \
    return ds_list_push_front(l, &value);                       \
}                                                               \
static inline ds_error_t                                        \
ds_list_push_back_##SUFFIX(ds_list_t *l, TYPE value) {          \
    return ds_list_push_back(l, &value);                        \
}                                                               \
static inline ds_error_t                                        \
ds_list_pop_front_##SUFFIX(ds_list_t *l, TYPE *out_value) {     \
    return ds_list_pop_front(l, out_value);                     \
}                                                               \
static inline ds_error_t                                        \
ds_list_pop_back_##SUFFIX(ds_list_t *l, TYPE *out_value) {      \
    return ds_list_pop_back(l, out_value);                      \
}

#endif /* DS_LIST_H */
