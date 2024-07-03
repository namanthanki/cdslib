#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

typedef enum
{
    STACK_SUCCESS = 0,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    STACK_MEMORY_ERROR
} stack_error_t;

typedef struct
{
    void **data;
    int top;
    int capacity;
    size_t element_size;
} stack_t;

// generic
stack_t *create_stack(size_t element_size);
stack_error_t push(stack_t *stack, const void *element);
stack_error_t pop(stack_t *stack, void *output);
stack_error_t peek(stack_t *stack, void *output);
stack_error_t resize_stack(stack_t *stack, int new_capacity);
void free_stack(stack_t *stack);

// char
stack_t *create_char_stack();
stack_error_t push_char(stack_t *stack, char value);
stack_error_t pop_char(stack_t *stack, char *value);
stack_error_t peek_char(stack_t *stack, char *value);

// int
stack_t *create_int_stack();
stack_error_t push_int(stack_t *stack, int value);
stack_error_t pop_int(stack_t *stack, int *value);
stack_error_t peek_int(stack_t *stack, int *value);

// float
stack_t *create_float_stack();
stack_error_t push_float(stack_t *stack, float value);
stack_error_t pop_float(stack_t *stack, float *value);
stack_error_t peek_float(stack_t *stack, float *value);

// double
stack_t *create_double_stack();
stack_error_t push_double(stack_t *stack, double value);
stack_error_t pop_double(stack_t *stack, double *value);
stack_error_t peek_double(stack_t *stack, double *value);

// string (char *)
stack_t *create_string_stack();
stack_error_t push_string(stack_t *stack, const char *value);
stack_error_t pop_string(stack_t *stack, char **value);
stack_error_t peek_string(stack_t *stack, char **value);
void free_string_stack(stack_t *stack);

#endif