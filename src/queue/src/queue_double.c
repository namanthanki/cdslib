#include "queue.h"

queue_t *create_double_queue()
{
    return create_queue(sizeof(double));
}

queue_error_t enqueue_double(queue_t *queue, double value)
{
    return enqueue(queue, &value);
}

queue_error_t dequeue_double(queue_t *queue, double *value)
{
    return dequeue(queue, value);
}

queue_error_t peek_double(queue_t *queue, double *value)
{
    return peek(queue, value);
}
