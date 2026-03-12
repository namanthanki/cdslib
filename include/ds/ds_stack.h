#ifndef DS_STACK_H
#define DS_STACK_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_stack ds_stack_t;

ds_stack_t *ds_stack_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_stack_destroy(ds_stack_t *s);

ds_error_t ds_stack_push(ds_stack_t *s, const void *value);
ds_error_t ds_stack_pop(ds_stack_t *s, void *out_value);
ds_error_t ds_stack_peek(const ds_stack_t *s, void *out_value);

size_t ds_stack_size(const ds_stack_t *s);
bool ds_stack_is_empty(const ds_stack_t *s);
void ds_stack_clear(ds_stack_t *s);

#define DS_STACK_DEFINE_TYPE(TYPE, SUFFIX)                      \
static inline ds_error_t                                        \
ds_stack_push_##SUFFIX(ds_stack_t *s, TYPE value) {             \
    return ds_stack_push(s, &value);                            \
}                                                               \
static inline ds_error_t                                        \
ds_stack_pop_##SUFFIX(ds_stack_t *s, TYPE *out_value) {         \
    return ds_stack_pop(s, out_value);                          \
}                                                               \
static inline ds_error_t                                        \
ds_stack_peek_##SUFFIX(const ds_stack_t *s, TYPE *out_value) {  \
    return ds_stack_peek(s, out_value);                         \
}

#endif /* DS_STACK_H */
