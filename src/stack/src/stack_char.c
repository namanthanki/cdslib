#include "stack.h"

stack_t *create_char_stack()
{
    return create_stack(sizeof(char));
}

stack_error_t push_char(stack_t *stack, char value)
{
    return push(stack, &value);
}

stack_error_t pop_char(stack_t *stack, char *value)
{
    return pop(stack, value);
}

stack_error_t peek_char(stack_t *stack, char *value)
{
    return peek(stack, value);
}