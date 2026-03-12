#include "ds/ds_vector.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_vector_push_pop() {
    ds_vector_t *v = ds_vector_create(sizeof(int), NULL, NULL, NULL);
    assert(v != NULL);

    for (int i = 0; i < 100; i++) {
        ds_vector_push_back(v, &i);
    }

    assert(ds_vector_size(v) == 100);

    for (int i = 99; i >= 0; i--) {
        int val;
        ds_vector_pop_back(v, &val);
        assert(val == i);
    }

    assert(ds_vector_is_empty(v));
    ds_vector_destroy(v);
    printf("test_vector_push_pop passed\n");
}

void test_vector_insert_remove() {
    ds_vector_t *v = ds_vector_create(sizeof(int), NULL, NULL, NULL);
    assert(v != NULL);

    // Insert at beginning
    int val = 10;
    ds_error_t err = ds_vector_insert(v, 0, &val);
    assert(err == DS_SUCCESS && ds_vector_size(v) == 1);

    // Insert in middle
    val = 20;
    err = ds_vector_insert(v, 1, &val);
    assert(err == DS_SUCCESS && ds_vector_size(v) == 2);

    val = 30;
    err = ds_vector_insert(v, 1, &val);
    assert(err == DS_SUCCESS && ds_vector_size(v) == 3);

    // Verify order: 10, 30, 20
    int out;
    ds_vector_get(v, 0, &out);
    assert(out == 10);
    ds_vector_get(v, 1, &out);
    assert(out == 30);
    ds_vector_get(v, 2, &out);
    assert(out == 20);

    // Remove from middle
    err = ds_vector_remove(v, 1, NULL);
    assert(err == DS_SUCCESS && ds_vector_size(v) == 2);

    ds_vector_get(v, 0, &out);
    assert(out == 10);
    ds_vector_get(v, 1, &out);
    assert(out == 20);

    ds_vector_destroy(v);
    printf("test_vector_insert_remove passed\n");
}

void test_vector_edge_cases() {
    ds_vector_t *v = ds_vector_create(sizeof(int), NULL, NULL, NULL);
    assert(v != NULL);

    // Empty vector checks
    assert(ds_vector_is_empty(v));
    assert(ds_vector_size(v) == 0);
    assert(ds_vector_capacity(v) == 0);

    // Pop from empty should fail
    int out;
    ds_error_t err = ds_vector_pop_back(v, &out);
    assert(err == DS_ERR_EMPTY);

    // Insert at invalid index should fail
    int val = 5;
    err = ds_vector_insert(v, 5, &val);
    assert(err == DS_ERR_OUT_OF_RANGE);

    // Valid single insert
    err = ds_vector_insert(v, 0, &val);
    assert(err == DS_SUCCESS && ds_vector_size(v) == 1);

    // Get from invalid index should fail
    err = ds_vector_get(v, 5, &out);
    assert(err == DS_ERR_OUT_OF_RANGE);

    // Remove from invalid index should fail
    err = ds_vector_remove(v, 5, NULL);
    assert(err == DS_ERR_OUT_OF_RANGE);

    // Clear vector
    ds_vector_clear(v);
    assert(ds_vector_is_empty(v));
    assert(ds_vector_size(v) == 0);

    ds_vector_destroy(v);
    printf("test_vector_edge_cases passed\n");
}

void test_vector_reserve_shrink() {
    ds_vector_t *v = ds_vector_create(sizeof(int), NULL, NULL, NULL);
    assert(v != NULL);

    // Reserve capacity
    ds_error_t err = ds_vector_reserve(v, 100);
    assert(err == DS_SUCCESS);
    assert(ds_vector_capacity(v) >= 100);

    // Add some elements
    for (int i = 0; i < 10; i++) {
        ds_vector_push_back(v, &i);
    }

    assert(ds_vector_size(v) == 10);
    assert(ds_vector_capacity(v) >= 100);

    // Shrink to fit
    err = ds_vector_shrink_to_fit(v);
    assert(err == DS_SUCCESS);
    assert(ds_vector_capacity(v) == 10);

    // Verify data is intact
    int out;
    for (int i = 0; i < 10; i++) {
        ds_vector_get(v, i, &out);
        assert(out == i);
    }

    ds_vector_destroy(v);
    printf("test_vector_reserve_shrink passed\n");
}

void test_vector_with_destructor() {
    void (*destructor)(void *) = free;
    ds_vector_t *v = ds_vector_create(sizeof(char*), destructor, NULL, NULL);
    assert(v != NULL);

    // Allocate and push strings
    char *s1 = malloc(10);
    strcpy(s1, "hello");
    char *s2 = malloc(10);
    strcpy(s2, "world");

    ds_vector_push_back(v, &s1);
    ds_vector_push_back(v, &s2);
    assert(ds_vector_size(v) == 2);

    // Remove with NULL (should call destructor)
    ds_vector_remove(v, 0, NULL);
    assert(ds_vector_size(v) == 1);

    // Clear should call destructor on remaining
    ds_vector_clear(v);
    assert(ds_vector_is_empty(v));

    ds_vector_destroy(v);
    printf("test_vector_with_destructor passed\n");
}

int main() {
    test_vector_push_pop();
    test_vector_insert_remove();
    test_vector_edge_cases();
    test_vector_reserve_shrink();
    test_vector_with_destructor();
    printf("\nAll vector tests passed\n");
    return 0;
}
