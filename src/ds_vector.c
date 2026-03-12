#include "ds/ds_vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct ds_vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;

    void (*destructor)(void *);
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_vector_t *ds_vector_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    if (element_size == 0) return NULL;

    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_vector_t *v = (ds_vector_t *)alloc(sizeof(ds_vector_t));
    if (!v) return NULL;

    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->element_size = element_size;
    v->destructor = destructor;
    v->allocator = alloc;
    v->deallocator = dealloc;

    return v;
}

void ds_vector_destroy(ds_vector_t *v) {
    if (!v) return;
    ds_vector_clear(v);
    if (v->data) {
        v->deallocator(v->data);
    }
    v->deallocator(v);
}

ds_error_t ds_vector_reserve(ds_vector_t *v, size_t new_capacity) {
    if (!v) return DS_ERR_INVALID_ARG;
    if (new_capacity <= v->capacity) return DS_SUCCESS;

    // Prevent integer overflow during allocation
    if (new_capacity > SIZE_MAX / v->element_size) {
        return DS_ERR_OUT_OF_RANGE;
    }

    void *new_data = v->allocator(new_capacity * v->element_size);
    if (!new_data) return DS_ERR_ALLOC;

    if (v->data) {
        memcpy(new_data, v->data, v->size * v->element_size);
        v->deallocator(v->data);
    }

    v->data = new_data;
    v->capacity = new_capacity;
    return DS_SUCCESS;
}

ds_error_t ds_vector_push_back(ds_vector_t *v, const void *value) {
    if (!v || !value) return DS_ERR_INVALID_ARG;

    if (v->size == v->capacity) {
        size_t new_cap = v->capacity == 0 ? 4 : v->capacity * 2;
        ds_error_t err = ds_vector_reserve(v, new_cap);
        if (err != DS_SUCCESS) return err;
    }

    char *dest = (char *)v->data + (v->size * v->element_size);
    memcpy(dest, value, v->element_size);
    v->size++;
    return DS_SUCCESS;
}

ds_error_t ds_vector_pop_back(ds_vector_t *v, void *out_value) {
    if (!v) return DS_ERR_INVALID_ARG;
    if (v->size == 0) return DS_ERR_EMPTY;

    v->size--;
    char *src = (char *)v->data + (v->size * v->element_size);
    
    if (out_value) {
        memcpy(out_value, src, v->element_size);
    } else if (v->destructor) {
        v->destructor(src);
    }

    return DS_SUCCESS;
}

ds_error_t ds_vector_insert(ds_vector_t *v, size_t index, const void *value) {
    if (!v || !value) return DS_ERR_INVALID_ARG;
    if (index > v->size) return DS_ERR_OUT_OF_RANGE;

    if (v->size == v->capacity) {
        size_t new_cap = v->capacity == 0 ? 4 : v->capacity * 2;
        ds_error_t err = ds_vector_reserve(v, new_cap);
        if (err != DS_SUCCESS) return err;
    }

    char *dest = (char *)v->data + (index * v->element_size);
    if (index < v->size) {
        memmove(dest + v->element_size, dest, (v->size - index) * v->element_size);
    }

    memcpy(dest, value, v->element_size);
    v->size++;
    return DS_SUCCESS;
}

ds_error_t ds_vector_remove(ds_vector_t *v, size_t index, void *out_value) {
    if (!v) return DS_ERR_INVALID_ARG;
    if (index >= v->size) return DS_ERR_OUT_OF_RANGE;

    char *src = (char *)v->data + (index * v->element_size);
    
    if (out_value) {
        memcpy(out_value, src, v->element_size);
    } else if (v->destructor) {
        v->destructor(src);
    }

    if (index < v->size - 1) {
        memmove(src, src + v->element_size, (v->size - index - 1) * v->element_size);
    }

    v->size--;
    return DS_SUCCESS;
}

ds_error_t ds_vector_get(const ds_vector_t *v, size_t index, void *out_value) {
    if (!v || !out_value) return DS_ERR_INVALID_ARG;
    if (index >= v->size) return DS_ERR_OUT_OF_RANGE;

    char *src = (char *)v->data + (index * v->element_size);
    memcpy(out_value, src, v->element_size);
    return DS_SUCCESS;
}

ds_error_t ds_vector_set(ds_vector_t *v, size_t index, const void *value) {
    if (!v || !value) return DS_ERR_INVALID_ARG;
    if (index >= v->size) return DS_ERR_OUT_OF_RANGE;

    char *dest = (char *)v->data + (index * v->element_size);
    if (v->destructor) {
        v->destructor(dest);
    }
    memcpy(dest, value, v->element_size);
    return DS_SUCCESS;
}

size_t ds_vector_size(const ds_vector_t *v) {
    return v ? v->size : 0;
}

size_t ds_vector_capacity(const ds_vector_t *v) {
    return v ? v->capacity : 0;
}

bool ds_vector_is_empty(const ds_vector_t *v) {
    return v ? v->size == 0 : true;
}

void ds_vector_clear(ds_vector_t *v) {
    if (!v) return;
    if (v->destructor) {
        for (size_t i = 0; i < v->size; i++) {
            char *elem = (char *)v->data + (i * v->element_size);
            v->destructor(elem);
        }
    }
    v->size = 0;
}

ds_error_t ds_vector_shrink_to_fit(ds_vector_t *v) {
    if (!v) return DS_ERR_INVALID_ARG;
    if (v->size == v->capacity) return DS_SUCCESS;

    if (v->size == 0) {
        if (v->data) {
            v->deallocator(v->data);
            v->data = NULL;
        }
        v->capacity = 0;
        return DS_SUCCESS;
    }

    void *new_data = v->allocator(v->size * v->element_size);
    if (!new_data) return DS_ERR_ALLOC;

    memcpy(new_data, v->data, v->size * v->element_size);
    v->deallocator(v->data);
    v->data = new_data;
    v->capacity = v->size;

    return DS_SUCCESS;
}

void *ds_vector_data(const ds_vector_t *v) {
    return v ? v->data : NULL;
}
