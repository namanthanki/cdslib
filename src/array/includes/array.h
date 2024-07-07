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
    int size;
    int capacity;
    size_t element_size;
} array_t;

// generic
array_t *create_array(size_t element_size);
array_error_t insert(array_t *arr, int index, const void *element);
array_error_t remove(array_t *arr, int index, void *output);
array_error_t get(array_t *arr, int index, void *output);
array_error_t set(array_t *arr, int index, const void *element);
array_error_t resize_array(array_t *arr, int new_capacity);
void free_array(array_t *arr);

// char
array_t *create_char_array();
array_error_t insert_char(array_t *arr, int index, char element);
array_error_t remove_char(array_t *arr, int index, char *output);
array_error_t get_char(array_t *arr, int index, char *output);
array_error_t set_char(array_t *arr, int index, char element);

// int
array_t *create_int_array();
array_error_t insert_int(array_t *arr, int index, int element);
array_error_t remove_int(array_t *arr, int index, int *output);
array_error_t get_int(array_t *arr, int index, int *output);
array_error_t set_int(array_t *arr, int index, int element);

// float
array_t *create_float_array();
array_error_t insert_float(array_t *arr, int index, float element);
array_error_t remove_float(array_t *arr, int index, float *output);
array_error_t get_float(array_t *arr, int index, float *output);
array_error_t set_float(array_t *arr, int index, float element);

// double
array_t *create_double_array();
array_error_t insert_double(array_t *arr, int index, double element);
array_error_t remove_double(array_t *arr, int index, double *output);
array_error_t get_double(array_t *arr, int index, double *output);
array_error_t set_double(array_t *arr, int index, double element);

// string
array_t *create_string_array();
array_error_t insert_string(array_t *arr, int index, char *element);
array_error_t remove_string(array_t *arr, int index, char **output);
array_error_t get_string(array_t *arr, int index, char **output);
array_error_t set_string(array_t *arr, int index, char *element);

#endif