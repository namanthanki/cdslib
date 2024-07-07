#include "array.h"

array_t *create_string_array()
{
    return create_array(sizeof(char *));
}

array_error_t insert_string(array_t *arr, size_t index, char *element)
{
    char *copy = strdup(element);
    if (!copy)
    {
        return ARRAY_MEMORY_ERROR;
    }

    array_error_t result = insert(arr, index, &copy);

    if (result != ARRAY_SUCCESS)
    {
        free(copy);
    }

    return result;
}

array_error_t remove_string(array_t *arr, size_t index, char **output)
{
    char *element;
    array_error_t result = remove_element(arr, index, &element);
    if (result == ARRAY_SUCCESS)
    {
        *output = element;
    }
    return result;

}

array_error_t get_string(array_t *arr, size_t index, char **output)
{
    char *element;
    array_error_t result = get(arr, index, &element);
    if (result == ARRAY_SUCCESS)
    {
        *output = element;
    }
    return result;
}

array_error_t set_string(array_t *arr, size_t index, char *element)
{
    char *copy = strdup(element);
    if (!copy)
    {
        return ARRAY_MEMORY_ERROR;
    }

    array_error_t result = set(arr, index, &copy);

    if (result != ARRAY_SUCCESS)
    {
        free(copy);
    }

    return result;
}

void free_string_array(array_t *arr)
{
    for (size_t i = 0; i < arr->size; i++)
    {
        char *element;
        remove_string(arr, i, &element);
        free(element);
    }

    free_array(arr);
}