#include "algorithms.h"
#include <stdlib.h>
#include <string.h>

// Helper for swap
static void swap(void *a, void *b, size_t size)
{
    char buffer[size];
    memcpy(buffer, a, size);
    memcpy(a, b, size);
    memcpy(b, buffer, size);
}

// Quick Sort Implementation
static void quick_sort_recursive(char *base, size_t size, int low, int high, compare_func_t compar)
{
    if (low < high)
    {
        // Partition
        char *pivot = base + high * size;
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (compar(base + j * size, pivot) < 0)
            {
                i++;
                swap(base + i * size, base + j * size, size);
            }
        }
        swap(base + (i + 1) * size, base + high * size, size);
        
        int pi = i + 1;

        quick_sort_recursive(base, size, low, pi - 1, compar);
        quick_sort_recursive(base, size, pi + 1, high, compar);
    }
}

void quick_sort(void *base, size_t num, size_t size, compare_func_t compar)
{
    if (num > 1)
    {
        quick_sort_recursive((char *)base, size, 0, num - 1, compar);
    }
}

// Merge Sort Implementation
static void merge(char *base, size_t size, int left, int mid, int right, compare_func_t compar)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char *L = malloc(n1 * size);
    char *R = malloc(n2 * size);

    if (!L || !R)
    {
        // Handle memory error gracefully (in a real lib, we might return error code)
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++)
        memcpy(L + i * size, base + (left + i) * size, size);
    for (int j = 0; j < n2; j++)
        memcpy(R + j * size, base + (mid + 1 + j) * size, size);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (compar(L + i * size, R + j * size) <= 0)
        {
            memcpy(base + k * size, L + i * size, size);
            i++;
        }
        else
        {
            memcpy(base + k * size, R + j * size, size);
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        memcpy(base + k * size, L + i * size, size);
        i++;
        k++;
    }

    while (j < n2)
    {
        memcpy(base + k * size, R + j * size, size);
        j++;
        k++;
    }

    free(L);
    free(R);
}

static void merge_sort_recursive(char *base, size_t size, int left, int right, compare_func_t compar)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort_recursive(base, size, left, mid, compar);
        merge_sort_recursive(base, size, mid + 1, right, compar);

        merge(base, size, left, mid, right, compar);
    }
}

void merge_sort(void *base, size_t num, size_t size, compare_func_t compar)
{
    if (num > 1)
    {
        merge_sort_recursive((char *)base, size, 0, num - 1, compar);
    }
}
