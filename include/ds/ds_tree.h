#ifndef DS_TREE_H
#define DS_TREE_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_tree ds_tree_t;
typedef struct ds_tree_node ds_tree_node_t;

typedef int (*ds_cmp_fn)(const void *key1, const void *key2);

ds_tree_t *ds_tree_create(
    size_t element_size,
    ds_cmp_fn cmp_fn,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_tree_destroy(ds_tree_t *tree);

ds_error_t ds_tree_insert(ds_tree_t *tree, const void *value);
ds_error_t ds_tree_remove(ds_tree_t *tree, const void *value, void *out_value);
ds_error_t ds_tree_find(const ds_tree_t *tree, const void *value, void *out_value);

void ds_tree_inorder(const ds_tree_t *tree, void (*callback)(const void *));
void ds_tree_preorder(const ds_tree_t *tree, void (*callback)(const void *));
void ds_tree_postorder(const ds_tree_t *tree, void (*callback)(const void *));

size_t ds_tree_size(const ds_tree_t *tree);
bool ds_tree_is_empty(const ds_tree_t *tree);
void ds_tree_clear(ds_tree_t *tree);

#define DS_TREE_DEFINE_TYPE(TYPE, SUFFIX)                       \
static inline ds_error_t                                        \
ds_tree_insert_##SUFFIX(ds_tree_t *tree, TYPE value) {          \
    return ds_tree_insert(tree, &value);                        \
}                                                               \
static inline ds_error_t                                        \
ds_tree_remove_##SUFFIX(ds_tree_t *tree, TYPE value, TYPE *out_value) { \
    return ds_tree_remove(tree, &value, out_value);             \
}                                                               \
static inline ds_error_t                                        \
ds_tree_find_##SUFFIX(const ds_tree_t *tree, TYPE value, TYPE *out_value) { \
    return ds_tree_find(tree, &value, out_value);               \
}

#endif /* DS_TREE_H */
