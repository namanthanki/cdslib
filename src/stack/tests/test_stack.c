#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// int main() {
//     stack_t *stack = create_stack(sizeof(int));

//     int data = 5;
//     push(stack, &data);

//     int output;
//     pop(stack, &output);
//     printf("%d\n", output);

//     free_stack(stack);

//     return 0;
// }

// int main() {
//     stack_t *stack = create_stack(sizeof(char)); // Change to sizeof(char)

//     char data = 'a';
//     push(stack, &data);

//     char output;
//     pop(stack, &output);

//     printf("%c\n", output); // Use %c for char

//     free_stack(stack);
//     return 0;
// }

int main() {
    stack_t *stack = create_stack(sizeof(char *));

    char *data = strdup("Hello, World!");
    push(stack, &data);

    char *output;
    pop(stack, &output);
    printf("%s\n", output);

    free(data);
    free_stack(stack);
    return 0;
}