#include "doubly_linked_list.h"
#include <stdlib.h>
#include <string.h>

#define DEFINE_DOUBLY_LINKED_LIST_FUNCTIONS(TYPE, SUFFIX)                                             \
    doubly_linked_list_t *create_##SUFFIX##_doubly_linked_list()                                      \
    {                                                                                                 \
        return create_doubly_linked_list(sizeof(TYPE));                                               \
    }                                                                                                 \
    linked_list_error_t insert_front_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE element)      \
    {                                                                                                 \
        return insert_front_doubly(list, &element);                                                   \
    }                                                                                                 \
    linked_list_error_t insert_back_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE element)       \
    {                                                                                                 \
        return insert_back_doubly(list, &element);                                                    \
    }                                                                                                 \
    linked_list_error_t remove_front_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE *output)      \
    {                                                                                                 \
        return remove_front_doubly(list, output);                                                     \
    }                                                                                                 \
    linked_list_error_t remove_back_##SUFFIX##_doubly(doubly_linked_list_t *list, TYPE *output)       \
    {                                                                                                 \
        return remove_back_doubly(list, output);                                                      \
    }                                                                                                 \
    linked_list_error_t get_##SUFFIX##_doubly(doubly_linked_list_t *list, size_t index, TYPE *output) \
    {                                                                                                 \
        return get_doubly(list, index, output);                                                       \
    }                                                                                                 \
    linked_list_error_t set_##SUFFIX##_doubly(doubly_linked_list_t *list, size_t index, TYPE element) \
    {                                                                                                 \
        return set_doubly(list, index, &element);                                                     \
    }

#define DEFINE_STRING_DOUBLY_LINKED_LIST_FUNCTIONS                                                       \
    doubly_linked_list_t *create_string_doubly_linked_list()                                             \
    {                                                                                                    \
        return create_doubly_linked_list(sizeof(char *));                                                \
    }                                                                                                    \
                                                                                                         \
    linked_list_error_t insert_front_string_doubly(doubly_linked_list_t *list, const char *element)      \
    {                                                                                                    \
        char *copy = strdup(element);                                                                    \
        if (!copy)                                                                                       \
        {                                                                                                \
            return LINKED_LIST_MEMORY_ERROR;                                                             \
        }                                                                                                \
        linked_list_error_t result = insert_front_doubly(list, &copy);                                   \
        if (result != LINKED_LIST_SUCCESS)                                                               \
        {                                                                                                \
            free(copy);                                                                                  \
        }                                                                                                \
        return result;                                                                                   \
    }                                                                                                    \
    linked_list_error_t insert_back_string_doubly(doubly_linked_list_t *list, const char *element)       \
    {                                                                                                    \
        char *copy = strdup(element);                                                                    \
        if (!copy)                                                                                       \
        {                                                                                                \
            return LINKED_LIST_MEMORY_ERROR;                                                             \
        }                                                                                                \
        linked_list_error_t result = insert_back_doubly(list, &copy);                                    \
        if (result != LINKED_LIST_SUCCESS)                                                               \
        {                                                                                                \
            free(copy);                                                                                  \
        }                                                                                                \
        return result;                                                                                   \
    }                                                                                                    \
    linked_list_error_t remove_front_string_doubly(doubly_linked_list_t *list, char **output)            \
    {                                                                                                    \
        return remove_front_doubly(list, output);                                                        \
    }                                                                                                    \
    linked_list_error_t remove_back_string_doubly(doubly_linked_list_t *list, char **output)             \
    {                                                                                                    \
        return remove_back_doubly(list, output);                                                         \
    }                                                                                                    \
    linked_list_error_t get_string_doubly(doubly_linked_list_t *list, size_t index, char **output)       \
    {                                                                                                    \
        return get_doubly(list, index, output);                                                          \
    }                                                                                                    \
    linked_list_error_t set_string_doubly(doubly_linked_list_t *list, size_t index, const char *element) \
    {                                                                                                    \
        char *copy = strdup(element);                                                                    \
        if (!copy)                                                                                       \
        {                                                                                                \
            return LINKED_LIST_MEMORY_ERROR;                                                             \
        }                                                                                                \
        linked_list_error_t result = set_doubly(list, index, &copy);                                     \
        if (result != LINKED_LIST_SUCCESS)                                                               \
        {                                                                                                \
            free(copy);                                                                                  \
        }                                                                                                \
        return result;                                                                                   \
    }                                                                                                    \
    void free_string_doubly_linked_list(doubly_linked_list_t *list)                                      \
    {                                                                                                    \
        if (!list)                                                                                       \
        {                                                                                                \
            return;                                                                                      \
        }                                                                                                \
        doubly_linked_list_node_t *current = list->head;                                                 \
        while (current)                                                                                  \
        {                                                                                                \
            doubly_linked_list_node_t *next = current->next;                                             \
            free(current->data);                                                                         \
            free(current);                                                                               \
            current = next;                                                                              \
        }                                                                                                \
        free(list);                                                                                      \
    }

DEFINE_DOUBLY_LINKED_LIST_FUNCTIONS(char, char)
DEFINE_DOUBLY_LINKED_LIST_FUNCTIONS(int, int)
DEFINE_DOUBLY_LINKED_LIST_FUNCTIONS(float, float)
DEFINE_DOUBLY_LINKED_LIST_FUNCTIONS(double, double)
DEFINE_STRING_DOUBLY_LINKED_LIST_FUNCTIONS

size_t doubly_linked_list_size(doubly_linked_list_t *list)
{
    return list->size;
}

int is_doubly_linked_list_empty(doubly_linked_list_t *list)
{
    return list ? list->size == 0 : 1;
}

doubly_linked_list_t *create_doubly_linked_list(size_t element_size)
{
    doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
    if (!list)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

linked_list_error_t insert_front_doubly(doubly_linked_list_t *list, void *element)
{
    doubly_linked_list_node_t *new_node = malloc(sizeof(doubly_linked_list_node_t));
    if (!new_node)
    {
        return LINKED_LIST_MEMORY_ERROR;
    }

    new_node->data = malloc(list->element_size);
    if (!new_node->data)
    {
        free(new_node);
        return LINKED_LIST_MEMORY_ERROR;
    }

    memcpy(new_node->data, element, list->element_size);

    if (!list->head)
    {
        list->head = new_node;
        list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else
    {
        new_node->next = list->head;
        new_node->prev = NULL;
        list->head->prev = new_node;
        list->head = new_node;
    }

    list->size++;

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t insert_back_doubly(doubly_linked_list_t *list, void *element)
{
    doubly_linked_list_node_t *new_node = malloc(sizeof(doubly_linked_list_node_t));
    if (!new_node)
    {
        return LINKED_LIST_MEMORY_ERROR;
    }

    new_node->data = malloc(list->element_size);
    if (!new_node->data)
    {
        free(new_node);
        return LINKED_LIST_MEMORY_ERROR;
    }

    memcpy(new_node->data, element, list->element_size);

    if (!list->tail)
    {
        list->head = new_node;
        list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else
    {
        new_node->next = NULL;
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t remove_front_doubly(doubly_linked_list_t *list, void *output)
{
    if (is_doubly_linked_list_empty(list))
    {
        return LINKED_LIST_EMPTY;
    }

    doubly_linked_list_node_t *node = list->head;
    list->head = list->head->next;
    if (list->head)
    {
        list->head->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }

    memcpy(output, node->data, list->element_size);

    free(node->data);
    free(node);

    list->size--;

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t remove_back_doubly(doubly_linked_list_t *list, void *output)
{
    if (is_doubly_linked_list_empty(list))
    {
        return LINKED_LIST_EMPTY;
    }

    doubly_linked_list_node_t *node = list->tail;
    list->tail = list->tail->prev;
    if (list->tail)
    {
        list->tail->next = NULL;
    }
    else
    {
        list->head = NULL;
    }

    memcpy(output, node->data, list->element_size);

    free(node->data);
    free(node);

    list->size--;

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t get_doubly(doubly_linked_list_t *list, size_t index, void *output)
{
    if (is_doubly_linked_list_empty(list))
    {
        return LINKED_LIST_EMPTY;
    }

    if (index >= list->size)
    {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    doubly_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    memcpy(output, current->data, list->element_size);

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t set_doubly(doubly_linked_list_t *list, size_t index, void *element)
{
    if (is_doubly_linked_list_empty(list))
    {
        return LINKED_LIST_EMPTY;
    }

    if (index >= list->size)
    {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    doubly_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    memcpy(current->data, element, list->element_size);

    return LINKED_LIST_SUCCESS;
}

void free_doubly_linked_list(doubly_linked_list_t *list)
{
    if (!list)
    {
        return;
    }

    doubly_linked_list_node_t *current = list->head;
    while (current)
    {
        doubly_linked_list_node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(list);
}