#include "stack.h"

stack_t *create_int_stack()
{
    return create_stack(sizeof(int));
}

stack_error_t push_int(stack_t *stack, int value)
{
    return push(stack, &value);
}

stack_error_t pop_int(stack_t *stack, int *value)
{
    return pop(stack, value);
}

stack_error_t peek_int(stack_t *stack, int *value)
{
    return peek(stack, value);
}