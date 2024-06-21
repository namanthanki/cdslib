#include "stack.h"

stack_t *create_float_stack()
{
    return create_stack(sizeof(float));
}

int push_float(stack_t *stack, float value)
{
    return push(stack, &value);
}

int pop_float(stack_t *stack, float *value)
{
    return pop(stack, value);
}

int peek_float(stack_t *stack, float *value)
{
    return peek(stack, value);
}