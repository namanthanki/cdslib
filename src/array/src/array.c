#include "array.h"
#include "data_structure_utils.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFINE_ARRAY_FUNCTIONS(TYPE, SUFFIX)                                \
                                                                            \
    array_t *create_##SUFFIX##_array()                                      \
    {                                                                       \
        return create_array(sizeof(TYPE));                                  \
    }                                                                       \
                                                                            \
    array_error_t insert_##SUFFIX(array_t *arr, size_t index, TYPE element) \
    {                                                                       \
        return insert(arr, index, &element);                                \
    }                                                                       \
                                                                            \
    array_error_t remove_##SUFFIX(array_t *arr, size_t index, TYPE *output) \
    {                                                                       \
        return remove_element(arr, index, output);                          \
    }                                                                       \
                                                                            \
    array_error_t get_##SUFFIX(array_t *arr, size_t index, TYPE *output)    \
    {                                                                       \
        return get(arr, index, output);                                     \
    }                                                                       \
                                                                            \
    array_error_t set_##SUFFIX(array_t *arr, size_t index, TYPE element)    \
    {                                                                       \
        return set(arr, index, &element);                                   \
    }

#define DEFINE_STRING_ARRAY_FUNCTIONS                                      \
                                                                           \
    array_t *create_string_array()                                         \
    {                                                                      \
        return create_array(sizeof(char *));                               \
    }                                                                      \
                                                                           \
    array_error_t insert_string(array_t *arr, size_t index, char *element) \
    {                                                                      \
        char *copy = strdup(element);                                      \
        if (!copy)                                                         \
        {                                                                  \
            return ARRAY_MEMORY_ERROR;                                     \
        }                                                                  \
                                                                           \
        array_error_t result = insert(arr, index, &copy);                  \
                                                                           \
        if (result != ARRAY_SUCCESS)                                       \
        {                                                                  \
            free(copy);                                                    \
        }                                                                  \
                                                                           \
        return result;                                                     \
    }                                                                      \
                                                                           \
    array_error_t remove_string(array_t *arr, size_t index, char **output) \
    {                                                                      \
        char *element;                                                     \
        array_error_t result = remove_element(arr, index, &element);       \
        if (result == ARRAY_SUCCESS)                                       \
        {                                                                  \
            *output = element;                                             \
        }                                                                  \
        return result;                                                     \
    }                                                                      \
                                                                           \
    array_error_t get_string(array_t *arr, size_t index, char **output)    \
    {                                                                      \
        char *element;                                                     \
        array_error_t result = get(arr, index, &element);                  \
        if (result == ARRAY_SUCCESS)                                       \
        {                                                                  \
            *output = element;                                             \
        }                                                                  \
        return result;                                                     \
    }                                                                      \
                                                                           \
    array_error_t set_string(array_t *arr, size_t index, char *element)    \
    {                                                                      \
        char *copy = strdup(element);                                      \
        if (!copy)                                                         \
        {                                                                  \
            return ARRAY_MEMORY_ERROR;                                     \
        }                                                                  \
                                                                           \
        array_error_t result = set(arr, index, &copy);                     \
                                                                           \
        if (result != ARRAY_SUCCESS)                                       \
        {                                                                  \
            free(copy);                                                    \
        }                                                                  \
                                                                           \
        return result;                                                     \
    }                                                                      \
                                                                           \
    void free_string_array(array_t *arr)                                   \
    {                                                                      \
        for (size_t i = 0; i < arr->size; i++)                             \
        {                                                                  \
            char *element;                                                 \
            remove_string(arr, i, &element);                               \
            free(element);                                                 \
        }                                                                  \
                                                                           \
        free_array(arr);                                                   \
    }

DEFINE_ARRAY_FUNCTIONS(char, char)
DEFINE_ARRAY_FUNCTIONS(int, int)
DEFINE_ARRAY_FUNCTIONS(float, float)
DEFINE_ARRAY_FUNCTIONS(double, double)
DEFINE_STRING_ARRAY_FUNCTIONS

array_t *create_array(size_t element_size)
{
    array_t *arr = (array_t *)malloc(sizeof(array_t));
    if (!arr)
    {
        return NULL;
    }

    arr->data = (void **)malloc(sizeof(void *) * 100);
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

void copy_func(void *dest, void *src, size_t size)
{
    memcpy(dest, src, size);
}

void free_func(void *data)
{
    free(data);
}

array_error_t resize_array(array_t *arr, size_t new_capacity)
{
    resize_error_t result = resize_data_structure(
        (void **)&arr->data,
        &arr->capacity,
        &arr->size,
        arr->element_size,
        new_capacity,
        copy_func,
        free_func);

    if (result != RESIZE_SUCCESS)
    {
        return ARRAY_MEMORY_ERROR;
    }

    return ARRAY_SUCCESS;
}

array_error_t shrink_array(array_t *arr)
{
    resize_error_t result = shrink_data_structure(
        arr,
        &arr->capacity,
        &arr->size,
        (resize_func_t)resize_array);

    if (result != RESIZE_SUCCESS)
    {
        return ARRAY_MEMORY_ERROR;
    }

    return ARRAY_SUCCESS;
}

array_error_t get(array_t *arr, size_t index, void *output)
{
    if (index >= arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(output, arr->data[index], arr->element_size);
    return ARRAY_SUCCESS;
}

array_error_t set(array_t *arr, size_t index, const void *element)
{
    if (index >= arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(arr->data[index], element, arr->element_size);
    return ARRAY_SUCCESS;
}

array_error_t insert(array_t *arr, size_t index, const void *element)
{
    if (index > arr->size)
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

    for (size_t i = arr->size; i > index; i--)
    {
        array_error_t set_result = set(arr, i, arr->data[i - 1]);
        if (set_result != ARRAY_SUCCESS)
        {
            return set_result;
        }
    }

    arr->data[index] = (void *)malloc(arr->element_size);
    if (!arr->data[index])
    {
        return ARRAY_MEMORY_ERROR;
    }
    memcpy(arr->data[index], element, arr->element_size);

    arr->size++;
    return ARRAY_SUCCESS;
}

array_error_t remove_element(array_t *arr, size_t index, void *output)
{
    if (index >= arr->size)
    {
        return ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    memcpy(output, arr->data[index], arr->element_size);

    for (size_t i = index; i < arr->size - 1; i++)
    {
        array_error_t set_result = set(arr, i, arr->data[i + 1]);
        if (set_result != ARRAY_SUCCESS)
        {
            return set_result;
        }
    }
    arr->size--;
    return shrink_array(arr);
}

void free_array(array_t *arr)
{
    for (size_t i = 0; i < arr->size; i++)
    {
        free(arr->data[i]);
    }

    free(arr->data);
    free(arr);
}
