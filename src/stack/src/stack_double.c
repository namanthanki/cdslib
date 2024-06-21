#include "stack.h"

stack_t *create_double_stack()
{
    return create_stack(sizeof(double));
}

int push_double(stack_t *stack, double value)
{
    return push(stack, &value);
}

int pop_double(stack_t *stack, double *value)
{
    return pop(stack, value);
}

int peek_double(stack_t *stack, double *value)
{
    return peek(stack, value);
}