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

int push(stack_t *stack, void *element)
{
    if (stack->top == stack->capacity - 1)
    {
        void **new_data = (void **)realloc(stack->data, sizeof(void *) * stack->capacity * 2);
        if (!new_data)
        {
            return -1;
        }

        stack->data = new_data;
        stack->capacity *= 2;
    }

    stack->top++;
    stack->data[stack->top] = (void *)malloc(stack->element_size);
    if (!stack->data[stack->top])
    {
        return -1;
    }
    memcpy(stack->data[stack->top], element, stack->element_size);
    return 0;
}

int pop(stack_t *stack, void *output)
{
    if (stack->top == -1)
    {
        return -1;
    }

    memcpy(output, stack->data[stack->top], stack->element_size);
    free(stack->data[stack->top]);
    stack->top--;

    return 0;
}

int peek(stack_t *stack, void *output)
{
    if (stack->top == -1)
    {
        return -1;
    }

    memcpy(output, stack->data[stack->top], stack->element_size);

    return 0;
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