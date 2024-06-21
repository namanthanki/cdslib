# Stack Implementation in C

This project provides a flexible and efficient implementation of a stack data structure in C, supporting various data types.

## Overview

A stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle. This implementation offers core stack operations and additional features for different data types.

## Features

1.  **Generic Stack Creation**: Create stacks for various data types (int, float, double, char, string).
2.  **Dynamic Resizing**: Automatically doubles capacity when the stack is full.
3.  **Type-Specific Operations**: Tailored push, pop, and peek functions for each supported data type.
4.  **Memory Management**: Proper allocation and deallocation of resources.
5.  **Error Handling**: Graceful handling of empty stack operations and memory allocation failures.

## Core Functions

-   `create_stack(size_t element_size)`: Creates a new stack for elements of the specified size.
-   `push(stack_t *stack, void *element)`: Adds an element to the top of the stack.
-   `pop(stack_t *stack, void *output)`: Removes and returns the top element from the stack.
-   `peek(stack_t *stack, void *output)`: Returns the top element without removing it.
-   `free_stack(stack_t *stack)`: Frees all memory associated with the stack.

## Type-Specific Functions

For each supported data type (int, float, double, char, string), there are specialized functions:

-   `create_[type]_stack()`
-   `push_[type](stack_t *stack, [type] value)`
-   `pop_[type](stack_t *stack, [type] *value)`
-   `peek_[type](stack_t *stack, [type] *value)`

Where `[type]` is one of: int, float, double, char, or string.

## Usage Example

```c
#include  "stack.h" 
#include  <stdio.h>   
int  main()  {   
    // Integer stack example stack_t  
    *int_stack =  create_int_stack(); push_int(int_stack,  10); 
    push_int(int_stack,  20);  
    int value; pop_int(int_stack,  &value); 
    printf("Popped integer: %d\n", value);  
    // Output: 20   
    
    // String stack example stack_t  
    *string_stack =  create_string_stack(); 
    push_string(string_stack,  "Hello"); 
    push_string(string_stack,  "World");   
    char  *str; 
    peek_string(string_stack,  &str); 
    printf("Peeked string: %s\n", str);  
    // Output: World   
    pop_string(string_stack,  &str); 
    printf("Popped string: %s\n", str);  
    // Output: World 
    free(str);  // Don't forget to free the popped string   
    // Clean up 
    free_stack(int_stack); 
    free_stack(string_stack);   
    return  0; 
}
```

## Error Handling

-   Functions return 0 on success and -1 on failure.
-   Trying to pop or peek from an empty stack will return -1.
-   If memory allocation fails during push or stack creation, the function will return -1.

## Memory Management

-   The `free_stack` function should be called when a stack is no longer needed to prevent memory leaks.
-   For string stacks, remember to free the strings returned by pop_string.

## Limitations

-   The stack has a maximum capacity determined by available memory.
-   It's the user's responsibility to ensure type safety when using the generic stack functions.

## Future Improvements

-   Add thread-safety for concurrent access.
-   Implement iterator functionality for stack traversal.
-   Add more comprehensive error codes and messages.

This implementation provides a robust and flexible stack data structure suitable for various C programming needs.