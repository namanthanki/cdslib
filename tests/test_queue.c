#include "ds/ds_queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_queue_enqueue_dequeue() {
    ds_queue_t *q = ds_queue_create(sizeof(int), NULL, NULL, NULL);
    assert(q != NULL);

    for (int i = 0; i < 100; i++) {
        ds_queue_enqueue(q, &i);
    }

    assert(ds_queue_size(q) == 100);

    for (int i = 0; i < 100; i++) {
        int val;
        ds_queue_dequeue(q, &val);
        assert(val == i);
    }

    assert(ds_queue_is_empty(q));
    ds_queue_destroy(q);
    printf("test_queue_enqueue_dequeue passed\n");
}

void test_queue_peek() {
    ds_queue_t *q = ds_queue_create(sizeof(int), NULL, NULL, NULL);
    assert(q != NULL);

    // Add elements
    for (int i = 1; i <= 5; i++) {
        ds_queue_enqueue(q, &i);
    }

    // Peek should return first element without removing it
    int val;
    ds_error_t err = ds_queue_peek(q, &val);
    assert(err == DS_SUCCESS && val == 1);
    assert(ds_queue_size(q) == 5);

    // Dequeue should match peek
    err = ds_queue_dequeue(q, &val);
    assert(err == DS_SUCCESS && val == 1);
    assert(ds_queue_size(q) == 4);

    ds_queue_destroy(q);
    printf("test_queue_peek passed\n");
}

void test_queue_empty() {
    ds_queue_t *q = ds_queue_create(sizeof(int), NULL, NULL, NULL);
    assert(q != NULL);

    // Empty queue
    assert(ds_queue_is_empty(q));
    assert(ds_queue_size(q) == 0);

    // Dequeue from empty should fail
    int val;
    ds_error_t err = ds_queue_dequeue(q, &val);
    assert(err == DS_ERR_EMPTY);

    // Peek from empty should fail
    err = ds_queue_peek(q, &val);
    assert(err == DS_ERR_EMPTY);

    ds_queue_destroy(q);
    printf("test_queue_empty passed\n");
}

void test_queue_clear() {
    ds_queue_t *q = ds_queue_create(sizeof(int), NULL, NULL, NULL);
    assert(q != NULL);

    for (int i = 0; i < 20; i++) {
        ds_queue_enqueue(q, &i);
    }
    assert(ds_queue_size(q) == 20);

    ds_queue_clear(q);
    assert(ds_queue_is_empty(q));
    assert(ds_queue_size(q) == 0);

    ds_queue_destroy(q);
    printf("test_queue_clear passed\n");
}

void test_queue_fifo_order() {
    ds_queue_t *q = ds_queue_create(sizeof(int), NULL, NULL, NULL);
    assert(q != NULL);

    // Enqueue 1, 2, 3, 4, 5
    for (int i = 1; i <= 5; i++) {
        ds_queue_enqueue(q, &i);
    }

    // Dequeue should be 1, 2, 3, 4, 5 (FIFO)
    for (int i = 1; i <= 5; i++) {
        int val;
        ds_queue_dequeue(q, &val);
        assert(val == i);
    }

    ds_queue_destroy(q);
    printf("test_queue_fifo_order passed\n");
}

void test_queue_with_destructor() {
    void (*destructor)(void *) = free;
    ds_queue_t *q = ds_queue_create(sizeof(char*), destructor, NULL, NULL);
    assert(q != NULL);

    char *s1 = malloc(10);
    char *s2 = malloc(10);
    strcpy(s1, "first");
    strcpy(s2, "second");

    ds_queue_enqueue(q, &s1);
    ds_queue_enqueue(q, &s2);
    assert(ds_queue_size(q) == 2);

    // Clear calls destructor
    ds_queue_clear(q);
    assert(ds_queue_is_empty(q));

    ds_queue_destroy(q);
    printf("test_queue_with_destructor passed\n");
}

int main() {
    test_queue_enqueue_dequeue();
    test_queue_peek();
    test_queue_empty();
    test_queue_clear();
    test_queue_fifo_order();
    test_queue_with_destructor();
    printf("\nAll queue tests passed\n");
    return 0;
}
