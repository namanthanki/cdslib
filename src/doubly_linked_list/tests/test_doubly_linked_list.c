#include <stdio.h>
#include <string.h>
#include "doubly_linked_list.h"

void test_char_doubly_list()
{
    printf("Testing char list...\n");

    doubly_linked_list_t *list = create_char_doubly_linked_list();

    for (char c = 'a'; c <= 'z'; c++)
    {
        insert_back_char_doubly(list, c);
    }

    char output;
    get_char_doubly(list, 0, &output);
    printf("First element: %c\n", output);

    get_char_doubly(list, 25, &output);
    printf("Last element: %c\n", output);

    printf("Removing first element...\n");
    remove_front_char_doubly(list, &output);
    printf("First element: %c\n", output);

    printf("Removing last element...\n");
    remove_back_char_doubly(list, &output);

    printf("Last element: %c\n", output);

    printf("List size: %zu\n", doubly_linked_list_size(list));

    free_doubly_linked_list(list);

    printf("Char list test finished.\n");
}

void test_int_doubly_list()
{
    printf("Testing int list...\n");

    doubly_linked_list_t *list = create_int_doubly_linked_list();

    for (int i = 0; i < 10; i++)
    {
        insert_back_int_doubly(list, i);
    }

    int output;
    get_int_doubly(list, 0, &output);
    printf("First element: %d\n", output);

    get_int_doubly(list, 9, &output);
    printf("Last element: %d\n", output);

    printf("Removing first element...\n");
    remove_front_int_doubly(list, &output);
    printf("First element: %d\n", output);

    printf("Removing last element...\n");
    remove_back_int_doubly(list, &output);

    printf("Last element: %d\n", output);

    printf("List size: %zu\n", doubly_linked_list_size(list));

    free_doubly_linked_list(list);

    printf("Int list test finished.\n");
}

void test_float_doubly_list()
{
    printf("Testing float list...\n");

    doubly_linked_list_t *list = create_float_doubly_linked_list();

    for (float i = 0.0; i < 10.0; i++)
    {
        insert_back_float_doubly(list, i);
    }

    float output;
    get_float_doubly(list, 0, &output);
    printf("First element: %f\n", output);

    get_float_doubly(list, 9, &output);
    printf("Last element: %f\n", output);

    printf("Removing first element...\n");
    remove_front_float_doubly(list, &output);
    printf("First element: %f\n", output);

    printf("Removing last element...\n");
    remove_back_float_doubly(list, &output);

    printf("Last element: %f\n", output);

    printf("List size: %zu\n", doubly_linked_list_size(list));

    free_doubly_linked_list(list);

    printf("Float list test finished.\n");
}

void test_double_doubly_list()
{
    printf("Testing double list...\n");

    doubly_linked_list_t *list = create_double_doubly_linked_list();

    for (double i = 0.0; i < 10.0; i++)
    {
        insert_back_double_doubly(list, i);
    }

    double output;
    get_double_doubly(list, 0, &output);
    printf("First element: %f\n", output);

    get_double_doubly(list, 9, &output);
    printf("Last element: %f\n", output);

    printf("Removing first element...\n");
    remove_front_double_doubly(list, &output);
    printf("First element: %f\n", output);

    printf("Removing last element...\n");
    remove_back_double_doubly(list, &output);

    printf("Last element: %f\n", output);

    printf("List size: %zu\n", doubly_linked_list_size(list));

    free_doubly_linked_list(list);

    printf("Double list test finished.\n");
}

void test_string_doubly_list()
{
    printf("Testing string list...\n");

    doubly_linked_list_t *list = create_string_doubly_linked_list();

    insert_back_string_doubly(list, "Hello");
    insert_back_string_doubly(list, "World");

    char *output;
    get_string_doubly(list, 0, &output);
    printf("First element: %s\n", output);

    get_string_doubly(list, 1, &output);
    printf("Last element: %s\n", output);

    printf("Removing first element...\n");
    remove_front_string_doubly(list, &output);
    printf("First element: %s\n", output);

    printf("Removing last element...\n");
    remove_back_string_doubly(list, &output);

    printf("Last element: %s\n", output);

    printf("List size: %zu\n", doubly_linked_list_size(list));

    free_string_doubly_linked_list(list);

    printf("String list test finished.\n");
}

int main()
{
    printf("\nDoubly linked list tests:\n");

    test_char_doubly_list();
    test_int_doubly_list();
    test_float_doubly_list();
    test_double_doubly_list();
    test_string_doubly_list();
    return 0;
}