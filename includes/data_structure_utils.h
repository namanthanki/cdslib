#ifndef DATA_STRUCTURE_UTILS_H
#define DATA_STRUCTURE_UTILS_H

#include <stddef.h>

typedef enum
{
    RESIZE_SUCCESS,
    RESIZE_MEMORY_ERROR
} resize_error_t;

typedef void (*copy_func_t)(void *dest, void *src, size_t size);
typedef void (*free_func_t)(void *data);
typedef resize_error_t (*resize_func_t)(void *structure, size_t new_capacity);

resize_error_t resize_data_structure(
    void **data,
    size_t *capacity,
    size_t *size,
    size_t element_size,
    size_t new_capacity,
    copy_func_t copy_func,
    free_func_t free_func
);

resize_error_t shrink_data_structure(
    void *strcture,
    size_t *capacity,
    size_t *size,
    resize_func_t resize_func);
#endif