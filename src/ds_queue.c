#include "ds/ds_queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct ds_queue {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
    size_t head;
    size_t tail;

    void (*destructor)(void *);
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_queue_t *ds_queue_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    if (element_size == 0) return NULL;

    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_queue_t *q = (ds_queue_t *)alloc(sizeof(ds_queue_t));
    if (!q) return NULL;

    q->data = NULL;
    q->size = 0;
    q->capacity = 0;
    q->element_size = element_size;
    q->head = 0;
    q->tail = 0;
    q->destructor = destructor;
    q->allocator = alloc;
    q->deallocator = dealloc;

    return q;
}

void ds_queue_destroy(ds_queue_t *q) {
    if (!q) return;
    ds_queue_clear(q);
    if (q->data) {
        q->deallocator(q->data);
    }
    q->deallocator(q);
}

static ds_error_t ds_queue_reserve(ds_queue_t *q, size_t new_capacity) {
    if (new_capacity <= q->capacity) return DS_SUCCESS;

    // Prevent integer overflow during allocation
    if (new_capacity > SIZE_MAX / q->element_size) {
        return DS_ERR_OUT_OF_RANGE;
    }

    void *new_data = q->allocator(new_capacity * q->element_size);
    if (!new_data) return DS_ERR_ALLOC;

    if (q->data) {
        if (q->head < q->tail) {
            memcpy(new_data, (char *)q->data + (q->head * q->element_size), q->size * q->element_size);
        } else if (q->size > 0) {
            size_t first_part = q->capacity - q->head;
            memcpy(new_data, (char *)q->data + (q->head * q->element_size), first_part * q->element_size);
            memcpy((char *)new_data + (first_part * q->element_size), q->data, q->tail * q->element_size);
        }
        q->deallocator(q->data);
    }

    q->data = new_data;
    q->capacity = new_capacity;
    q->head = 0;
    q->tail = q->size;
    return DS_SUCCESS;
}

ds_error_t ds_queue_enqueue(ds_queue_t *q, const void *value) {
    if (!q || !value) return DS_ERR_INVALID_ARG;

    if (q->size == q->capacity) {
        size_t new_cap = q->capacity == 0 ? 4 : q->capacity * 2;
        ds_error_t err = ds_queue_reserve(q, new_cap);
        if (err != DS_SUCCESS) return err;
    }

    char *dest = (char *)q->data + (q->tail * q->element_size);
    memcpy(dest, value, q->element_size);
    
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return DS_SUCCESS;
}

ds_error_t ds_queue_dequeue(ds_queue_t *q, void *out_value) {
    if (!q) return DS_ERR_INVALID_ARG;
    if (q->size == 0) return DS_ERR_EMPTY;

    char *src = (char *)q->data + (q->head * q->element_size);
    
    if (out_value) {
        memcpy(out_value, src, q->element_size);
    } else if (q->destructor) {
        q->destructor(src);
    }

    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return DS_SUCCESS;
}

ds_error_t ds_queue_peek(const ds_queue_t *q, void *out_value) {
    if (!q || !out_value) return DS_ERR_INVALID_ARG;
    if (q->size == 0) return DS_ERR_EMPTY;

    char *src = (char *)q->data + (q->head * q->element_size);
    memcpy(out_value, src, q->element_size);
    return DS_SUCCESS;
}

size_t ds_queue_size(const ds_queue_t *q) {
    return q ? q->size : 0;
}

size_t ds_queue_capacity(const ds_queue_t *q) {
    return q ? q->capacity : 0;
}

bool ds_queue_is_empty(const ds_queue_t *q) {
    return q ? q->size == 0 : true;
}

void ds_queue_clear(ds_queue_t *q) {
    if (!q) return;
    if (q->destructor) {
        for (size_t i = 0; i < q->size; i++) {
            size_t idx = (q->head + i) % q->capacity;
            char *elem = (char *)q->data + (idx * q->element_size);
            q->destructor(elem);
        }
    }
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}
