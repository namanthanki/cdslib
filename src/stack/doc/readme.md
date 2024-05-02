# Stack Implementation in C

This project contains a simple implementation of a stack data structure in C.

## Overview

A stack is a linear data structure that follows the LIFO (Last In First Out) principle. The operations are performed based on this principle. It contains two main operations push and pop.

## Features

1. **create_stack**: This function creates a new stack with a specified element size. It returns a pointer to the newly created stack.
2. **push**: This function adds an element to the stack. If the stack is full, it reallocates memory to double the capacity of the stack.
3. **pop**: This function removes an element from the stack and copies it to the output pointer. If the stack is empty, it simply returns without doing anything.
4. **peek**: This function copies the top element of the stack to the output pointer. If the stack is empty, it simply returns without doing anything.
5. **free_stack**: This function frees all the memory allocated for the stack.

## Usage

To use this stack implementation, you need to include "stack.h" and call the appropriate functions. Here is an example:

```c
stack_t *stack = create_stack(sizeof(int));
int element = 10;
push(stack, &element);
int output;
pop(stack, &output);
printf("%d\n", output);  // prints 10
free_stack(stack);