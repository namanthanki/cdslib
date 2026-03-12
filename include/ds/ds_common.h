#ifndef DS_COMMON_H
#define DS_COMMON_H

#include <stddef.h>

#define DS_VERSION_MAJOR 1
#define DS_VERSION_MINOR 0
#define DS_VERSION_PATCH 0

typedef enum {
    DS_SUCCESS = 0,
    DS_ERR_ALLOC,
    DS_ERR_OUT_OF_RANGE,
    DS_ERR_EMPTY,
    DS_ERR_INVALID_ARG
} ds_error_t;

typedef void* (*ds_malloc_fn)(size_t);
typedef void  (*ds_free_fn)(void*);

#endif /* DS_COMMON_H */
