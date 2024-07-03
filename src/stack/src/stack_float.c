#include "stack.h"

stack_t *create_float_stack()
{
    return create_stack(sizeof(float));
}

stack_error_t push_float(stack_t *stack, float value)
{
    return push(stack, &value);
}

stack_error_t pop_float(stack_t *stack, float *value)
{
    return pop(stack, value);
}

stack_error_t peek_float(stack_t *stack, float *value)
{
    return peek(stack, value);
}