#include "array.h"

array_t *create_float_array()
{
    return create_array(sizeof(float));
}

array_error_t insert_float(array_t *arr, size_t index, float element)
{
    return insert(arr, index, &element);
}

array_error_t remove_float(array_t *arr, size_t index, float *output)
{
    return remove_element(arr, index, output);
}

array_error_t get_float(array_t *arr, size_t index, float *output)
{
    return get(arr, index, output);
}

array_error_t set_float(array_t *arr, size_t index, float element)
{
    return set(arr, index, &element);
}