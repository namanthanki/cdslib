#include "queue.h"
#include <string.h>

queue_t *create_string_queue()
{
    return create_queue(sizeof(char *));
}

queue_error_t enqueue_string(queue_t *queue, const char *value)
{
    char *copy = strdup(value);
    if (!copy)
    {
        return QUEUE_MEMORY_ERROR;
    }

    queue_error_t result = enqueue(queue, &copy);

    if (result != QUEUE_SUCCESS)
    {
        free(copy);
    }

    return result;
}

queue_error_t dequeue_string(queue_t *queue, char **value)
{
    char *dequeued_value;
    queue_error_t result = dequeue(queue, &dequeued_value);
    if (result == QUEUE_SUCCESS)
    {
        *value = dequeued_value;
    }
    return result;
}

queue_error_t peek_string(queue_t *queue, char **value)
{
    return peek(queue, value);
}

void free_string_queue(queue_t *queue)
{
    while (queue->front != NULL)
    {
        char *value;
        dequeue_string(queue, &value);
        free(value);
    }
    free_queue(queue);
}