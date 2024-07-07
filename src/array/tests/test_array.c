#include <stdio.h>
#include <string.h>
#include "array.h"

void test_char_array()
{
    printf("Testing char array...\n");

    array_t *arr = create_char_array();
    if (!arr)
    {
        printf("Failed to create char array\n");
        return;
    }

    char element = 'a';
    if (insert_char(arr, 0, element) == ARRAY_SUCCESS)
    {
        printf("Inserted '%c' into char array\n", element);
    }
    else
    {
        printf("Failed to insert '%c' into char array\n", element);
    }

    char output;
    if (get_char(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Got '%c' from char array\n", output);
    }
    else
    {
        printf("Failed to get from char array\n");
    }

    if (remove_char(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Removed '%c' from char array\n", output);
    }
    else
    {
        printf("Failed to remove from char array\n");
    }

    free_array(arr);
    printf("Char array test complete\n\n");
}

void test_int_array()
{
    printf("Testing int array...\n");

    array_t *arr = create_int_array();
    if (!arr)
    {
        printf("Failed to create int array\n");
        return;
    }

    int element = 10;
    if (insert_int(arr, 0, element) == ARRAY_SUCCESS)
    {
        printf("Inserted %d into int array\n", element);
    }
    else
    {
        printf("Failed to insert %d into int array\n", element);
    }

    int output;
    if (get_int(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Got %d from int array\n", output);
    }
    else
    {
        printf("Failed to get from int array\n");
    }

    if (remove_int(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Removed %d from int array\n", output);
    }
    else
    {
        printf("Failed to remove from int array\n");
    }

    free_array(arr);
    printf("Int array test complete\n\n");
}

void test_float_array()
{
    printf("Testing float array...\n");

    array_t *arr = create_float_array();
    if (!arr)
    {
        printf("Failed to create float array\n");
        return;
    }

    float element = 10.5;
    if (insert_float(arr, 0, element) == ARRAY_SUCCESS)
    {
        printf("Inserted %f into float array\n", element);
    }
    else
    {
        printf("Failed to insert %f into float array\n", element);
    }

    float output;
    if (get_float(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Got %f from float array\n", output);
    }
    else
    {
        printf("Failed to get from float array\n");
    }

    if (remove_float(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Removed %f from float array\n", output);
    }
    else
    {
        printf("Failed to remove from float array\n");
    }

    free_array(arr);
    printf("Float array test complete\n\n");
}

void test_double_array()
{
    printf("Testing double array...\n");

    array_t *arr = create_double_array();
    if (!arr)
    {
        printf("Failed to create double array\n");
        return;
    }

    double element = 10.5;
    if (insert_double(arr, 0, element) == ARRAY_SUCCESS)
    {
        printf("Inserted %f into double array\n", element);
    }
    else
    {
        printf("Failed to insert %f into double array\n", element);
    }

    double output;
    if (get_double(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Got %f from double array\n", output);
    }
    else
    {
        printf("Failed to get from double array\n");
    }

    if (remove_double(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Removed %f from double array\n", output);
    }
    else
    {
        printf("Failed to remove from double array\n");
    }

    free_array(arr);
    printf("Double array test complete\n\n");
}

void test_string_array()
{
    printf("Testing string array...\n");

    array_t *arr = create_string_array();
    if (!arr)
    {
        printf("Failed to create string array\n");
        return;
    }

    char *element = "Hello, World!";
    if (insert_string(arr, 0, element) == ARRAY_SUCCESS)
    {
        printf("Inserted \"%s\" into string array\n", element);
    }
    else
    {
        printf("Failed to insert \"%s\" into string array\n", element);
    }

    char *output;
    if (get_string(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Got \"%s\" from string array\n", output);
    }
    else
    {
        printf("Failed to get from string array\n");
    }

    if (remove_string(arr, 0, &output) == ARRAY_SUCCESS)
    {
        printf("Removed \"%s\" from string array\n", output);
    }
    else
    {
        printf("Failed to remove from string array\n");
    }

    free_array(arr);
    printf("String array test complete\n\n");
}

void test_string_array_extended()
{
    printf("Testing string array extended...\n");

    array_t *arr = create_string_array();
    if (!arr)
    {
        printf("Failed to create string array\n");
        return;
    }

    // Test get and remove on empty array
    char *output = NULL;
    if (get_string(arr, 0, &output) == ARRAY_INDEX_OUT_OF_BOUNDS)
    {
        printf("Got from empty string array\n");
    }
    else
    {
        printf("Failed to get from empty string array\n");
    }

    if (remove_string(arr, 0, &output) == ARRAY_INDEX_OUT_OF_BOUNDS)
    {
        printf("Removed from empty string array\n");
    }
    else
    {
        printf("Failed to remove from empty string array\n");
    }

    // Insert multiple elements
    char *elements[] = {"Hello", "World", "Goodbye"};
    for (int i = 0; i < 3; i++)
    {
        if (insert_string(arr, i, elements[i]) == ARRAY_SUCCESS)
        {
            printf("Inserted \"%s\" into string array\n", elements[i]);
        }
        else
        {
            printf("Failed to insert \"%s\" into string array\n", elements[i]);
        }
    }

    // Loop through array
    for (size_t i = 0; i < arr->size; i++)
    {
        if (get_string(arr, i, &output) == ARRAY_SUCCESS)
        {
            printf("Got \"%s\" from string array\n", output);
        }
        else
        {
            printf("Failed to get from string array\n");
        }
    }

    // Remove all
    size_t size = arr->size;
    for (size_t i = 0; i < size; i++)
    {
        if (remove_string(arr, 0, &output) == ARRAY_SUCCESS)
        {
            printf("Removed \"%s\" from string array\n", output);
        }
        else
        {
            printf("Failed to remove from string array\n");
        }
    }

    // Test get and remove on empty array
    if (get_string(arr, 0, &output) == ARRAY_INDEX_OUT_OF_BOUNDS)
    {
        printf("Index out of bounds\n");
    }
    else
    {
        printf("Failed to get from empty string array\n");
    }

    if (remove_string(arr, 0, &output) == ARRAY_INDEX_OUT_OF_BOUNDS)
    {
        printf("Index out of bounds\n");
    }
    else
    {
        printf("Failed to remove from empty string array\n");
    }

    free_string_array(arr);
    printf("String array extended test complete\n\n");
}

int main()
{
    test_char_array();
    test_int_array();
    test_float_array();
    test_double_array();
    test_string_array();
    test_string_array_extended();

    return 0;
}