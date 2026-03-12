#include "ds/ds_stack.h"
#include "ds/ds_vector.h"
#include <stdlib.h>

struct ds_stack {
    ds_vector_t *vec;
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_stack_t *ds_stack_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_stack_t *s = (ds_stack_t *)alloc(sizeof(ds_stack_t));
    if (!s) return NULL;

    s->vec = ds_vector_create(element_size, destructor, alloc, dealloc);
    if (!s->vec) {
        dealloc(s);
        return NULL;
    }

    s->allocator = alloc;
    s->deallocator = dealloc;

    return s;
}

void ds_stack_destroy(ds_stack_t *s) {
    if (!s) return;
    ds_vector_destroy(s->vec);
    s->deallocator(s);
}

ds_error_t ds_stack_push(ds_stack_t *s, const void *value) {
    if (!s) return DS_ERR_INVALID_ARG;
    return ds_vector_push_back(s->vec, value);
}

ds_error_t ds_stack_pop(ds_stack_t *s, void *out_value) {
    if (!s) return DS_ERR_INVALID_ARG;
    return ds_vector_pop_back(s->vec, out_value);
}

ds_error_t ds_stack_peek(const ds_stack_t *s, void *out_value) {
    if (!s) return DS_ERR_INVALID_ARG;
    size_t size = ds_vector_size(s->vec);
    if (size == 0) return DS_ERR_EMPTY;
    return ds_vector_get(s->vec, size - 1, out_value);
}

size_t ds_stack_size(const ds_stack_t *s) {
    return s ? ds_vector_size(s->vec) : 0;
}

bool ds_stack_is_empty(const ds_stack_t *s) {
    return s ? ds_vector_is_empty(s->vec) : true;
}

void ds_stack_clear(ds_stack_t *s) {
    if (s) ds_vector_clear(s->vec);
}
