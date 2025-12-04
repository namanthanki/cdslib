#include "algorithms.h"
#include <stdlib.h>

void *binary_search(const void *key, const void *base, size_t num, size_t size, compare_func_t compar)
{
    const char *ptr = (const char *)base;
    int low = 0;
    int high = num - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        const void *mid_elem = ptr + mid * size;
        int cmp = compar(key, mid_elem);

        if (cmp == 0)
        {
            return (void *)mid_elem;
        }
        else if (cmp < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return NULL;
}
