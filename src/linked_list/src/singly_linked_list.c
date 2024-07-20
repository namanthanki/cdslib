#include "linked_list.h"
#include "singly_linked_list.h"

#include <stdlib.h>
#include <string.h>

#define DEFINE_SINGLY_LINKED_LIST_FUNCTIONS(TYPE, SUFFIX)                                    \
    singly_linked_list_t *create_##SUFFIX##_singly_linked_list()                             \
    {                                                                                        \
        return create_singly_linked_list(sizeof(TYPE));                                      \
    }                                                                                        \
                                                                                             \
    linked_list_error_t insert_front_##SUFFIX(singly_linked_list_t *list, TYPE element)      \
    {                                                                                        \
        return insert_front(list, &element);                                                 \
    }                                                                                        \
                                                                                             \
    linked_list_error_t insert_back_##SUFFIX(singly_linked_list_t *list, TYPE element)       \
    {                                                                                        \
        return insert_back(list, &element);                                                  \
    }                                                                                        \
                                                                                             \
    linked_list_error_t remove_front_##SUFFIX(singly_linked_list_t *list, TYPE *output)      \
    {                                                                                        \
        return remove_front(list, output);                                                   \
    }                                                                                        \
                                                                                             \
    linked_list_error_t remove_back_##SUFFIX(singly_linked_list_t *list, TYPE *output)       \
    {                                                                                        \
        return remove_back(list, output);                                                    \
    }                                                                                        \
                                                                                             \
    linked_list_error_t get_##SUFFIX(singly_linked_list_t *list, size_t index, TYPE *output) \
    {                                                                                        \
        return get(list, index, output);                                                     \
    }                                                                                        \
                                                                                             \
    linked_list_error_t set_##SUFFIX(singly_linked_list_t *list, size_t index, TYPE element) \
    {                                                                                        \
        return set(list, index, &element);                                                   \
    }

#define DEFINE_STRING_SINGLY_LINKED_LIST_FUNCTIONS                                              \
    singly_linked_list_t *create_string_singly_linked_list()                                    \
    {                                                                                           \
        return create_singly_linked_list(sizeof(char *));                                       \
    }                                                                                           \
                                                                                                \
    linked_list_error_t insert_front_string(singly_linked_list_t *list, const char *element)    \
    {                                                                                           \
        char *copy = strdup(element);                                                           \
        if (!copy)                                                                              \
            return LINKED_LIST_MEMORY_ERROR;                                                    \
        linked_list_error_t result = insert_front(list, &copy);                                 \
        if (result != LINKED_LIST_SUCCESS)                                                      \
            free(copy);                                                                         \
        return result;                                                                          \
    }                                                                                           \
    linked_list_error_t insert_back_string(singly_linked_list_t *list, const char *value)       \
    {                                                                                           \
        char *copy = strdup(value);                                                             \
        if (!copy)                                                                              \
            return LINKED_LIST_MEMORY_ERROR;                                                    \
        linked_list_error_t result = insert_back(list, &copy);                                  \
        if (result != LINKED_LIST_SUCCESS)                                                      \
            free(copy);                                                                         \
        return result;                                                                          \
    }                                                                                           \
    linked_list_error_t remove_front_string(singly_linked_list_t *list, char **value)           \
    {                                                                                           \
        return remove_front(list, value);                                                       \
    }                                                                                           \
                                                                                                \
    linked_list_error_t remove_back_string(singly_linked_list_t *list, char **value)            \
    {                                                                                           \
        return remove_back(list, value);                                                        \
    }                                                                                           \
    linked_list_error_t get_string(singly_linked_list_t *list, size_t index, char **value)      \
    {                                                                                           \
        return get(list, index, value);                                                         \
    }                                                                                           \
    linked_list_error_t set_string(singly_linked_list_t *list, size_t index, const char *value) \
    {                                                                                           \
        return set(list, index, &value);                                                        \
    }                                                                                           \
    void free_string_singly_linked_list(singly_linked_list_t *list)                             \
    {                                                                                           \
        singly_linked_list_node_t *current = list->head;                                        \
        while (current != NULL)                                                                 \
        {                                                                                       \
            singly_linked_list_node_t *next = current->next;                                    \
            free(*(char **)current->data);                                                      \
            free(current->data);                                                                \
            free(current);                                                                      \
            current = next;                                                                     \
        }                                                                                       \
        free(list);                                                                             \
    }

DEFINE_SINGLY_LINKED_LIST_FUNCTIONS(char, char)
DEFINE_SINGLY_LINKED_LIST_FUNCTIONS(int, int)
DEFINE_SINGLY_LINKED_LIST_FUNCTIONS(float, float)
DEFINE_SINGLY_LINKED_LIST_FUNCTIONS(double, double)
DEFINE_STRING_SINGLY_LINKED_LIST_FUNCTIONS

size_t singly_linked_list_size(singly_linked_list_t *list)
{
    return list ? list->size : 0;
}

int is_singly_linked_list_empty(singly_linked_list_t *list)
{
    return list ? list->size == 0 : 1;
}

singly_linked_list_t *create_singly_linked_list(size_t element_size)
{
    singly_linked_list_t *list = malloc(sizeof(singly_linked_list_t));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

linked_list_error_t insert_front(singly_linked_list_t *list, void *element)
{
    singly_linked_list_node_t *new_node = malloc(sizeof(singly_linked_list_node_t));
    if (new_node == NULL)
    {
        return LINKED_LIST_MEMORY_ERROR;
    }

    new_node->data = malloc(list->element_size);

    if (new_node->data == NULL)
    {
        free(new_node);
        return LINKED_LIST_MEMORY_ERROR;
    }

    memcpy(new_node->data, element, list->element_size);

    new_node->next = list->head;
    list->head = new_node;
    list->size++;

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t insert_back(singly_linked_list_t *list, void *element)
{
    singly_linked_list_node_t *new_node = malloc(sizeof(singly_linked_list_node_t));
    if (new_node == NULL)
    {
        return LINKED_LIST_MEMORY_ERROR;
    }

    new_node->data = malloc(list->element_size);
    if (new_node->data == NULL)
    {
        free(new_node);
        return LINKED_LIST_MEMORY_ERROR;
    }

    memcpy(new_node->data, element, list->element_size);

    new_node->next = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        singly_linked_list_node_t *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }

    list->size++;
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t remove_front(singly_linked_list_t *list, void *output)
{
    if (list->head == NULL)
    {
        return LINKED_LIST_EMPTY;
    }

    singly_linked_list_node_t *temp = list->head;
    list->head = list->head->next;

    memcpy(output, temp->data, list->element_size);
    free(temp->data);
    free(temp);

    list->size--;
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t remove_back(singly_linked_list_t *list, void *output)
{
    if (list->head == NULL)
    {
        return LINKED_LIST_EMPTY;
    }

    if (list->size == 1)
    {
        singly_linked_list_node_t *temp = list->head;
        memcpy(output, temp->data, list->element_size);
        free(temp->data);
        free(temp);
        list->head = NULL;
        list->size = 0;
        return LINKED_LIST_SUCCESS;
    }

    singly_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < list->size - 2; i++)
    {
        current = current->next;
    }

    memcpy(output, current->next->data, list->element_size);
    free(current->next->data);
    free(current->next);
    current->next = NULL;
    list->size--;

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t get(singly_linked_list_t *list, size_t index, void *output)
{
    if (index >= list->size)
    {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    singly_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    memcpy(output, current->data, list->element_size);
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t set(singly_linked_list_t *list, size_t index, void *element)
{
    if (index >= list->size)
    {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    singly_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    memcpy(current->data, element, list->element_size);
    return LINKED_LIST_SUCCESS;
}
#include <stdio.h>

void free_singly_linked_list(singly_linked_list_t *list)
{
    if (!list)
    {
        return;
    }

    singly_linked_list_node_t *current = list->head;

    for (size_t i = 0; i < list->size; i++)
    {
        singly_linked_list_node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}