#include "stack.h"

stack_t *create_double_stack()
{
    return create_stack(sizeof(double));
}

stack_error_t push_double(stack_t *stack, double value)
{
    return push(stack, &value);
}

stack_error_t pop_double(stack_t *stack, double *value)
{
    return pop(stack, value);
}

stack_error_t peek_double(stack_t *stack, double *value)
{
    return peek(stack, value);
}