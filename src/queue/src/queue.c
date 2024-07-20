#include "queue.h"
#include "data_structure_utils.h"
#include <stdlib.h>
#include <string.h>

#define DEFINE_QUEUE_FUNCTIONS(TYPE, SUFFIX)                    \
    queue_t *create_##SUFFIX##_queue()                          \
    {                                                           \
        return create_queue(sizeof(TYPE));                      \
    }                                                           \
                                                                \
    queue_error_t enqueue_##SUFFIX(queue_t *queue, TYPE value)  \
    {                                                           \
        return enqueue(queue, &value);                          \
    }                                                           \
                                                                \
    queue_error_t dequeue_##SUFFIX(queue_t *queue, TYPE *value) \
    {                                                           \
        return dequeue(queue, value);                           \
    }                                                           \
                                                                \
    queue_error_t peek_##SUFFIX(queue_t *queue, TYPE *value)    \
    {                                                           \
        return peek(queue, value);                              \
    }

#define DEFINE_STRING_QUEUE_FUNCTIONS                               \
    queue_t *create_string_queue()                                  \
    {                                                               \
        return create_queue(sizeof(char *));                        \
    }                                                               \
                                                                    \
    queue_error_t enqueue_string(queue_t *queue, const char *value) \
    {                                                               \
        char *copy = strdup(value);                                 \
        if (!copy)                                                  \
        {                                                           \
            return QUEUE_MEMORY_ERROR;                              \
        }                                                           \
                                                                    \
        queue_error_t result = enqueue(queue, &copy);               \
                                                                    \
        if (result != QUEUE_SUCCESS)                                \
        {                                                           \
            free(copy);                                             \
        }                                                           \
                                                                    \
        return result;                                              \
    }                                                               \
                                                                    \
    queue_error_t dequeue_string(queue_t *queue, char **value)      \
    {                                                               \
        char *popped_value;                                         \
        queue_error_t result = dequeue(queue, &popped_value);       \
        if (result == QUEUE_SUCCESS)                                \
        {                                                           \
            *value = popped_value;                                  \
        }                                                           \
        return result;                                              \
    }                                                               \
                                                                    \
    queue_error_t peek_string(queue_t *queue, char **value)         \
    {                                                               \
        char *peeked_value;                                         \
        queue_error_t result = peek(queue, &peeked_value);          \
        if (result == QUEUE_SUCCESS)                                \
        {                                                           \
            *value = peeked_value;                                  \
        }                                                           \
        return result;                                              \
    }                                                               \
                                                                    \
    void free_string_queue(queue_t *queue)                          \
    {                                                               \
        for (size_t i = 0; i < queue->size; i++)                    \
        {                                                           \
            size_t index = (queue->front + i) % queue->capacity;    \
            free(queue->data[index]);                               \
        }                                                           \
                                                                    \
        free(queue->data);                                          \
        free(queue);                                                \
    }

DEFINE_QUEUE_FUNCTIONS(char, char)
DEFINE_QUEUE_FUNCTIONS(int, int)
DEFINE_QUEUE_FUNCTIONS(float, float)
DEFINE_QUEUE_FUNCTIONS(double, double)
DEFINE_STRING_QUEUE_FUNCTIONS

int is_queue_full(queue_t *queue)
{
    return queue->size == queue->capacity;
}

int is_queue_empty(queue_t *queue)
{
    return queue->size == 0;
}

int queue_size(queue_t *queue)
{
    return queue->size;
}

queue_t *create_queue(size_t element_size)
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    if (!queue)
    {
        return NULL;
    }

    queue->data = (void **)malloc(sizeof(void *) * 100);
    if (!queue->data)
    {
        free(queue);
        return NULL;
    }

    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = 100;
    queue->element_size = element_size;

    return queue;
}

void copy_func(void *dest, void *src, size_t size)
{
    memcpy(dest, src, size);
}

void free_func(void *data)
{
    free(data);
}

queue_error_t resize_queue(queue_t *queue, size_t new_capacity)
{
    resize_error_t result = resize_data_structure(
        (void **)&queue->data,
        &queue->capacity,
        &queue->size,
        queue->element_size,
        new_capacity,
        copy_func,
        free_func);

    if (result != RESIZE_SUCCESS)
    {
        return QUEUE_MEMORY_ERROR;
    }

    return QUEUE_SUCCESS;
}

queue_error_t shrink_queue(queue_t *queue)
{
    resize_error_t result = shrink_data_structure(
        queue,
        &queue->capacity,
        &queue->size,
        (resize_func_t)resize_queue);

    if (result != RESIZE_SUCCESS)
    {
        return QUEUE_MEMORY_ERROR;
    }

    return QUEUE_SUCCESS;
}

queue_error_t enqueue(queue_t *queue, const void *element)
{
    if (is_queue_full(queue))
    {
        queue_error_t resize_result = resize_queue(queue, queue->capacity * 2);
        if (resize_result != QUEUE_SUCCESS)
        {
            return resize_result;
        }
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = malloc(queue->element_size);
    if (!queue->data[queue->rear])
    {
        return QUEUE_MEMORY_ERROR;
    }

    memcpy(queue->data[queue->rear], element, queue->element_size);

    if (queue->front == -1)
    {
        queue->front = queue->rear;
    }

    queue->size++;

    return QUEUE_SUCCESS;
}

queue_error_t dequeue(queue_t *queue, void *output)
{
    if (is_queue_empty(queue))
    {
        return QUEUE_UNDERFLOW;
    }

    memcpy(output, queue->data[queue->front], queue->element_size);
    free(queue->data[queue->front]);

    if (queue->front == queue->rear)
    {
        queue->front = -1;
        queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % queue->capacity;
    }

    queue->size--;

    return QUEUE_SUCCESS;
}

queue_error_t peek(queue_t *queue, void *output)
{
    if (is_queue_empty(queue))
    {
        return QUEUE_UNDERFLOW;
    }

    memcpy(output, queue->data[queue->front], queue->element_size);

    return QUEUE_SUCCESS;
}

void free_queue(queue_t *queue)
{
    for (size_t i = 0; i < queue->size; i++)
    {
        size_t index = (queue->front + i) % queue->capacity;
        free(queue->data[index]);
    }

    free(queue->data);
    free(queue);
}