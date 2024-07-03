#include "stack.h"

stack_t *create_stack(size_t element_size)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (!stack)
    {
        return NULL;
    }

    stack->data = (void **)malloc(sizeof(void *) * 10);
    if (!stack->data)
    {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->capacity = 10;
    stack->element_size = element_size;

    return stack;
}

stack_error_t push(stack_t *stack, const void *element)
{
    if (stack->top == stack->capacity - 1)
    {
        stack_error_t resize_result = resize_stack(stack, stack->capacity * 2);
        if (resize_result != STACK_SUCCESS)
        {
            return resize_result;
        }
    }

    stack->top++;
    stack->data[stack->top] = (void *)malloc(stack->element_size);
    if (!stack->data[stack->top])
    {
        return STACK_MEMORY_ERROR;
    }
    memcpy(stack->data[stack->top], element, stack->element_size);
    return STACK_SUCCESS;
}

stack_error_t pop(stack_t *stack, void *output)
{
    if (stack->top == -1)
    {
        return STACK_UNDERFLOW;
    }

    memcpy(output, stack->data[stack->top], stack->element_size);
    free(stack->data[stack->top]);
    stack->top--;

    return STACK_SUCCESS;
}

stack_error_t peek(stack_t *stack, void *output)
{
    if (stack->top == -1)
    {
        return STACK_UNDERFLOW;
    }

    memcpy(output, stack->data[stack->top], stack->element_size);

    return STACK_SUCCESS;
}

void free_stack(stack_t *stack)
{
    for (int i = 0; i <= stack->top; i++)
    {
        free(stack->data[i]);
    }

    free(stack->data);
    free(stack);
}

stack_error_t resize_stack(stack_t *stack, int new_capacity)
{
    void **new_data = (void **)realloc(stack->data, sizeof(void *) * new_capacity);
    if (!new_data)
    {
        return STACK_MEMORY_ERROR;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;

    return STACK_SUCCESS;
}