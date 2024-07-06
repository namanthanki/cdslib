#include "array.h"

array_t *create_char_array()
{
    return create_array(sizeof(char));
}

array_error_t insert_char(array_t *arr, int index, char element)
{
    return insert(arr, index, &element);
}

array_error_t remove_char(array_t *arr, int index, char *output)
{
    return remove_element(arr, index, output);
}

array_error_t get_char(array_t *arr, int index, char *output)
{
    return get(arr, index, output);
}

array_error_t set_char(array_t *arr, int index, char element)
{
    return set(arr, index, &element);
}
