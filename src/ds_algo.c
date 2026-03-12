#include "ds/ds_algo.h"
#include <stdlib.h>
#include <string.h>

static void ds_algo_swap(void *a, void *b, size_t size) {
    char *ca = (char *)a;
    char *cb = (char *)b;
    for (size_t i = 0; i < size; i++) {
        char temp = ca[i];
        ca[i] = cb[i];
        cb[i] = temp;
    }
}

static void ds_algo_quicksort_impl(void *base, size_t low, size_t high, size_t element_size, int (*cmp)(const void *, const void *)) {
    if (low < high) {
        char *pivot = (char *)base + high * element_size;
        size_t i = low;
        for (size_t j = low; j < high; j++) {
            if (cmp((char *)base + j * element_size, pivot) < 0) {
                ds_algo_swap((char *)base + i * element_size, (char *)base + j * element_size, element_size);
                i++;
            }
        }
        ds_algo_swap((char *)base + i * element_size, (char *)base + high * element_size, element_size);
        
        if (i > 0) {
            ds_algo_quicksort_impl(base, low, i - 1, element_size, cmp);
        }
        ds_algo_quicksort_impl(base, i + 1, high, element_size, cmp);
    }
}

void ds_algo_quicksort(void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *)) {
    if (count > 1) {
        ds_algo_quicksort_impl(base, 0, count - 1, element_size, cmp);
    }
}

static ds_error_t ds_algo_merge(void *base, size_t low, size_t mid, size_t high, size_t element_size, int (*cmp)(const void *, const void *)) {
    size_t n1 = mid - low + 1;
    size_t n2 = high - mid;

    char *L = (char *)malloc(n1 * element_size);
    if (!L) return DS_ERR_ALLOC;

    char *R = (char *)malloc(n2 * element_size);
    if (!R) {
        free(L);
        return DS_ERR_ALLOC;
    }

    for (size_t i = 0; i < n1; i++) {
        memcpy(L + i * element_size, (char *)base + (low + i) * element_size, element_size);
    }
    for (size_t j = 0; j < n2; j++) {
        memcpy(R + j * element_size, (char *)base + (mid + 1 + j) * element_size, element_size);
    }

    size_t i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (cmp(L + i * element_size, R + j * element_size) <= 0) {
            memcpy((char *)base + k * element_size, L + i * element_size, element_size);
            i++;
        } else {
            memcpy((char *)base + k * element_size, R + j * element_size, element_size);
            j++;
        }
        k++;
    }

    while (i < n1) {
        memcpy((char *)base + k * element_size, L + i * element_size, element_size);
        i++;
        k++;
    }

    while (j < n2) {
        memcpy((char *)base + k * element_size, R + j * element_size, element_size);
        j++;
        k++;
    }

    free(L);
    free(R);
    return DS_SUCCESS;
}

static ds_error_t ds_algo_mergesort_impl(void *base, size_t low, size_t high, size_t element_size, int (*cmp)(const void *, const void *)) {
    if (low < high) {
        size_t mid = low + (high - low) / 2;
        ds_error_t err;
        
        err = ds_algo_mergesort_impl(base, low, mid, element_size, cmp);
        if (err != DS_SUCCESS) return err;
        
        err = ds_algo_mergesort_impl(base, mid + 1, high, element_size, cmp);
        if (err != DS_SUCCESS) return err;
        
        return ds_algo_merge(base, low, mid, high, element_size, cmp);
    }
    return DS_SUCCESS;
}

ds_error_t ds_algo_mergesort(void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *)) {
    if (count > 1) {
        return ds_algo_mergesort_impl(base, 0, count - 1, element_size, cmp);
    }
    return DS_SUCCESS;
}

void *ds_algo_binary_search(const void *key, const void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *)) {
    size_t low = 0;
    size_t high = count - 1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        char *mid_elem = (char *)base + mid * element_size;
        int res = cmp(key, mid_elem);

        if (res == 0) {
            return mid_elem;
        } else if (res < 0) {
            if (mid == 0) break;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return NULL;
}

static void ds_algo_heapify_impl(void *base, size_t count, size_t i, size_t element_size, int (*cmp)(const void *, const void *)) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < count && cmp((char *)base + left * element_size, (char *)base + largest * element_size) > 0) {
        largest = left;
    }

    if (right < count && cmp((char *)base + right * element_size, (char *)base + largest * element_size) > 0) {
        largest = right;
    }

    if (largest != i) {
        ds_algo_swap((char *)base + i * element_size, (char *)base + largest * element_size, element_size);
        ds_algo_heapify_impl(base, count, largest, element_size, cmp);
    }
}

void ds_algo_heapify(void *base, size_t count, size_t element_size, int (*cmp)(const void *, const void *)) {
    for (size_t i = count / 2; i > 0; i--) {
        ds_algo_heapify_impl(base, count, i - 1, element_size, cmp);
    }
}
