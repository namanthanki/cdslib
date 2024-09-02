#include <stdio.h>
#include <string.h>
#include "circular_linked_list.h"

void test_char_circular_list()
{
    printf("Testing char list...\n");

    circular_linked_list_t *list = create_char_circular_linked_list();

    for (char c = 'a'; c <= 'z'; c++)
    {
        insert_back_char_circular(list, c);
    }

    char output;
    get_char_circular(list, 0, &output);
    printf("First element: %c\n", output);

    get_char_circular(list, 25, &output);
    printf("Last element: %c\n", output);

    printf("Removing first element...\n");
    remove_front_char_circular(list, &output);
    printf("First element: %c\n", output);

    printf("Removing last element...\n");
    remove_back_char_circular(list, &output);

    printf("Last element: %c\n", output);

    printf("List size: %zu\n", circular_linked_list_size(list));

    free_circular_linked_list(list);

    printf("Char list test finished.\n");
}

void test_int_circular_list()
{
    printf("Testing int list...\n");

    circular_linked_list_t *list = create_int_circular_linked_list();

    for (int i = 0; i < 10; i++)
    {
        insert_back_int_circular(list, i);
    }

    int output;
    get_int_circular(list, 0, &output);
    printf("First element: %d\n", output);

    get_int_circular(list, 9, &output);
    printf("Last element: %d\n", output);

    printf("Removing first element...\n");
    remove_front_int_circular(list, &output);
    printf("First element: %d\n", output);

    printf("Removing last element...\n");
    remove_back_int_circular(list, &output);

    printf("Last element: %d\n", output);

    printf("List size: %zu\n", circular_linked_list_size(list));

    free_circular_linked_list(list);

    printf("Int list test finished.\n");
}

void test_float_circular_list()
{
    printf("Testing float list...\n");

    circular_linked_list_t *list = create_float_circular_linked_list();

    for (float i = 0.0; i < 10.0; i++)
    {
        insert_back_float_circular(list, i);
    }

    float output;
    get_float_circular(list, 0, &output);
    printf("First element: %f\n", output);

    get_float_circular(list, 9, &output);
    printf("Last element: %f\n", output);

    printf("Removing first element...\n");
    remove_front_float_circular(list, &output);
    printf("First element: %f\n", output);

    printf("Removing last element...\n");
    remove_back_float_circular(list, &output);

    printf("Last element: %f\n", output);

    printf("List size: %zu\n", circular_linked_list_size(list));

    free_circular_linked_list(list);

    printf("Float list test finished.\n");
}

void test_double_circular_list()
{
    printf("Testing double list...\n");

    circular_linked_list_t *list = create_double_circular_linked_list();

    for (double i = 0.0; i < 10.0; i++)
    {
        insert_back_double_circular(list, i);
    }

    double output;
    get_double_circular(list, 0, &output);
    printf("First element: %f\n", output);

    get_double_circular(list, 9, &output);
    printf("Last element: %f\n", output);

    printf("Removing first element...\n");
    remove_front_double_circular(list, &output);
    printf("First element: %f\n", output);

    printf("Removing last element...\n");
    remove_back_double_circular(list, &output);

    printf("Last element: %f\n", output);

    printf("List size: %zu\n", circular_linked_list_size(list));

    free_circular_linked_list(list);

    printf("Double list test finished.\n");
}

void test_string_circular_list()
{
    printf("Testing string list...\n");

    circular_linked_list_t *list = create_string_circular_linked_list();

    insert_back_string_circular(list, "Hello");
    insert_back_string_circular(list, "World");

    char *output;
    get_string_circular(list, 0, &output);
    printf("First element: %s\n", output);

    get_string_circular(list, 1, &output);
    printf("Last element: %s\n", output);

    printf("Removing first element...\n");
    remove_front_string_circular(list, &output);
    printf("First element: %s\n", output);

    printf("Removing last element...\n");
    remove_back_string_circular(list, &output);
    printf("Last element: %s\n", output);

    printf("List size: %zu\n", circular_linked_list_size(list));

    free_string_circular_linked_list(list);

    printf("String list test finished.\n");
}

int main()
{
    test_char_circular_list();
    test_int_circular_list();
    test_float_circular_list();
    test_double_circular_list();

    return 0;
}