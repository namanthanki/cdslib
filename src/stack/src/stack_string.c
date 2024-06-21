#include "stack.h"
#include <stdio.h>
#include <string.h>

stack_t *create_string_stack()
{
    stack_t *stack = create_stack(sizeof(char *));
    // if (stack)
    // {
    //     printf("Debug: Created string stack with element_size = %zu\n", stack->element_size);
    // }
    return stack;
}

int push_string(stack_t *stack, const char *value)
{
    char *copy = strdup(value);
    if (!copy)
    {
        return -1;
    }

    // printf("Debug: push_string - Copied string: %s\n", copy);
    // printf("Debug: push_string - Address of copy: %p\n", (void *)copy);

    int result = push(stack, &copy);

    if (result != 0)
    {
        free(copy);
    }

    return result;
}

int pop_string(stack_t *stack, char **value)
{
    char *popped_value;
    int result = pop(stack, &popped_value);
    if (result == 0)
    {
        *value = popped_value;
        // printf("Debug: pop_string - Popped value: %s\n", *value);
    }
    return result;
}

int peek_string(stack_t *stack, char **value)
{
    printf("Debug: peek_string called\n");
    int result = peek(stack, value);
    // if (result == 0)
    // {
    //     printf("Debug: peek_string - Peeked value: %s\n", *value);
    // }
    return result;
}