#include "stack.h"

stack_t *create_char_stack()
{
    return create_stack(sizeof(char));
}

int push_char(stack_t *stack, char value)
{
    return push(stack, &value);
}

int pop_char(stack_t *stack, char *value)
{
    return pop(stack, value);
}

int peek_char(stack_t *stack, char *value)
{
    return peek(stack, value);
}