#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef enum
{
    ARRAY_SUCCESS = 0,
    ARRAY_INDEX_OUT_OF_BOUNDS,
    ARRAY_MEMORY_ERROR
} array_error_t;

typedef struct
{
    void **data;
    size_t size;
    size_t capacity;
    size_t element_size;
} array_t;

#define DECLARE_ARRAY_FUNCTIONS(TYPE, SUFFIX)                                \
    array_t *create_##SUFFIX##_array();                                      \
    array_error_t insert_##SUFFIX(array_t *arr, size_t index, TYPE element); \
    array_error_t remove_##SUFFIX(array_t *arr, size_t index, TYPE *output); \
    array_error_t get_##SUFFIX(array_t *arr, size_t index, TYPE *output);    \
    array_error_t set_##SUFFIX(array_t *arr, size_t index, TYPE element);

#define DECLARE_STRING_ARRAY_FUNCTIONS                                      \
    array_t *create_string_array();                                         \
    array_error_t insert_string(array_t *arr, size_t index, char *element); \
    array_error_t remove_string(array_t *arr, size_t index, char **output); \
    array_error_t get_string(array_t *arr, size_t index, char **output);    \
    array_error_t set_string(array_t *arr, size_t index, char *element);    \
    void free_string_array(array_t *arr);

DECLARE_ARRAY_FUNCTIONS(char, char)
DECLARE_ARRAY_FUNCTIONS(int, int)
DECLARE_ARRAY_FUNCTIONS(float, float)
DECLARE_ARRAY_FUNCTIONS(double, double)
DECLARE_STRING_ARRAY_FUNCTIONS

// generic
array_t *create_array(size_t element_size);
array_error_t insert(array_t *arr, size_t index, const void *element);
array_error_t remove_element(array_t *arr, size_t index, void *output);
array_error_t get(array_t *arr, size_t index, void *output);
array_error_t set(array_t *arr, size_t index, const void *element);
array_error_t resize_array(array_t *arr, size_t new_capacity);
array_error_t shrink_array(array_t *arr);
void free_array(array_t *arr);

#endif