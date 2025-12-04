#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stddef.h>

// Comparison function type
// Returns < 0 if a < b, > 0 if a > b, 0 if a == b
typedef int (*compare_func_t)(const void *a, const void *b);

// Sorting
void quick_sort(void *base, size_t num, size_t size, compare_func_t compar);
void merge_sort(void *base, size_t num, size_t size, compare_func_t compar);

// Searching
// Returns pointer to matching element or NULL if not found
void *binary_search(const void *key, const void *base, size_t num, size_t size, compare_func_t compar);

#endif // ALGORITHMS_H
