#include "algorithms.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int compare_ints(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

void test_quick_sort()
{
    printf("Testing Quick Sort...\n");
    int arr[] = {5, 2, 9, 1, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, size, sizeof(int), compare_ints);

    for (size_t i = 0; i < size - 1; i++)
    {
        assert(arr[i] <= arr[i + 1]);
    }
    printf("Quick Sort passed.\n");
}

void test_merge_sort()
{
    printf("Testing Merge Sort...\n");
    int arr[] = {10, -1, 4, 2, 0, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, size, sizeof(int), compare_ints);

    for (size_t i = 0; i < size - 1; i++)
    {
        assert(arr[i] <= arr[i + 1]);
    }
    printf("Merge Sort passed.\n");
}

void test_binary_search()
{
    printf("Testing Binary Search...\n");
    int arr[] = {1, 3, 5, 7, 9, 11};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int key = 7;
    int *result = (int *)binary_search(&key, arr, size, sizeof(int), compare_ints);
    assert(result != NULL);
    assert(*result == 7);

    key = 4;
    result = (int *)binary_search(&key, arr, size, sizeof(int), compare_ints);
    assert(result == NULL);

    printf("Binary Search passed.\n");
}

int main()
{
    test_quick_sort();
    test_merge_sort();
    test_binary_search();
    printf("All algorithm tests passed!\n");
    return 0;
}
