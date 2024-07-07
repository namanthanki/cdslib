#include "data_structure_utils.h"
#include <stdlib.h>

resize_error_t resize_data_structure(
    void **data,
    size_t *capacity,
    size_t *size,
    size_t element_size,
    size_t new_capacity,
    copy_func_t copy_func,
    free_func_t free_func)
{
    void *new_data = malloc(element_size * new_capacity);
    if (!new_data)
    {
        return RESIZE_MEMORY_ERROR;
    }

    size_t copy_size = (new_capacity < *size) ? new_capacity : *size;
    for (size_t i = 0; i < copy_size; i++)
    {
        copy_func((char *)new_data + i * element_size,
                  (char *)*data + i * element_size,
                  element_size);
    }

    for (size_t i = copy_size; i < *size; i++)
    {
        free_func((char *)*data + i * element_size);
    }

    free(*data);
    *data = new_data;
    *capacity = new_capacity;
    *size = copy_size;

    return RESIZE_SUCCESS;
}

resize_error_t shrink_data_structure(
    void *structure,
    size_t *capacity,
    size_t *size,
    resize_func_t resize_func)
{
    if (*size < *capacity / 4 && *capacity > 100)
    {
        size_t new_capacity = *capacity / 2;
        resize_error_t error = resize_func(structure, new_capacity);
        if (error != RESIZE_SUCCESS)
        {
            return error;
        }
    }

    return RESIZE_SUCCESS;
}