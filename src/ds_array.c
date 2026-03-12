#include "ds/ds_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct ds_array {
    void *data;
    size_t capacity;
    size_t element_size;

    void (*destructor)(void *);
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_array_t *ds_array_create(
    size_t capacity,
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    if (capacity == 0 || element_size == 0) return NULL;

    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_array_t *arr = (ds_array_t *)alloc(sizeof(ds_array_t));
    if (!arr) return NULL;

    // Prevent integer overflow during allocation
    if (capacity > SIZE_MAX / element_size) {
        dealloc(arr);
        return NULL;
    }

    arr->data = alloc(capacity * element_size);
    if (!arr->data) {
        dealloc(arr);
        return NULL;
    }

    memset(arr->data, 0, capacity * element_size);

    arr->capacity = capacity;
    arr->element_size = element_size;
    arr->destructor = destructor;
    arr->allocator = alloc;
    arr->deallocator = dealloc;

    return arr;
}

void ds_array_destroy(ds_array_t *arr) {
    if (!arr) return;
    if (arr->destructor) {
        for (size_t i = 0; i < arr->capacity; i++) {
            char *elem = (char *)arr->data + (i * arr->element_size);
            arr->destructor(elem);
        }
    }
    if (arr->data) {
        arr->deallocator(arr->data);
    }
    arr->deallocator(arr);
}

ds_error_t ds_array_get(const ds_array_t *arr, size_t index, void *out_value) {
    if (!arr || !out_value) return DS_ERR_INVALID_ARG;
    if (index >= arr->capacity) return DS_ERR_OUT_OF_RANGE;

    char *src = (char *)arr->data + (index * arr->element_size);
    memcpy(out_value, src, arr->element_size);
    return DS_SUCCESS;
}

ds_error_t ds_array_set(ds_array_t *arr, size_t index, const void *value) {
    if (!arr || !value) return DS_ERR_INVALID_ARG;
    if (index >= arr->capacity) return DS_ERR_OUT_OF_RANGE;

    char *dest = (char *)arr->data + (index * arr->element_size);
    if (arr->destructor) {
        arr->destructor(dest);
    }
    memcpy(dest, value, arr->element_size);
    return DS_SUCCESS;
}

size_t ds_array_capacity(const ds_array_t *arr) {
    return arr ? arr->capacity : 0;
}

void *ds_array_data(const ds_array_t *arr) {
    return arr ? arr->data : NULL;
}
