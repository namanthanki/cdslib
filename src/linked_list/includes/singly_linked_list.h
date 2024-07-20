#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "linked_list.h"
#include <stdlib.h>

typedef struct singly_linked_list_node
{
    void *data;
    struct singly_linked_list_node *next;

} singly_linked_list_node_t;

typedef struct
{
    singly_linked_list_node_t *head;
    size_t size;
    size_t element_size;
} singly_linked_list_t;

#define DECLARE_SINGLY_LINKED_LIST_FUNCTIONS(TYPE, SUFFIX)                                    \
    singly_linked_list_t *create_##SUFFIX##_singly_linked_list();                             \
    linked_list_error_t insert_front_##SUFFIX(singly_linked_list_t *list, TYPE element);      \
    linked_list_error_t insert_back_##SUFFIX(singly_linked_list_t *list, TYPE element);       \
    linked_list_error_t remove_front_##SUFFIX(singly_linked_list_t *list, TYPE *output);      \
    linked_list_error_t remove_back_##SUFFIX(singly_linked_list_t *list, TYPE *output);       \
    linked_list_error_t get_##SUFFIX(singly_linked_list_t *list, size_t index, TYPE *output); \
    linked_list_error_t set_##SUFFIX(singly_linked_list_t *list, size_t index, TYPE element);

#define DECLARE_STRING_SINGLY_LINKED_LIST_FUNCTIONS                                                \
    singly_linked_list_t *create_string_singly_linked_list();                                      \
    linked_list_error_t insert_front_string(singly_linked_list_t *list, const char *element);      \
    linked_list_error_t insert_back_string(singly_linked_list_t *list, const char *element);       \
    linked_list_error_t remove_front_string(singly_linked_list_t *list, char **output);            \
    linked_list_error_t remove_back_string(singly_linked_list_t *list, char **output);             \
    linked_list_error_t get_string(singly_linked_list_t *list, size_t index, char **output);       \
    linked_list_error_t set_string(singly_linked_list_t *list, size_t index, const char *element); \
    void free_string_singly_linked_list(singly_linked_list_t *list);

DECLARE_SINGLY_LINKED_LIST_FUNCTIONS(char, char)
DECLARE_SINGLY_LINKED_LIST_FUNCTIONS(int, int)
DECLARE_SINGLY_LINKED_LIST_FUNCTIONS(float, float)
DECLARE_SINGLY_LINKED_LIST_FUNCTIONS(double, double)
DECLARE_STRING_SINGLY_LINKED_LIST_FUNCTIONS

// Generic functions

singly_linked_list_t *create_singly_linked_list(size_t element_size);
linked_list_error_t insert_front(singly_linked_list_t *list, void *element);
linked_list_error_t insert_back(singly_linked_list_t *list, void *element);
linked_list_error_t remove_front(singly_linked_list_t *list, void *output);
linked_list_error_t remove_back(singly_linked_list_t *list, void *output);
linked_list_error_t get(singly_linked_list_t *list, size_t index, void *output);
linked_list_error_t set(singly_linked_list_t *list, size_t index, void *element);
void free_singly_linked_list(singly_linked_list_t *list);

size_t singly_linked_list_size(singly_linked_list_t *list);
int is_singly_linked_list_empty(singly_linked_list_t *list);

#endif // SINGLY_LINKED_LIST_H