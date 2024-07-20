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
    size_t capacity;
    size_t size;
    size_t element_size;
} stack_t;

#define DECLARE_STACK_FUNCTIONS(TYPE, SUFFIX)                \
    stack_t *create_##SUFFIX##_stack();                      \
    stack_error_t push_##SUFFIX(stack_t *stack, TYPE value); \
    stack_error_t pop_##SUFFIX(stack_t *stack, TYPE *value); \
    stack_error_t peek_##SUFFIX(stack_t *stack, TYPE *value);

#define DECLARE_STRING_STACK_FUNCTIONS                            \
    stack_t *create_string_stack();                               \
    stack_error_t push_string(stack_t *stack, const char *value); \
    stack_error_t pop_string(stack_t *stack, char **value);       \
    stack_error_t peek_string(stack_t *stack, char **value);      \
    void free_string_stack(stack_t *stack);

DECLARE_STACK_FUNCTIONS(char, char)
DECLARE_STACK_FUNCTIONS(int, int)
DECLARE_STACK_FUNCTIONS(float, float)
DECLARE_STACK_FUNCTIONS(double, double)
DECLARE_STRING_STACK_FUNCTIONS

// Generic functions
stack_t *create_stack(size_t element_size);
stack_error_t push(stack_t *stack, const void *element);
stack_error_t pop(stack_t *stack, void *output);
stack_error_t peek(stack_t *stack, void *output);
stack_error_t resize_stack(stack_t *stack, size_t new_capacity);
stack_error_t shrink_stack(stack_t *stack);
void free_stack(stack_t *stack);

int is_stack_full(stack_t *stack);
int is_stack_empty(stack_t *stack);

#endif // STACK_H