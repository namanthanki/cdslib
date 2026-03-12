#include "ds/ds_stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_stack_push_pop() {
    ds_stack_t *s = ds_stack_create(sizeof(int), NULL, NULL, NULL);
    assert(s != NULL);

    for (int i = 0; i < 100; i++) {
        ds_stack_push(s, &i);
    }

    assert(ds_stack_size(s) == 100);

    for (int i = 99; i >= 0; i--) {
        int val;
        ds_stack_pop(s, &val);
        assert(val == i);
    }

    assert(ds_stack_is_empty(s));
    ds_stack_destroy(s);
    printf("test_stack_push_pop passed\n");
}

void test_stack_peek() {
    ds_stack_t *s = ds_stack_create(sizeof(int), NULL, NULL, NULL);
    assert(s != NULL);

    // Add elements
    for (int i = 1; i <= 5; i++) {
        ds_stack_push(s, &i);
    }

    // Peek should return top element without removing it
    int val;
    ds_error_t err = ds_stack_peek(s, &val);
    assert(err == DS_SUCCESS && val == 5);
    assert(ds_stack_size(s) == 5);

    // Pop should match peek
    err = ds_stack_pop(s, &val);
    assert(err == DS_SUCCESS && val == 5);
    assert(ds_stack_size(s) == 4);

    ds_stack_destroy(s);
    printf("test_stack_peek passed\n");
}

void test_stack_empty() {
    ds_stack_t *s = ds_stack_create(sizeof(int), NULL, NULL, NULL);
    assert(s != NULL);

    // Empty stack
    assert(ds_stack_is_empty(s));
    assert(ds_stack_size(s) == 0);

    // Pop from empty should fail
    int val;
    ds_error_t err = ds_stack_pop(s, &val);
    assert(err == DS_ERR_EMPTY);

    // Peek from empty should fail
    err = ds_stack_peek(s, &val);
    assert(err == DS_ERR_EMPTY);

    ds_stack_destroy(s);
    printf("test_stack_empty passed\n");
}

void test_stack_clear() {
    ds_stack_t *s = ds_stack_create(sizeof(int), NULL, NULL, NULL);
    assert(s != NULL);

    for (int i = 0; i < 20; i++) {
        ds_stack_push(s, &i);
    }
    assert(ds_stack_size(s) == 20);

    ds_stack_clear(s);
    assert(ds_stack_is_empty(s));
    assert(ds_stack_size(s) == 0);

    ds_stack_destroy(s);
    printf("test_stack_clear passed\n");
}

void test_stack_lifo_order() {
    ds_stack_t *s = ds_stack_create(sizeof(int), NULL, NULL, NULL);
    assert(s != NULL);

    // Push 1, 2, 3, 4, 5
    for (int i = 1; i <= 5; i++) {
        ds_stack_push(s, &i);
    }

    // Pop should be 5, 4, 3, 2, 1 (LIFO)
    for (int i = 5; i >= 1; i--) {
        int val;
        ds_stack_pop(s, &val);
        assert(val == i);
    }

    ds_stack_destroy(s);
    printf("test_stack_lifo_order passed\n");
}

void test_stack_with_destructor() {
    void (*destructor)(void *) = free;
    ds_stack_t *s = ds_stack_create(sizeof(char*), destructor, NULL, NULL);
    assert(s != NULL);

    char *s1 = malloc(10);
    char *s2 = malloc(10);
    strcpy(s1, "first");
    strcpy(s2, "second");

    ds_stack_push(s, &s1);
    ds_stack_push(s, &s2);
    assert(ds_stack_size(s) == 2);

    // Clear calls destructor
    ds_stack_clear(s);
    assert(ds_stack_is_empty(s));

    ds_stack_destroy(s);
    printf("test_stack_with_destructor passed\n");
}

int main() {
    test_stack_push_pop();
    test_stack_peek();
    test_stack_empty();
    test_stack_clear();
    test_stack_lifo_order();
    test_stack_with_destructor();
    printf("\nAll stack tests passed\n");
    return 0;
}
