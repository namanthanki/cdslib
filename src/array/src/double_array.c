#include "array.h"

array_t *create_double_array()
{
    return create_array(sizeof(double));
}

array_error_t insert_double(array_t *arr, size_t index, double element)
{
    return insert(arr, index, &element);
}

array_error_t remove_double(array_t *arr, size_t index, double *output)
{
    return remove_element(arr, index, output);
}

array_error_t get_double(array_t *arr, size_t index, double *output)
{
    return get(arr, index, output);
}

array_error_t set_double(array_t *arr, size_t index, double element)
{
    return set(arr, index, &element);
}