#include "circular_linked_list.h"
#include <stdlib.h>
#include <string.h>

#define DEFINE_CIRCULAR_LINKED_LIST_FUNCTIONS(TYPE, SUFFIX)                                               \
    circular_linked_list_t *create_##SUFFIX##_circular_linked_list()                                      \
    {                                                                                                     \
        return create_circular_linked_list(sizeof(TYPE));                                                 \
    }                                                                                                     \
    linked_list_error_t insert_front_##SUFFIX##_circular(circular_linked_list_t *list, TYPE element)      \
    {                                                                                                     \
        return insert_front_circular(list, &element);                                                     \
    }                                                                                                     \
    linked_list_error_t insert_back_##SUFFIX##_circular(circular_linked_list_t *list, TYPE element)       \
    {                                                                                                     \
        return insert_back_circular(list, &element);                                                      \
    }                                                                                                     \
    linked_list_error_t remove_front_##SUFFIX##_circular(circular_linked_list_t *list, TYPE *output)      \
    {                                                                                                     \
        return remove_front_circular(list, output);                                                       \
    }                                                                                                     \
    linked_list_error_t remove_back_##SUFFIX##_circular(circular_linked_list_t *list, TYPE *output)       \
    {                                                                                                     \
        return remove_back_circular(list, output);                                                        \
    }                                                                                                     \
    linked_list_error_t get_##SUFFIX##_circular(circular_linked_list_t *list, size_t index, TYPE *output) \
    {                                                                                                     \
        return get_circular(list, index, output);                                                         \
    }                                                                                                     \
    linked_list_error_t set_##SUFFIX##_circular(circular_linked_list_t *list, size_t index, TYPE element) \
    {                                                                                                     \
        return set_circular(list, index, &element);                                                       \
    }

#define DEFINE_STRING_CIRCULAR_LINKED_LIST_FUNCTIONS                                                         \
    circular_linked_list_t *create_string_circular_linked_list()                                             \
    {                                                                                                        \
        return create_circular_linked_list(sizeof(char *));                                                  \
    }                                                                                                        \
                                                                                                             \
    linked_list_error_t insert_front_string_circular(circular_linked_list_t *list, const char *element)      \
    {                                                                                                        \
        char *copy = strdup(element);                                                                        \
        if (!copy)                                                                                           \
        {                                                                                                    \
            return LINKED_LIST_MEMORY_ERROR;                                                                 \
        }                                                                                                    \
        linked_list_error_t result = insert_front_circular(list, &copy);                                     \
        if (result != LINKED_LIST_SUCCESS)                                                                   \
        {                                                                                                    \
            free(copy);                                                                                      \
        }                                                                                                    \
        return result;                                                                                       \
    }                                                                                                        \
    linked_list_error_t insert_back_string_circular(circular_linked_list_t *list, const char *element)       \
    {                                                                                                        \
        char *copy = strdup(element);                                                                        \
        if (!copy)                                                                                           \
        {                                                                                                    \
            return LINKED_LIST_MEMORY_ERROR;                                                                 \
        }                                                                                                    \
        linked_list_error_t result = insert_back_circular(list, &copy);                                      \
        if (result != LINKED_LIST_SUCCESS)                                                                   \
        {                                                                                                    \
            free(copy);                                                                                      \
        }                                                                                                    \
        return result;                                                                                       \
    }                                                                                                        \
    linked_list_error_t remove_front_string_circular(circular_linked_list_t *list, char **output)            \
    {                                                                                                        \
        return remove_front_circular(list, output);                                                          \
    }                                                                                                        \
    linked_list_error_t remove_back_string_circular(circular_linked_list_t *list, char **output)             \
    {                                                                                                        \
        return remove_back_circular(list, output);                                                           \
    }                                                                                                        \
    linked_list_error_t get_string_circular(circular_linked_list_t *list, size_t index, char **output)       \
    {                                                                                                        \
        return get_circular(list, index, output);                                                            \
    }                                                                                                        \
    linked_list_error_t set_string_circular(circular_linked_list_t *list, size_t index, const char *element) \
    {                                                                                                        \
        char *copy = strdup(element);                                                                        \
        if (!copy)                                                                                           \
        {                                                                                                    \
            return LINKED_LIST_MEMORY_ERROR;                                                                 \
        }                                                                                                    \
        linked_list_error_t result = set_circular(list, index, &copy);                                       \
        if (result != LINKED_LIST_SUCCESS)                                                                   \
        {                                                                                                    \
            free(copy);                                                                                      \
        }                                                                                                    \
        return result;                                                                                       \
    }                                                                                                        \
    void free_string_circular_linked_list(circular_linked_list_t *list)                                      \
    {                                                                                                        \
        if (!list)                                                                                           \
        {                                                                                                    \
            return;                                                                                          \
        }                                                                                                    \
        circular_linked_list_node_t *current = list->head;                                                   \
        while (current)                                                                                      \
        {                                                                                                    \
            circular_linked_list_node_t *next = current->next;                                               \
            free(current->data);                                                                             \
            free(current);                                                                                   \
            current = next;                                                                                  \
        }                                                                                                    \
        free(list);                                                                                          \
    }

DEFINE_CIRCULAR_LINKED_LIST_FUNCTIONS(char, char)
DEFINE_CIRCULAR_LINKED_LIST_FUNCTIONS(int, int)
DEFINE_CIRCULAR_LINKED_LIST_FUNCTIONS(float, float)
DEFINE_CIRCULAR_LINKED_LIST_FUNCTIONS(double, double)
DEFINE_STRING_CIRCULAR_LINKED_LIST_FUNCTIONS

size_t circular_linked_list_size(circular_linked_list_t *list)
{
    return list->size;
}

int is_circular_linked_list_empty(circular_linked_list_t *list)
{
    return list->size == 0;
}

circular_linked_list_t *create_circular_linked_list(size_t element_size)
{
    circular_linked_list_t *list = (circular_linked_list_t *)malloc(sizeof(circular_linked_list_t));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

linked_list_error_t insert_front_circular(circular_linked_list_t *list, void *element)
{
    circular_linked_list_node_t *new_node = malloc(sizeof(circular_linked_list_node_t));
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
        new_node->next = list->head;
    }
    else
    {
        circular_linked_list_node_t *current = list->head;
        while (current->next != list->head)
        {
            current = current->next;
        }

        new_node->next = list->head;
        current->next = new_node;
        list->head = new_node;
    }

    list->size++;
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t insert_back_circular(circular_linked_list_t *list, void *element)
{
    circular_linked_list_node_t *new_node = malloc(sizeof(circular_linked_list_node_t));
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
        new_node->next = list->head;
    }
    else
    {
        circular_linked_list_node_t *current = list->head;
        while (current->next != list->head)
        {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = list->head;
    }

    list->size++;
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t remove_front_circular(circular_linked_list_t *list, void *output)
{
    if (list->head == NULL)
    {
        return LINKED_LIST_EMPTY;
    }

    if (list->head->next == list->head)
    {
        circular_linked_list_node_t *temp = list->head;
        mempcpy(output, temp->data, list->element_size);
        free(temp->data);
        free(temp);
        list->head = NULL;
        list->size = 0;
        return LINKED_LIST_SUCCESS;
    }

    circular_linked_list_node_t *current = list->head;
    while (current->next != list->head)
    {
        current = current->next;
    }

    circular_linked_list_node_t *first_node = list->head;
    list->head = first_node->next;
    current->next = list->head;
    free(first_node->data);
    free(first_node);

    list->size--;
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t remove_back_circular(circular_linked_list_t *list, void *output)
{
    if (list->head == NULL)
    {
        return LINKED_LIST_EMPTY;
    }

    if (list->head->next == list->head)
    {
        circular_linked_list_node_t *temp = list->head;
        mempcpy(output, temp->data, list->element_size);
        free(temp->data);
        free(temp);
        list->head = NULL;
        list->size = 0;
        return LINKED_LIST_SUCCESS;
    }

    circular_linked_list_node_t *prev = list->head;
    circular_linked_list_node_t *current = list->head->next;
    while (current->next != list->head)
    {
        prev = current;
        current = current->next;
    }

    prev->next = list->head;
    free(current->data);
    free(current);

    list->size--;
    return LINKED_LIST_SUCCESS;
}

linked_list_error_t get_circular(circular_linked_list_t *list, size_t index, void *output)
{
    if (is_circular_linked_list_empty(list))
    {
        return LINKED_LIST_EMPTY;
    }

    if (index >= list->size)
    {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    circular_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    memcpy(output, current->data, list->element_size);

    return LINKED_LIST_SUCCESS;
}

linked_list_error_t set_circular(circular_linked_list_t *list, size_t index, void *element)
{
    if (is_circular_linked_list_empty(list))
    {
        return LINKED_LIST_EMPTY;
    }

    if (index > list->size)
    {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    circular_linked_list_node_t *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    memcpy(current->data, element, list->element_size);

    return LINKED_LIST_SUCCESS;
}

void free_circular_linked_list(circular_linked_list_t *list)
{
    if (!list)
    {
        return;
    }

    if (!list->head)
    {
        free(list);
        return;
    }

    circular_linked_list_node_t *current = list->head;
    do
    {
        circular_linked_list_node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    } while (current->next != list->head);
    free(list);
}