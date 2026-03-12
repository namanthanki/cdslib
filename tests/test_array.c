#include "ds/ds_array.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_array_set_get() {
    ds_array_t *arr = ds_array_create(10, sizeof(int), NULL, NULL, NULL);
    assert(arr != NULL);

    for (int i = 0; i < 10; i++) {
        ds_array_set(arr, i, &i);
    }

    assert(ds_array_capacity(arr) == 10);

    for (int i = 0; i < 10; i++) {
        int val;
        ds_error_t err = ds_array_get(arr, i, &val);
        assert(err == DS_SUCCESS);
        assert(val == i);
    }

    ds_array_destroy(arr);
    printf("test_array_set_get passed\n");
}

void test_array_bounds_checking() {
    ds_array_t *arr = ds_array_create(5, sizeof(int), NULL, NULL, NULL);
    assert(arr != NULL);

    int val = 10;

    // Valid access
    ds_error_t err = ds_array_set(arr, 0, &val);
    assert(err == DS_SUCCESS);

    err = ds_array_set(arr, 4, &val);
    assert(err == DS_SUCCESS);

    // Out of bounds access should fail
    err = ds_array_set(arr, 5, &val);
    assert(err == DS_ERR_OUT_OF_RANGE);

    err = ds_array_set(arr, 100, &val);
    assert(err == DS_ERR_OUT_OF_RANGE);

    // Get out of bounds
    int out;
    err = ds_array_get(arr, 5, &out);
    assert(err == DS_ERR_OUT_OF_RANGE);

    ds_array_destroy(arr);
    printf("test_array_bounds_checking passed\n");
}

void test_array_update() {
    ds_array_t *arr = ds_array_create(5, sizeof(int), NULL, NULL, NULL);
    assert(arr != NULL);

    // Set initial values
    for (int i = 0; i < 5; i++) {
        ds_array_set(arr, i, &i);
    }

    // Update values
    for (int i = 0; i < 5; i++) {
        int new_val = i * 10;
        ds_array_set(arr, i, &new_val);
    }

    // Verify updates
    for (int i = 0; i < 5; i++) {
        int val;
        ds_array_get(arr, i, &val);
        assert(val == i * 10);
    }

    ds_array_destroy(arr);
    printf("test_array_update passed\n");
}

void test_array_clear() {
    ds_array_t *arr = ds_array_create(5, sizeof(int), NULL, NULL, NULL);
    assert(arr != NULL);

    // Set values
    for (int i = 0; i < 5; i++) {
        ds_array_set(arr, i, &i);
    }

    // Clear
    ds_array_clear(arr);

    // Capacity should remain the same
    assert(ds_array_capacity(arr) == 5);

    ds_array_destroy(arr);
    printf("test_array_clear passed\n");
}

void test_array_data_pointer() {
    ds_array_t *arr = ds_array_create(3, sizeof(int), NULL, NULL, NULL);
    assert(arr != NULL);

    // Set values
    int vals[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        ds_array_set(arr, i, &vals[i]);
    }

    // Get raw data pointer
    int *data = (int *)ds_array_data(arr);
    assert(data != NULL);
    assert(data[0] == 10);
    assert(data[1] == 20);
    assert(data[2] == 30);

    ds_array_destroy(arr);
    printf("test_array_data_pointer passed\n");
}

void test_array_with_destructor() {
    void (*destructor)(void *) = free;
    ds_array_t *arr = ds_array_create(2, sizeof(char*), destructor, NULL, NULL);
    assert(arr != NULL);

    // Set string pointers
    char *s1 = malloc(10);
    char *s2 = malloc(10);
    strcpy(s1, "hello");
    strcpy(s2, "world");

    ds_array_set(arr, 0, &s1);
    ds_array_set(arr, 1, &s2);

    // Update one element (should call destructor on old value)
    char *s3 = malloc(10);
    strcpy(s3, "new");
    ds_array_set(arr, 0, &s3);

    // Clear calls destructor on remaining elements
    ds_array_clear(arr);

    ds_array_destroy(arr);
    printf("test_array_with_destructor passed\n");
}

void test_array_different_types() {
    // Test with chars
    ds_array_t *arr_char = ds_array_create(5, sizeof(char), NULL, NULL, NULL);
    assert(arr_char != NULL);

    for (int i = 0; i < 5; i++) {
        char c = 'a' + i;
        ds_array_set(arr_char, i, &c);
    }

    char c_out;
    ds_array_get(arr_char, 0, &c_out);
    assert(c_out == 'a');

    ds_array_destroy(arr_char);

    // Test with doubles
    ds_array_t *arr_double = ds_array_create(3, sizeof(double), NULL, NULL, NULL);
    assert(arr_double != NULL);

    double vals[] = {1.5, 2.5, 3.5};
    for (int i = 0; i < 3; i++) {
        ds_array_set(arr_double, i, &vals[i]);
    }

    double d_out;
    ds_array_get(arr_double, 1, &d_out);
    assert(d_out == 2.5);

    ds_array_destroy(arr_double);

    printf("test_array_different_types passed\n");
}

int main() {
    test_array_set_get();
    test_array_bounds_checking();
    test_array_update();
    test_array_clear();
    test_array_data_pointer();
    test_array_with_destructor();
    test_array_different_types();
    printf("\nAll array tests passed\n");
    return 0;
}
