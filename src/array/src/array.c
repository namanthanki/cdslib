#include "array.h"
#include <stdlib.h>

array_t *create_array(size_t element_size)
{
    array_t *arr = (array_t *)malloc(sizeof(array_t));
    if (!arr)
    {
        return NULL;
    }

    arr->data = (int **)malloc(sizeof(int *) * 100);
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = 100;
    arr->element_size = element_size;

    return arr;
}

array_error_t resize_array(array_t *arr, int new_capacity)
{
    int **new_data = (int **)realloc(arr->data, sizeof(int *) * new_capacity);
    if (!new_data)
    {
        return ARRAY_MEMORY_ERROR;
    }

    arr->data = new_data;
    arr->capacity = new_capacity;

    return ARRAY_SUCCESS;
}

array_error_t get(array_t *arr, int index, void *output)
{
    if (index < 0 || index >= arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(output, arr->data[index], arr->element_size);
    return ARRAY_SUCCESS;
}

array_error_t set(array_t *arr, int index, const void *element)
{
    if (index < 0 || index >= arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(arr->data[index], element, arr->element_size);
    return ARRAY_SUCCESS;
}

array_error_t insert(array_t *arr, int index, const void *element)
{
    if (index < 0 || index > arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    if (arr->size == arr->capacity)
    {
        array_error_t resize_result = resize_array(arr, arr->capacity * 2);
        if (resize_result != ARRAY_SUCCESS)
        {
            return resize_result;
        }
    }

    for (int i = arr->size; i > index; i--)
    {
        set(arr, i, arr->data[i - 1]);
    }

    arr->data[index] = (int *)malloc(arr->element_size);
    if (!arr->data[index])
    {
        return ARRAY_MEMORY_ERROR;
    }
    memcpy(arr->data[index], element, arr->element_size);

    arr->size++;
    return ARRAY_SUCCESS;
}

array_error_t remove_element(array_t *arr, int index, void *output)
{
    if (index < 0 || index >= arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(output, arr->data[index], arr->element_size);
    free(arr->data[index]);

    for (int i = index; i < arr->size - 1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
    return ARRAY_SUCCESS;
}

void free_array(array_t *arr)
{
    for (int i = 0; i < arr->size; i++)
    {
        free(arr->data[i]);
    }

    free(arr->data);
    free(arr);
}
