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

#define DECLARE_QUEUE_FUNCTIONS(TYPE, SUFFIX)                    \
    queue_t *create_##SUFFIX##_queue();                          \
    queue_error_t enqueue_##SUFFIX(queue_t *queue, TYPE value);  \
    queue_error_t dequeue_##SUFFIX(queue_t *queue, TYPE *value); \
    queue_error_t peek_##SUFFIX(queue_t *queue, TYPE *value);

#define DECLARE_STRING_QUEUE_FUNCTIONS                               \
    queue_t *create_string_queue();                                  \
    queue_error_t enqueue_string(queue_t *queue, const char *value); \
    queue_error_t dequeue_string(queue_t *queue, char **value);      \
    queue_error_t peek_string(queue_t *queue, char **value);         \
    void free_string_queue(queue_t *queue);

DECLARE_QUEUE_FUNCTIONS(char, char)
DECLARE_QUEUE_FUNCTIONS(int, int)
DECLARE_QUEUE_FUNCTIONS(float, float)
DECLARE_QUEUE_FUNCTIONS(double, double)
DECLARE_STRING_QUEUE_FUNCTIONS

// Generic functions
queue_t *create_queue(size_t element_size);
queue_error_t enqueue(queue_t *queue, const void *element);
queue_error_t dequeue(queue_t *queue, void *output);
queue_error_t peek(queue_t *queue, void *output);
queue_error_t resize_queue(queue_t *queue, size_t new_capacity);
queue_error_t shrink_queue(queue_t *queue);
void free_queue(queue_t *queue);

int is_queue_full(queue_t *queue);
int is_queue_empty(queue_t *queue);
int queue_size(queue_t *queue);

#endif // QUEUE_H