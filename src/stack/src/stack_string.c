#include "stack.h"
#include <stdio.h>
#include <string.h>

stack_t *create_string_stack()
{
    return create_stack(sizeof(char *));
}

stack_error_t push_string(stack_t *stack, const char *value)
{
    char *copy = strdup(value);
    if (!copy)
    {
        return STACK_MEMORY_ERROR;
    }

    stack_error_t result = push(stack, &copy);

    if (result != STACK_SUCCESS)
    {
        free(copy);
    }

    return result;
}

stack_error_t pop_string(stack_t *stack, char **value)
{
    char *popped_value;
    stack_error_t result = pop(stack, &popped_value);
    if (result == STACK_SUCCESS)
    {
        *value = popped_value;
    }
    return result;
}

stack_error_t peek_string(stack_t *stack, char **value)
{
    return peek(stack, value);
}

void free_string_stack(stack_t *stack)
{
    while (stack->top >= 0)
    {
        char *value;
        pop_string(stack, &value);
        free(value);
    }
    free_stack(stack);
}