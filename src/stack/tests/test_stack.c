#include <stdio.h>
#include <string.h>
#include "stack.h"

void test_char_stack()
{
    printf("Testing char stack...\n");

    stack_t *stack = create_char_stack();
    if (!stack)
    {
        printf("Failed to create char stack\n");
        return;
    }

    char value = 'a';
    if (push_char(stack, value) == STACK_SUCCESS)
    {
        printf("Pushed '%c' onto char stack\n", value);
    }
    else
    {
        printf("Failed to push '%c' onto char stack\n", value);
    }

    char output;
    if (peek_char(stack, &output) == STACK_SUCCESS)
    {
        printf("Peeked '%c' from char stack\n", output);
    }
    else
    {
        printf("Failed to peek from char stack\n");
    }

    if (pop_char(stack, &output) == STACK_SUCCESS)
    {
        printf("Popped '%c' from char stack\n", output);
    }
    else
    {
        printf("Failed to pop from char stack\n");
    }

    free_stack(stack);
    printf("Char stack test complete\n\n");
}

void test_int_stack()
{
    printf("Testing int stack...\n");

    stack_t *stack = create_int_stack();
    if (!stack)
    {
        printf("Failed to create int stack\n");
        return;
    }

    int value = 10;
    if (push_int(stack, value) == STACK_SUCCESS)
    {
        printf("Pushed %d onto int stack\n", value);
    }
    else
    {
        printf("Failed to push %d onto int stack\n", value);
    }

    int output;
    if (peek_int(stack, &output) == STACK_SUCCESS)
    {
        printf("Peeked %d from int stack\n", output);
    }
    else
    {
        printf("Failed to peek from int stack\n");
    }

    if (pop_int(stack, &output) == STACK_SUCCESS)
    {
        printf("Popped %d from int stack\n", output);
    }
    else
    {
        printf("Failed to pop from int stack\n");
    }

    free_stack(stack);
    printf("Int stack test complete\n\n");
}

void test_float_stack()
{
    printf("Testing float stack...\n");

    stack_t *stack = create_float_stack();
    if (!stack)
    {
        printf("Failed to create float stack\n");
        return;
    }

    float value = 10.5f;
    if (push_float(stack, value) == STACK_SUCCESS)
    {
        printf("Pushed %f onto float stack\n", value);
    }
    else
    {
        printf("Failed to push %f onto float stack\n", value);
    }

    float output;
    if (peek_float(stack, &output) == STACK_SUCCESS)
    {
        printf("Peeked %f from float stack\n", output);
    }
    else
    {
        printf("Failed to peek from float stack\n");
    }

    if (pop_float(stack, &output) == STACK_SUCCESS)
    {
        printf("Popped %f from float stack\n", output);
    }
    else
    {
        printf("Failed to pop from float stack\n");
    }

    free_stack(stack);
    printf("Float stack test complete\n\n");
}

void test_double_stack()
{
    printf("Testing double stack...\n");

    stack_t *stack = create_double_stack();
    if (!stack)
    {
        printf("Failed to create double stack\n");
        return;
    }

    double value = 20.25;
    if (push_double(stack, value) == STACK_SUCCESS)
    {
        printf("Pushed %f onto double stack\n", value);
    }
    else
    {
        printf("Failed to push %f onto double stack\n", value);
    }

    double output;
    if (peek_double(stack, &output) == STACK_SUCCESS)
    {
        printf("Peeked %f from double stack\n", output);
    }
    else
    {
        printf("Failed to peek from double stack\n");
    }

    if (pop_double(stack, &output) == STACK_SUCCESS)
    {
        printf("Popped %f from double stack\n", output);
    }
    else
    {
        printf("Failed to pop from double stack\n");
    }

    free_stack(stack);
    printf("Double stack test complete\n\n");
}

void test_string_stack()
{
    printf("Testing string stack...\n");

    stack_t *stack = create_string_stack();
    if (!stack)
    {
        printf("Failed to create string stack\n");
        return;
    }

    const char *value = "hello";
    if (push_string(stack, value) == STACK_SUCCESS)
    {
        printf("Pushed \"%s\" onto string stack\n", value);
    }
    else
    {
        printf("Failed to push \"%s\" onto string stack\n", value);
    }

    char *output = NULL;
    if (peek_string(stack, &output) == STACK_SUCCESS)
    {
        printf("Peeked \"%s\" from string stack\n", output);
    }
    else
    {
        printf("Failed to peek from string stack\n");
    }

    if (pop_string(stack, &output) == STACK_SUCCESS)
    {
        printf("Popped \"%s\" from string stack\n", output);
        free(output); // Free the duplicated string
    }
    else
    {
        printf("Failed to pop from string stack\n");
    }

    free_string_stack(stack);
    printf("String stack test complete\n\n");
}

void test_string_stack_extended()
{
    printf("Extended testing of string stack...\n");

    stack_t *stack = create_string_stack();
    if (!stack)
    {
        printf("Failed to create string stack\n");
        return;
    }

    // Test peek and pop on empty stack
    char *output = NULL;
    if (peek_string(stack, &output) == STACK_UNDERFLOW)
    {
        printf("Correctly failed to peek from empty stack\n");
    }
    if (pop_string(stack, &output) == STACK_UNDERFLOW)
    {
        printf("Correctly failed to pop from empty stack\n");
    }

    // Push multiple strings
    const char *values[] = {"first", "second", "third", "fourth", "fifth"};
    for (int i = 0; i < 5; i++)
    {
        if (push_string(stack, values[i]) == STACK_SUCCESS)
        {
            printf("Pushed \"%s\" onto string stack\n", values[i]);
        }
    }

    // Peek and pop in reverse order
    for (int i = 4; i >= 0; i--)
    {
        if (peek_string(stack, &output) == STACK_SUCCESS)
        {
            printf("Peeked \"%s\" from string stack\n", output);
        }
        if (pop_string(stack, &output) == STACK_SUCCESS)
        {
            printf("Popped \"%s\" from string stack\n", output);
            free(output);
        }
    }

    free_string_stack(stack);
    printf("Extended string stack test complete\n\n");
}

int main()
{
    test_char_stack();
    test_int_stack();
    test_float_stack();
    test_double_stack();
    test_string_stack();
    test_string_stack_extended();

    return 0;
}