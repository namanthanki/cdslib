#include <stdio.h>
#include <string.h>
#include "singly_linked_list.h"

void test_char_list()
{
    printf("Testing char list...\n");

    singly_linked_list_t *list = create_char_singly_linked_list();

    for (char c = 'a'; c <= 'z'; c++)
    {
        insert_back_char(list, c);
    }

    char output;
    get_char(list, 0, &output);
    printf("First element: %c\n", output);

    get_char(list, 25, &output);
    printf("Last element: %c\n", output);

    printf("Removing first element...\n");
    remove_front_char(list, &output);
    printf("First element: %c\n", output);

    printf("Removing last element...\n");
    remove_back_char(list, &output);

    printf("Last element: %c\n", output);

    printf("List size: %zu\n", singly_linked_list_size(list));

    free_singly_linked_list(list);

    printf("Char list test finished.\n");
}

void test_int_list()
{
    printf("Testing int list...\n");

    singly_linked_list_t *list = create_int_singly_linked_list();

    for (int i = 0; i < 10; i++)
    {
        insert_back_int(list, i);
    }

    int output;
    get_int(list, 0, &output);
    printf("First element: %d\n", output);

    get_int(list, 9, &output);
    printf("Last element: %d\n", output);

    printf("Removing first element...\n");
    remove_front_int(list, &output);
    printf("First element: %d\n", output);

    printf("Removing last element...\n");
    remove_back_int(list, &output);

    printf("Last element: %d\n", output);

    printf("List size: %zu\n", singly_linked_list_size(list));

    free_singly_linked_list(list);

    printf("Int list test finished.\n");
}

void test_float_list()
{
    printf("Testing float list...\n");

    singly_linked_list_t *list = create_float_singly_linked_list();

    for (float i = 0.0; i < 10.0; i++)
    {
        insert_back_float(list, i);
    }

    float output;
    get_float(list, 0, &output);
    printf("First element: %f\n", output);

    get_float(list, 9, &output);
    printf("Last element: %f\n", output);

    printf("Removing first element...\n");
    remove_front_float(list, &output);
    printf("First element: %f\n", output);

    printf("Removing last element...\n");
    remove_back_float(list, &output);

    printf("Last element: %f\n", output);

    printf("List size: %zu\n", singly_linked_list_size(list));

    free_singly_linked_list(list);

    printf("Float list test finished.\n");
}

void test_double_list()
{
    printf("Testing double list...\n");

    singly_linked_list_t *list = create_double_singly_linked_list();

    for (double i = 0.0; i < 10.0; i++)
    {
        insert_back_double(list, i);
    }

    double output;
    get_double(list, 0, &output);
    printf("First element: %f\n", output);

    get_double(list, 9, &output);
    printf("Last element: %f\n", output);

    printf("Removing first element...\n");
    remove_front_double(list, &output);
    printf("First element: %f\n", output);

    printf("Removing last element...\n");
    remove_back_double(list, &output);

    printf("Last element: %f\n", output);

    printf("List size: %zu\n", singly_linked_list_size(list));

    free_singly_linked_list(list);

    printf("Double list test finished.\n");
}

void test_string_list()
{
    printf("Testing string list...\n");

    singly_linked_list_t *list = create_string_singly_linked_list();

    insert_back_string(list, "Hello");
    insert_back_string(list, "World");

    char *output;
    get_string(list, 0, &output);
    printf("First element: %s\n", output);

    get_string(list, 1, &output);
    printf("Last element: %s\n", output);

    printf("Removing first element...\n");
    remove_front_string(list, &output);
    printf("First element: %s\n", output);

    printf("Removing last element...\n");
    remove_back_string(list, &output);

    printf("Last element: %s\n", output);

    printf("List size: %zu\n", singly_linked_list_size(list));

    free_string_singly_linked_list(list);

    printf("String list test finished.\n");
}

int main()
{
    printf("Singly linked list tests:\n");

    test_char_list();
    test_int_list();
    test_float_list();
    test_double_list();
    test_string_list();
    return 0;
}