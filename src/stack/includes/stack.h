#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

typedef struct
{
    void **data;
    int top;
    int capacity;
    size_t element_size;
} stack_t;

// generic
stack_t *create_stack(size_t element_size);
int push(stack_t *stack, void *element);
int pop(stack_t *stack, void *output);
int peek(stack_t *stack, void *output);
void free_stack(stack_t *stack);

// char
stack_t *create_char_stack();
int push_char(stack_t *stack, char value);
int pop_char(stack_t *stack, char *value);
int peek_char(stack_t *stack, char *value);

// int
stack_t *create_int_stack();
int push_int(stack_t *stack, int value);
int pop_int(stack_t *stack, int *value);
int peek_int(stack_t *stack, int *value);

// float
stack_t *create_float_stack();
int push_float(stack_t *stack, float value);
int pop_float(stack_t *stack, float *value);
int peek_float(stack_t *stack, float *value);

// double
stack_t *create_double_stack();
int push_double(stack_t *stack, double value);
int pop_double(stack_t *stack, double *value);
int peek_double(stack_t *stack, double *value);

// string (char *)
stack_t *create_string_stack();
int push_string(stack_t *stack, const char *value);
int pop_string(stack_t *stack, char **value);
int peek_string(stack_t *stack, char **value);

#endif