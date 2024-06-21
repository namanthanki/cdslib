#include "stack.h"

stack_t *create_int_stack()
{
    return create_stack(sizeof(int));
}

int push_int(stack_t *stack, int value)
{
    return push(stack, &value);
}

int pop_int(stack_t *stack, int *value)
{
    return pop(stack, value);
}

int peek_int(stack_t *stack, int *value)
{
    return peek(stack, value);
}