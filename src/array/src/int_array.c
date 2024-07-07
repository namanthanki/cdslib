#include "array.h"

array_t *create_int_array()
{
    return create_array(sizeof(int));
}

array_error_t insert_int(array_t *arr, size_t index, int element)
{
    return insert(arr, index, &element);
}

array_error_t remove_int(array_t *arr, size_t index, int *output)
{
    return remove_element(arr, index, output);
}

array_error_t get_int(array_t *arr, size_t index, int *output)
{
    return get(arr, index, output);
}

array_error_t set_int(array_t *arr, size_t index, int element)
{
    return set(arr, index, &element);
}