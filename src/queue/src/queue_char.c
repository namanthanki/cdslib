#include "queue.h"

queue_t *create_char_queue()
{
    return create_queue(sizeof(char));
}

queue_error_t enqueue_char(queue_t *queue, char value)
{
    return enqueue(queue, &value);
}

queue_error_t dequeue_char(queue_t *queue, char *value)
{
    return dequeue(queue, value);
}

queue_error_t peek_char(queue_t *queue, char *value)
{
    return peek(queue, value);
}
