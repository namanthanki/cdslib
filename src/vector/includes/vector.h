#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef enum
{
    VECTOR_SUCCESS,
    VECTOR_MEMORY_ERROR,
    VECTOR_INDEX_OUT_OF_BOUNDS,
    VECTOR_EMPTY
} vector_error_t;

typedef struct
{
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} vector_t;

#define DECLARE_VECTOR_FUNCTIONS(TYPE, SUFFIX)                                    \
    vector_t *create_##SUFFIX##_vector();                                         \
    vector_error_t push_back_##SUFFIX(vector_t *vec, TYPE element);               \
    vector_error_t pop_back_##SUFFIX(vector_t *vec, TYPE *output);                \
    vector_error_t insert_##SUFFIX(vector_t *vec, size_t index, TYPE element);    \
    vector_error_t remove_##SUFFIX(vector_t *vec, size_t index, TYPE *output);    \
    vector_error_t get_##SUFFIX(vector_t *vec, size_t index, TYPE *output);       \
    vector_error_t set_##SUFFIX(vector_t *vec, size_t index, TYPE element);       \
    void free_##SUFFIX##_vector(vector_t *vec);

#define DECLARE_STRING_VECTOR_FUNCTIONS                                           \
    vector_t *create_string_vector();                                             \
    vector_error_t push_back_string(vector_t *vec, const char *element);          \
    vector_error_t pop_back_string(vector_t *vec, char **output);                 \
    vector_error_t insert_string(vector_t *vec, size_t index, const char *element);\
    vector_error_t remove_string(vector_t *vec, size_t index, char **output);     \
    vector_error_t get_string(vector_t *vec, size_t index, char **output);        \
    vector_error_t set_string(vector_t *vec, size_t index, const char *element);  \
    void free_string_vector(vector_t *vec);

DECLARE_VECTOR_FUNCTIONS(char, char)
DECLARE_VECTOR_FUNCTIONS(int, int)
DECLARE_VECTOR_FUNCTIONS(float, float)
DECLARE_VECTOR_FUNCTIONS(double, double)
DECLARE_STRING_VECTOR_FUNCTIONS

// Generic functions
vector_t *create_vector(size_t element_size);
vector_error_t vector_push_back(vector_t *vec, void *element);
vector_error_t vector_pop_back(vector_t *vec, void *output);
vector_error_t vector_insert(vector_t *vec, size_t index, void *element);
vector_error_t vector_remove(vector_t *vec, size_t index, void *output);
vector_error_t vector_get(vector_t *vec, size_t index, void *output);
vector_error_t vector_set(vector_t *vec, size_t index, void *element);
size_t vector_size(vector_t *vec);
int vector_is_empty(vector_t *vec);
void free_vector(vector_t *vec);

#endif // VECTOR_H
