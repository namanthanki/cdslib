#include "stack.h"

stack_t *create_stack(size_t element_size) {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stack -> data = (void **) malloc(sizeof(void *) * 10);
    stack -> top = -1;
    stack -> capacity = 10;
    stack -> element_size = element_size;

    return stack;
}

void push(stack_t *stack, void *element) {
    if (stack -> top == stack -> capacity - 1) {
        stack -> data = (void **) realloc(stack -> data, sizeof(void *) * stack -> capacity * 2);
        stack -> capacity *= 2;
    }

    stack -> top++;
    stack -> data[stack -> top] = (void *) malloc(stack -> element_size);
    memcpy(stack -> data[stack -> top], element, stack -> element_size);
}

void pop(stack_t *stack, void *output) {
    if (stack -> top == -1) {
        return;
    }

    memcpy(output, stack -> data[stack -> top], stack -> element_size);
    free(stack -> data[stack -> top]);
    stack -> top--;
}

void peek(stack_t *stack, void *output) {
    if (stack -> top == -1) {
        return;
    }

    memcpy(output, stack -> data[stack -> top], stack -> element_size);
}

void free_stack(stack_t *stack) {
    for (int i = 0; i <= stack -> top; i++) {
        free(stack -> data[i]);
    }

    free(stack -> data);
    free(stack);
}