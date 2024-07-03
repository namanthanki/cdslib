#include "queue.h"

queue_t *create_float_queue()
{
    return create_queue(sizeof(float));
}

queue_error_t enqueue_float(queue_t *queue, float value)
{
    return enqueue(queue, &value);
}

queue_error_t dequeue_float(queue_t *queue, float *value)
{
    return dequeue(queue, value);
}

queue_error_t peek_float(queue_t *queue, float *value)
{
    return peek(queue, value);
}