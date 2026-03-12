#include "ds/ds_list.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_list_push_pop() {
    ds_list_t *l = ds_list_create(sizeof(int), NULL, NULL, NULL);
    assert(l != NULL);

    for (int i = 0; i < 100; i++) {
        ds_list_push_back(l, &i);
    }

    assert(ds_list_size(l) == 100);

    for (int i = 0; i < 100; i++) {
        int val;
        ds_list_pop_front(l, &val);
        assert(val == i);
    }

    assert(ds_list_is_empty(l));
    ds_list_destroy(l);
    printf("test_list_push_pop passed\n");
}

void test_list_push_front_pop_back() {
    ds_list_t *l = ds_list_create(sizeof(int), NULL, NULL, NULL);
    assert(l != NULL);

    // Push from front
    for (int i = 0; i < 10; i++) {
        ds_list_push_front(l, &i);
    }
    assert(ds_list_size(l) == 10);

    // Pop from back (should get in reverse order: 0, 1, 2, ...)
    for (int i = 0; i < 10; i++) {
        int val;
        ds_list_pop_back(l, &val);
        assert(val == i);
    }

    assert(ds_list_is_empty(l));
    ds_list_destroy(l);
    printf("test_list_push_front_pop_back passed\n");
}

void test_list_iterator() {
    ds_list_t *l = ds_list_create(sizeof(int), NULL, NULL, NULL);
    assert(l != NULL);

    // Add elements
    for (int i = 0; i < 5; i++) {
        ds_list_push_back(l, &i);
    }

    // Forward iteration
    int idx = 0;
    for (ds_list_node_t *node = ds_list_begin(l); node != NULL; node = ds_list_next(node)) {
        int *val = (int *)ds_list_node_data(node);
        assert(*val == idx);
        idx++;
    }

    // Backward iteration
    idx = 4;
    for (ds_list_node_t *node = ds_list_end(l); node != NULL; node = ds_list_prev(node)) {
        int *val = (int *)ds_list_node_data(node);
        assert(*val == idx);
        idx--;
    }

    ds_list_destroy(l);
    printf("test_list_iterator passed\n");
}

void test_list_insert_after() {
    ds_list_t *l = ds_list_create(sizeof(int), NULL, NULL, NULL);
    assert(l != NULL);

    // Create: 1, 2, 3
    int val = 1;
    ds_list_push_back(l, &val);
    val = 3;
    ds_list_push_back(l, &val);

    // Get first node and insert 2 after it
    ds_list_node_t *first = ds_list_begin(l);
    assert(first != NULL);
    val = 2;
    ds_list_insert_after(l, first, &val);
    assert(ds_list_size(l) == 3);

    // Verify order: 1, 2, 3
    int idx = 1;
    for (ds_list_node_t *node = ds_list_begin(l); node != NULL; node = ds_list_next(node)) {
        int *v = (int *)ds_list_node_data(node);
        assert(*v == idx);
        idx++;
    }

    ds_list_destroy(l);
    printf("test_list_insert_after passed\n");
}

void test_list_remove() {
    ds_list_t *l = ds_list_create(sizeof(int), NULL, NULL, NULL);
    assert(l != NULL);

    // Create: 1, 2, 3, 4, 5
    for (int i = 1; i <= 5; i++) {
        ds_list_push_back(l, &i);
    }
    assert(ds_list_size(l) == 5);

    // Remove second node (value 2)
    ds_list_node_t *second = ds_list_next(ds_list_begin(l));
    int removed;
    ds_list_remove(l, second, &removed);
    assert(removed == 2 && ds_list_size(l) == 4);

    // Verify: 1, 3, 4, 5
    int expected[] = {1, 3, 4, 5};
    int idx = 0;
    for (ds_list_node_t *node = ds_list_begin(l); node != NULL; node = ds_list_next(node)) {
        int *v = (int *)ds_list_node_data(node);
        assert(*v == expected[idx]);
        idx++;
    }

    ds_list_destroy(l);
    printf("test_list_remove passed\n");
}

void test_list_clear() {
    ds_list_t *l = ds_list_create(sizeof(int), NULL, NULL, NULL);
    assert(l != NULL);

    for (int i = 0; i < 20; i++) {
        ds_list_push_back(l, &i);
    }
    assert(ds_list_size(l) == 20);

    ds_list_clear(l);
    assert(ds_list_is_empty(l));
    assert(ds_list_size(l) == 0);
    assert(ds_list_begin(l) == NULL);

    ds_list_destroy(l);
    printf("test_list_clear passed\n");
}

void test_list_with_destructor() {
    void (*destructor)(void *) = free;
    ds_list_t *l = ds_list_create(sizeof(char*), destructor, NULL, NULL);
    assert(l != NULL);

    // Add string pointers
    char *s1 = malloc(10);
    char *s2 = malloc(10);
    strcpy(s1, "hello");
    strcpy(s2, "world");

    ds_list_push_back(l, &s1);
    ds_list_push_back(l, &s2);
    assert(ds_list_size(l) == 2);

    // Remove with destructor call
    ds_list_node_t *first = ds_list_begin(l);
    ds_list_remove(l, first, NULL);
    assert(ds_list_size(l) == 1);

    // Clear calls destructor on remaining
    ds_list_clear(l);
    assert(ds_list_is_empty(l));

    ds_list_destroy(l);
    printf("test_list_with_destructor passed\n");
}

int main() {
    test_list_push_pop();
    test_list_push_front_pop_back();
    test_list_iterator();
    test_list_insert_after();
    test_list_remove();
    test_list_clear();
    test_list_with_destructor();
    printf("\nAll list tests passed\n");
    return 0;
}
