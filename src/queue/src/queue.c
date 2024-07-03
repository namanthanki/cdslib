#include "queue.h"

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
    queue->data[queue->rear] = (void *)malloc(queue->element_size);
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

queue_error_t resize_queue(queue_t *queue, int new_capacity)
{
    void **new_data = (void **)realloc(queue->data, sizeof(void *) * new_capacity);
    if (!new_data)
    {
        return QUEUE_MEMORY_ERROR;
    }

    queue->data = new_data;
    queue->capacity = new_capacity;

    return QUEUE_SUCCESS;
}

void free_queue(queue_t *queue)
{
    for (int i = 0; i < queue->size; i++)
    {
        int index = (queue->front + i) % queue->capacity;
        free(queue->data[index]);
    }

    free(queue->data);
    free(queue);
}

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