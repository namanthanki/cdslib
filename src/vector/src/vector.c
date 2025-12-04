#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

// Generic functions implementation

vector_t *create_vector(size_t element_size)
{
    vector_t *vec = (vector_t *)malloc(sizeof(vector_t));
    if (!vec)
    {
        return NULL;
    }

    vec->data = malloc(element_size * INITIAL_CAPACITY);
    if (!vec->data)
    {
        free(vec);
        return NULL;
    }

    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    vec->element_size = element_size;

    return vec;
}

static vector_error_t resize_vector(vector_t *vec, size_t new_capacity)
{
    void *new_data = realloc(vec->data, vec->element_size * new_capacity);
    if (!new_data)
    {
        return VECTOR_MEMORY_ERROR;
    }

    vec->data = new_data;
    vec->capacity = new_capacity;
    return VECTOR_SUCCESS;
}

vector_error_t vector_push_back(vector_t *vec, void *element)
{
    if (vec->size == vec->capacity)
    {
        vector_error_t result = resize_vector(vec, vec->capacity * 2);
        if (result != VECTOR_SUCCESS)
        {
            return result;
        }
    }

    char *dest = (char *)vec->data + (vec->size * vec->element_size);
    memcpy(dest, element, vec->element_size);
    vec->size++;

    return VECTOR_SUCCESS;
}

vector_error_t vector_pop_back(vector_t *vec, void *output)
{
    if (vec->size == 0)
    {
        return VECTOR_EMPTY;
    }

    vec->size--;
    if (output)
    {
        char *src = (char *)vec->data + (vec->size * vec->element_size);
        memcpy(output, src, vec->element_size);
    }

    // Optional: Shrink if too empty (e.g., size < capacity / 4)
    if (vec->size > 0 && vec->size < vec->capacity / 4 && vec->capacity > INITIAL_CAPACITY)
    {
        resize_vector(vec, vec->capacity / 2);
    }

    return VECTOR_SUCCESS;
}

vector_error_t vector_insert(vector_t *vec, size_t index, void *element)
{
    if (index > vec->size)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS;
    }

    if (vec->size == vec->capacity)
    {
        vector_error_t result = resize_vector(vec, vec->capacity * 2);
        if (result != VECTOR_SUCCESS)
        {
            return result;
        }
    }

    // Shift elements to the right
    char *base = (char *)vec->data;
    if (index < vec->size)
    {
        memmove(base + (index + 1) * vec->element_size,
                base + index * vec->element_size,
                (vec->size - index) * vec->element_size);
    }

    memcpy(base + index * vec->element_size, element, vec->element_size);
    vec->size++;

    return VECTOR_SUCCESS;
}

vector_error_t vector_remove(vector_t *vec, size_t index, void *output)
{
    if (index >= vec->size)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS;
    }

    char *base = (char *)vec->data;
    if (output)
    {
        memcpy(output, base + index * vec->element_size, vec->element_size);
    }

    // Shift elements to the left
    if (index < vec->size - 1)
    {
        memmove(base + index * vec->element_size,
                base + (index + 1) * vec->element_size,
                (vec->size - index - 1) * vec->element_size);
    }

    vec->size--;

    if (vec->size > 0 && vec->size < vec->capacity / 4 && vec->capacity > INITIAL_CAPACITY)
    {
        resize_vector(vec, vec->capacity / 2);
    }

    return VECTOR_SUCCESS;
}

vector_error_t vector_get(vector_t *vec, size_t index, void *output)
{
    if (index >= vec->size)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS;
    }

    char *base = (char *)vec->data;
    memcpy(output, base + index * vec->element_size, vec->element_size);
    return VECTOR_SUCCESS;
}

vector_error_t vector_set(vector_t *vec, size_t index, void *element)
{
    if (index >= vec->size)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS;
    }

    char *base = (char *)vec->data;
    memcpy(base + index * vec->element_size, element, vec->element_size);
    return VECTOR_SUCCESS;
}

size_t vector_size(vector_t *vec)
{
    return vec ? vec->size : 0;
}

int vector_is_empty(vector_t *vec)
{
    return vec ? vec->size == 0 : 1;
}

void free_vector(vector_t *vec)
{
    if (vec)
    {
        free(vec->data);
        free(vec);
    }
}

// Macro implementations

#define DEFINE_VECTOR_FUNCTIONS(TYPE, SUFFIX)                                    \
    vector_t *create_##SUFFIX##_vector()                                         \
    {                                                                            \
        return create_vector(sizeof(TYPE));                                      \
    }                                                                            \
    vector_error_t push_back_##SUFFIX(vector_t *vec, TYPE element)               \
    {                                                                            \
        return vector_push_back(vec, &element);                                  \
    }                                                                            \
    vector_error_t pop_back_##SUFFIX(vector_t *vec, TYPE *output)                \
    {                                                                            \
        return vector_pop_back(vec, output);                                     \
    }                                                                            \
    vector_error_t insert_##SUFFIX(vector_t *vec, size_t index, TYPE element)    \
    {                                                                            \
        return vector_insert(vec, index, &element);                              \
    }                                                                            \
    vector_error_t remove_##SUFFIX(vector_t *vec, size_t index, TYPE *output)    \
    {                                                                            \
        return vector_remove(vec, index, output);                                \
    }                                                                            \
    vector_error_t get_##SUFFIX(vector_t *vec, size_t index, TYPE *output)       \
    {                                                                            \
        return vector_get(vec, index, output);                                   \
    }                                                                            \
    vector_error_t set_##SUFFIX(vector_t *vec, size_t index, TYPE element)       \
    {                                                                            \
        return vector_set(vec, index, &element);                                 \
    }                                                                            \
    void free_##SUFFIX##_vector(vector_t *vec)                                   \
    {                                                                            \
        free_vector(vec);                                                        \
    }

#define DEFINE_STRING_VECTOR_FUNCTIONS                                              \
    vector_t *create_string_vector()                                                \
    {                                                                               \
        return create_vector(sizeof(char *));                                       \
    }                                                                               \
    vector_error_t push_back_string(vector_t *vec, const char *element)             \
    {                                                                               \
        char *copy = strdup(element);                                               \
        if (!copy) return VECTOR_MEMORY_ERROR;                                      \
        vector_error_t res = vector_push_back(vec, &copy);                          \
        if (res != VECTOR_SUCCESS) free(copy);                                      \
        return res;                                                                 \
    }                                                                               \
    vector_error_t pop_back_string(vector_t *vec, char **output)                    \
    {                                                                               \
        return vector_pop_back(vec, output);                                        \
    }                                                                               \
    vector_error_t insert_string(vector_t *vec, size_t index, const char *element)  \
    {                                                                               \
        char *copy = strdup(element);                                               \
        if (!copy) return VECTOR_MEMORY_ERROR;                                      \
        vector_error_t res = vector_insert(vec, index, &copy);                      \
        if (res != VECTOR_SUCCESS) free(copy);                                      \
        return res;                                                                 \
    }                                                                               \
    vector_error_t remove_string(vector_t *vec, size_t index, char **output)        \
    {                                                                               \
        return vector_remove(vec, index, output);                                   \
    }                                                                               \
    vector_error_t get_string(vector_t *vec, size_t index, char **output)           \
    {                                                                               \
        return vector_get(vec, index, output);                                      \
    }                                                                               \
    vector_error_t set_string(vector_t *vec, size_t index, const char *element)     \
    {                                                                               \
        char *copy = strdup(element);                                               \
        if (!copy) return VECTOR_MEMORY_ERROR;                                      \
        /* Free old string */                                                       \
        char *old;                                                                  \
        if (vector_get(vec, index, &old) == VECTOR_SUCCESS) free(old);              \
        vector_error_t res = vector_set(vec, index, &copy);                         \
        if (res != VECTOR_SUCCESS) free(copy);                                      \
        return res;                                                                 \
    }                                                                               \
    void free_string_vector(vector_t *vec)                                          \
    {                                                                               \
        if (!vec) return;                                                           \
        for (size_t i = 0; i < vec->size; i++)                                      \
        {                                                                           \
            char *str;                                                              \
            vector_get(vec, i, &str);                                               \
            free(str);                                                              \
        }                                                                           \
        free_vector(vec);                                                           \
    }

DEFINE_VECTOR_FUNCTIONS(char, char)
DEFINE_VECTOR_FUNCTIONS(int, int)
DEFINE_VECTOR_FUNCTIONS(float, float)
DEFINE_VECTOR_FUNCTIONS(double, double)
DEFINE_STRING_VECTOR_FUNCTIONS
