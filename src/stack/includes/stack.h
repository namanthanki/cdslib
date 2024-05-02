#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;
    int top;
    int capacity;
    size_t element_size;
} stack_t;

stack_t *create_stack(size_t element_size);
void push(stack_t *stack, void *element);
void pop(stack_t *stack, void *output);
void peek(stack_t *stack, void *output);
void free_stack(stack_t *stack);

#endif