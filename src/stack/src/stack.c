#include "stack.h"
#include "data_structure_utils.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFINE_STACK_FUNCTIONS(TYPE, SUFFIX)                 \
    stack_t *create_##SUFFIX##_stack()                       \
    {                                                        \
        return create_stack(sizeof(TYPE));                   \
    }                                                        \
                                                             \
    stack_error_t push_##SUFFIX(stack_t *stack, TYPE value)  \
    {                                                        \
        return push(stack, &value);                          \
    }                                                        \
                                                             \
    stack_error_t pop_##SUFFIX(stack_t *stack, TYPE *value)  \
    {                                                        \
        return pop(stack, value);                            \
    }                                                        \
                                                             \
    stack_error_t peek_##SUFFIX(stack_t *stack, TYPE *value) \
    {                                                        \
        return peek(stack, value);                           \
    }

#define DEFINE_STRING_STACK_FUNCTIONS                            \
    stack_t *create_string_stack()                               \
    {                                                            \
        return create_stack(sizeof(char *));                     \
    }                                                            \
                                                                 \
    stack_error_t push_string(stack_t *stack, const char *value) \
    {                                                            \
        char *copy = strdup(value);                              \
        if (!copy)                                               \
        {                                                        \
            return STACK_MEMORY_ERROR;                           \
        }                                                        \
                                                                 \
        stack_error_t result = push(stack, &copy);               \
                                                                 \
        if (result != STACK_SUCCESS)                             \
        {                                                        \
            free(copy);                                          \
        }                                                        \
                                                                 \
        return result;                                           \
    }                                                            \
                                                                 \
    stack_error_t pop_string(stack_t *stack, char **value)       \
    {                                                            \
        char *popped_value;                                      \
        stack_error_t result = pop(stack, &popped_value);        \
        if (result == STACK_SUCCESS)                             \
        {                                                        \
            *value = popped_value;                               \
        }                                                        \
        return result;                                           \
    }                                                            \
                                                                 \
    stack_error_t peek_string(stack_t *stack, char **value)      \
    {                                                            \
        return peek(stack, value);                               \
    }                                                            \
                                                                 \
    void free_string_stack(stack_t *stack)                       \
    {                                                            \
        while (stack->top >= 0)                                  \
        {                                                        \
            char *value;                                         \
            pop_string(stack, &value);                           \
            free(value);                                         \
        }                                                        \
        free_stack(stack);                                       \
    }

DEFINE_STACK_FUNCTIONS(char, char)
DEFINE_STACK_FUNCTIONS(int, int)
DEFINE_STACK_FUNCTIONS(float, float)
DEFINE_STACK_FUNCTIONS(double, double)
DEFINE_STRING_STACK_FUNCTIONS

int is_stack_full(stack_t *stack)
{
    return stack->size == stack->capacity;
}

int is_stack_empty(stack_t *stack)
{
    return stack->size == 0;
}

stack_t *create_stack(size_t element_size)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (!stack)
    {
        return NULL;
    }

    stack->data = (void **)malloc(sizeof(void *) * 100);
    if (!stack->data)
    {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->size = 0;
    stack->capacity = 100;
    stack->element_size = element_size;

    return stack;
}

void copy_func(void *dest, void *src, size_t size)
{
    memcpy(dest, src, size);
}

void free_func(void *data)
{
    free(data);
}

stack_error_t resize_stack(stack_t *stack, size_t new_capacity)
{
    resize_error_t result = resize_data_structure(
        (void **)&stack->data,
        &stack->capacity,
        &stack->size,
        stack->element_size,
        new_capacity,
        copy_func,
        free_func);

    if (result != RESIZE_SUCCESS)
    {
        return STACK_MEMORY_ERROR;
    }

    return STACK_SUCCESS;
}

stack_error_t shrink_stack(stack_t *stack)
{
    resize_error_t result = shrink_data_structure(
        stack,
        &stack->capacity,
        &stack->size,
        (resize_func_t)resize_stack);

    if (result != RESIZE_SUCCESS)
    {
        return STACK_MEMORY_ERROR;
    }

    return STACK_SUCCESS;
}

stack_error_t push(stack_t *stack, const void *element)
{
    if (is_stack_full(stack))
    {
        stack_error_t resize_result = resize_stack(stack, stack->capacity * 2);
        if (resize_result != STACK_SUCCESS)
        {
            return resize_result;
        }
    }

    stack->top++;
    stack->data[stack->top] = malloc(stack->element_size);
    if (!stack->data[stack->top])
    {
        return STACK_MEMORY_ERROR;
    }
    memcpy(stack->data[stack->top], element, stack->element_size);

    stack->size++;
    return STACK_SUCCESS;
}

stack_error_t pop(stack_t *stack, void *output)
{
    if (is_stack_empty(stack))
    {
        return STACK_UNDERFLOW;
    }

    memcpy(output, stack->data[stack->top], stack->element_size);
    free(stack->data[stack->top]);
    stack->top--;
    stack->size--;
    return STACK_SUCCESS;
}

stack_error_t peek(stack_t *stack, void *output)
{
    if (is_stack_empty(stack))
    {
        return STACK_UNDERFLOW;
    }

    memcpy(output, stack->data[stack->top], stack->element_size);

    return STACK_SUCCESS;
}

void free_stack(stack_t *stack)
{
    for (int i = 0; i <= stack->top; i++)
    {
        free(stack->data[i]);
    }

    free(stack->data);
    free(stack);
}