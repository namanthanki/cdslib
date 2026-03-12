#ifndef DS_ALGO_H
#define DS_ALGO_H

#include "ds_common.h"

void ds_algo_quicksort(void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *));
ds_error_t ds_algo_mergesort(void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *));
void *ds_algo_binary_search(const void *key, const void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *));
void ds_algo_heapify(void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *));

#endif /* DS_ALGO_H */
