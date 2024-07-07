#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <string.h>

typedef enum
{
    QUEUE_SUCCESS = 0,
    QUEUE_OVERFLOW,
    QUEUE_UNDERFLOW,
    QUEUE_MEMORY_ERROR
} queue_error_t;

typedef struct
{
    void **data;
    int front;
    int rear;
    size_t size;
    size_t capacity;
    size_t element_size;
} queue_t;

// generuc
queue_t *create_queue(size_t element_size);
queue_error_t enqueue(queue_t *queue, const void *element);
queue_error_t dequeue(queue_t *queue, void *output);
queue_error_t peek(queue_t *queue, void *output);
queue_error_t resize_queue(queue_t *queue, size_t new_capacity);
queue_error_t shrink_queue(queue_t *queue);
void free_queue(queue_t *queue);

// char
queue_t *create_char_queue();
queue_error_t enqueue_char(queue_t *queue, char value);
queue_error_t dequeue_char(queue_t *queue, char *value);
queue_error_t peek_char(queue_t *queue, char *value);

// int
queue_t *create_int_queue();
queue_error_t enqueue_int(queue_t *queue, int value);
queue_error_t dequeue_int(queue_t *queue, int *value);
queue_error_t peek_int(queue_t *queue, int *value);

// float
queue_t *create_float_queue();
queue_error_t enqueue_float(queue_t *queue, float value);
queue_error_t dequeue_float(queue_t *queue, float *value);
queue_error_t peek_float(queue_t *queue, float *value);

// double
queue_t *create_double_queue();
queue_error_t enqueue_double(queue_t *queue, double value);
queue_error_t dequeue_double(queue_t *queue, double *value);
queue_error_t peek_double(queue_t *queue, double *value);

// string (char *)
queue_t *create_string_queue();
queue_error_t enqueue_string(queue_t *queue, const char *value);
queue_error_t dequeue_string(queue_t *queue, char **value);
queue_error_t peek_string(queue_t *queue, char **value);
void free_string_queue(queue_t *queue);

#endif