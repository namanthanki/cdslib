#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdlib.h>

typedef enum
{
    LINKED_LIST_SUCCESS,
    LINKED_LIST_EMPTY,
    LINKED_LIST_OUT_OF_RANGE,
    LINKED_LIST_MEMORY_ERROR,

} linked_list_error_t;

typedef struct doubly_linked_list_node
{
    void *data;
    struct doubly_linked_list_node *next;
    struct doubly_linked_list_node *prev;

} doubly_linked_list_node_t;

typedef struct
{
    doubly_linked_list_node_t *head;
    doubly_linked_list_node_t *tail;
    size_t size;
    size_t element_size;
} doubly_linked_list_t;

#define DECLARE_DOUBLY_LINKED_LIST_FUNCTIONS(TYPE, SUFFIX)                                             \
    doubly_linked_list_t *create_##SUFFIX##_doubly_linked_list();                                      \
    linked_list_error_t insert_front_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE element);      \
    linked_list_error_t insert_back_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE element);       \
    linked_list_error_t remove_front_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE *output);      \
    linked_list_error_t remove_back_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE *output);       \
    linked_list_error_t get_##SUFFIX##_doubly(doubly_linked_list_t *list, size_t index, TYPE *output); \
    linked_list_error_t set_##SUFFIX##_doubly(doubly_linked_list_t *list, size_t index, TYPE element);

#define DECLARE_STRING_DOUBLY_LINKED_LIST_FUNCTIONS                                                       \
    doubly_linked_list_t *create_string_doubly_linked_list();                                             \
    linked_list_error_t insert_front_string_doubly(doubly_linked_list_t *list, const char *element);      \
    linked_list_error_t insert_back_string_doubly(doubly_linked_list_t *list, const char *element);       \
    linked_list_error_t remove_front_string_doubly(doubly_linked_list_t *list, char **output);            \
    linked_list_error_t remove_back_string_doubly(doubly_linked_list_t *list, char **output);             \
    linked_list_error_t get_string_doubly(doubly_linked_list_t *list, size_t index, char **output);       \
    linked_list_error_t set_string_doubly(doubly_linked_list_t *list, size_t index, const char *element); \
    void free_string_doubly_linked_list(doubly_linked_list_t *list);

DECLARE_DOUBLY_LINKED_LIST_FUNCTIONS(char, char)
DECLARE_DOUBLY_LINKED_LIST_FUNCTIONS(int, int)
DECLARE_DOUBLY_LINKED_LIST_FUNCTIONS(float, float)
DECLARE_DOUBLY_LINKED_LIST_FUNCTIONS(double, double)
DECLARE_STRING_DOUBLY_LINKED_LIST_FUNCTIONS

// Generic functions
doubly_linked_list_t *create_doubly_linked_list(size_t element_size);
linked_list_error_t insert_front_doubly(doubly_linked_list_t *list, void *element);
linked_list_error_t insert_back_doubly(doubly_linked_list_t *list, void *element);
linked_list_error_t remove_front_doubly(doubly_linked_list_t *list, void *output);
linked_list_error_t remove_back_doubly(doubly_linked_list_t *list, void *output);
linked_list_error_t get_doubly(doubly_linked_list_t *list, size_t index, void *output);
linked_list_error_t set_doubly(doubly_linked_list_t *list, size_t index, void *element);
void free_doubly_linked_list(doubly_linked_list_t *list);

size_t doubly_linked_list_size(doubly_linked_list_t *list);
int is_doubly_linked_list_empty(doubly_linked_list_t *list);

#endif // DOUBLY_LINKED_LIST_H