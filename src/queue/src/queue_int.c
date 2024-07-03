#include "queue.h"

queue_t *create_int_queue()
{
    return create_queue(sizeof(int));
}

queue_error_t enqueue_int(queue_t *queue, int value)
{
    return enqueue(queue, &value);
}

queue_error_t dequeue_int(queue_t *queue, int *value)
{
    return dequeue(queue, value);
}

queue_error_t peek_int(queue_t *queue, int *value)
{
    return peek(queue, value);
}
