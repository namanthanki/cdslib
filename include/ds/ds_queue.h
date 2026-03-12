#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include "ds_common.h"
#include <stdbool.h>

typedef struct ds_queue ds_queue_t;

ds_queue_t *ds_queue_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn);

void ds_queue_destroy(ds_queue_t *q);

ds_error_t ds_queue_enqueue(ds_queue_t *q, const void *value);
ds_error_t ds_queue_dequeue(ds_queue_t *q, void *out_value);
ds_error_t ds_queue_peek(const ds_queue_t *q, void *out_value);

size_t ds_queue_size(const ds_queue_t *q);
size_t ds_queue_capacity(const ds_queue_t *q);
bool ds_queue_is_empty(const ds_queue_t *q);
void ds_queue_clear(ds_queue_t *q);

#define DS_QUEUE_DEFINE_TYPE(TYPE, SUFFIX)                      \
static inline ds_error_t                                        \
ds_queue_enqueue_##SUFFIX(ds_queue_t *q, TYPE value) {          \
    return ds_queue_enqueue(q, &value);                         \
}                                                               \
static inline ds_error_t                                        \
ds_queue_dequeue_##SUFFIX(ds_queue_t *q, TYPE *out_value) {     \
    return ds_queue_dequeue(q, out_value);                      \
}                                                               \
static inline ds_error_t                                        \
ds_queue_peek_##SUFFIX(const ds_queue_t *q, TYPE *out_value) {  \
    return ds_queue_peek(q, out_value);                         \
}

#endif /* DS_QUEUE_H */
