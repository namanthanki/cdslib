#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdlib.h>

typedef enum
{
    LINKED_LIST_SUCCESS,
    LINKED_LIST_EMPTY,
    LINKED_LIST_OUT_OF_RANGE,
    LINKED_LIST_MEMORY_ERROR,

} linked_list_error_t;

typedef struct circular_linked_list_node
{
    void *data;
    struct circular_linked_list_node *next;

} circular_linked_list_node_t;

typedef struct
{
    circular_linked_list_node_t *head;
    size_t size;
    size_t element_size;
} circular_linked_list_t;

#define DECLARE_CIRCULAR_LINKED_LIST_FUNCTIONS(TYPE, SUFFIX)                                               \
    circular_linked_list_t *create_##SUFFIX##_circular_linked_list();                                      \
    linked_list_error_t insert_front_##SUFFIX##_circular(circular_linked_list_t *list, TYPE element);      \
    linked_list_error_t insert_back_##SUFFIX##_circular(circular_linked_list_t *list, TYPE element);       \
    linked_list_error_t remove_front_##SUFFIX##_circular(circular_linked_list_t *list, TYPE *output);      \
    linked_list_error_t remove_back_##SUFFIX##_circular(circular_linked_list_t *list, TYPE *output);       \
    linked_list_error_t get_##SUFFIX##_circular(circular_linked_list_t *list, size_t index, TYPE *output); \
    linked_list_error_t set_##SUFFIX##_circular(circular_linked_list_t *list, size_t index, TYPE element);

#define DECLARE_STRING_CIRCULAR_LINKED_LIST_FUNCTIONS                                                         \
    circular_linked_list_t *create_string_circular_linked_list();                                             \
    linked_list_error_t insert_front_string_circular(circular_linked_list_t *list, const char *element);      \
    linked_list_error_t insert_back_string_circular(circular_linked_list_t *list, const char *element);       \
    linked_list_error_t remove_front_string_circular(circular_linked_list_t *list, char **output);            \
    linked_list_error_t remove_back_string_circular(circular_linked_list_t *list, char **output);             \
    linked_list_error_t get_string_circular(circular_linked_list_t *list, size_t index, char **output);       \
    linked_list_error_t set_string_circular(circular_linked_list_t *list, size_t index, const char *element); \
    void free_string_circular_linked_list(circular_linked_list_t *list);

DECLARE_CIRCULAR_LINKED_LIST_FUNCTIONS(char, char)
DECLARE_CIRCULAR_LINKED_LIST_FUNCTIONS(int, int)
DECLARE_CIRCULAR_LINKED_LIST_FUNCTIONS(float, float)
DECLARE_CIRCULAR_LINKED_LIST_FUNCTIONS(double, double)
DECLARE_STRING_CIRCULAR_LINKED_LIST_FUNCTIONS

// Generic functions
circular_linked_list_t *create_circular_linked_list(size_t element_size);
linked_list_error_t insert_front_circular(circular_linked_list_t *list, void *element);
linked_list_error_t insert_back_circular(circular_linked_list_t *list, void *element);
linked_list_error_t remove_front_circular(circular_linked_list_t *list, void *output);
linked_list_error_t remove_back_circular(circular_linked_list_t *list, void *output);
linked_list_error_t get_circular(circular_linked_list_t *list, size_t index, void *output);
linked_list_error_t set_circular(circular_linked_list_t *list, size_t index, void *element);
void free_circular_linked_list(circular_linked_list_t *list);

size_t circular_linked_list_size(circular_linked_list_t *list);
int is_circular_linked_list_empty(circular_linked_list_t *list);

#endif // CIRCULAR_LINKED_LIST_H