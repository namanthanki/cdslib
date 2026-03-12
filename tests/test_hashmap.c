#include "ds/ds_hashmap.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

size_t int_hash(const void *key) {
    return *(const int *)key;
}

int int_cmp(const void *k1, const void *k2) {
    int a = *(const int *)k1;
    int b = *(const int *)k2;
    return (a > b) - (a < b);
}

void test_hashmap_insert_get() {
    ds_hashmap_t *map = ds_hashmap_create(sizeof(int), sizeof(int), int_hash, int_cmp, NULL, NULL, NULL, NULL);
    assert(map != NULL);

    for (int i = 0; i < 100; i++) {
        int val = i * 10;
        ds_hashmap_insert(map, &i, &val);
    }

    assert(ds_hashmap_size(map) == 100);

    for (int i = 0; i < 100; i++) {
        int val;
        ds_error_t err = ds_hashmap_get(map, &i, &val);
        assert(err == DS_SUCCESS);
        assert(val == i * 10);
    }

    ds_hashmap_destroy(map);
    printf("test_hashmap_insert_get passed\n");
}

void test_hashmap_remove() {
    ds_hashmap_t *map = ds_hashmap_create(sizeof(int), sizeof(int), int_hash, int_cmp, NULL, NULL, NULL, NULL);
    assert(map != NULL);

    // Insert some elements
    for (int i = 0; i < 20; i++) {
        int val = i * 10;
        ds_hashmap_insert(map, &i, &val);
    }
    assert(ds_hashmap_size(map) == 20);

    // Remove some elements
    int removed_val;
    ds_error_t err = ds_hashmap_remove(map, &5, &removed_val);
    assert(err == DS_SUCCESS && removed_val == 50);
    assert(ds_hashmap_size(map) == 19);

    err = ds_hashmap_remove(map, &15, &removed_val);
    assert(err == DS_SUCCESS && removed_val == 150);
    assert(ds_hashmap_size(map) == 18);

    // Verify removed elements are gone
    int val;
    err = ds_hashmap_get(map, &5, &val);
    assert(err != DS_SUCCESS);

    // Verify remaining elements still exist
    err = ds_hashmap_get(map, &0, &val);
    assert(err == DS_SUCCESS && val == 0);

    ds_hashmap_destroy(map);
    printf("test_hashmap_remove passed\n");
}

void test_hashmap_contains() {
    ds_hashmap_t *map = ds_hashmap_create(sizeof(int), sizeof(int), int_hash, int_cmp, NULL, NULL, NULL, NULL);
    assert(map != NULL);

    int key = 42, val = 100;
    ds_hashmap_insert(map, &key, &val);

    assert(ds_hashmap_contains(map, &key));

    int missing_key = 999;
    assert(!ds_hashmap_contains(map, &missing_key));

    ds_hashmap_destroy(map);
    printf("test_hashmap_contains passed\n");
}

void test_hashmap_clear() {
    ds_hashmap_t *map = ds_hashmap_create(sizeof(int), sizeof(int), int_hash, int_cmp, NULL, NULL, NULL, NULL);
    assert(map != NULL);

    // Add elements
    for (int i = 0; i < 10; i++) {
        int val = i * 5;
        ds_hashmap_insert(map, &i, &val);
    }
    assert(ds_hashmap_size(map) == 10);

    // Clear
    ds_hashmap_clear(map);
    assert(ds_hashmap_size(map) == 0);

    // Verify all are gone
    int val;
    for (int i = 0; i < 10; i++) {
        ds_error_t err = ds_hashmap_get(map, &i, &val);
        assert(err != DS_SUCCESS);
    }

    ds_hashmap_destroy(map);
    printf("test_hashmap_clear passed\n");
}

void test_hashmap_update() {
    ds_hashmap_t *map = ds_hashmap_create(sizeof(int), sizeof(int), int_hash, int_cmp, NULL, NULL, NULL, NULL);
    assert(map != NULL);

    int key = 5, val = 50;
    ds_hashmap_insert(map, &key, &val);
    assert(ds_hashmap_size(map) == 1);

    // Update the same key
    int new_val = 100;
    ds_hashmap_insert(map, &key, &new_val);
    assert(ds_hashmap_size(map) == 1);  // Size should not increase

    // Verify the update
    int retrieved;
    ds_hashmap_get(map, &key, &retrieved);
    assert(retrieved == 100);

    ds_hashmap_destroy(map);
    printf("test_hashmap_update passed\n");
}

void test_hashmap_with_destructors() {
    void (*val_destructor)(void *) = free;
    ds_hashmap_t *map = ds_hashmap_create(sizeof(int), sizeof(char*), int_hash, int_cmp, NULL, val_destructor, NULL, NULL);
    assert(map != NULL);

    // Insert string values
    int key1 = 1, key2 = 2;
    char *str1 = malloc(20);
    char *str2 = malloc(20);
    strcpy(str1, "value1");
    strcpy(str2, "value2");

    ds_hashmap_insert(map, &key1, &str1);
    ds_hashmap_insert(map, &key2, &str2);
    assert(ds_hashmap_size(map) == 2);

    // Clear should call destructor
    ds_hashmap_clear(map);
    assert(ds_hashmap_size(map) == 0);

    ds_hashmap_destroy(map);
    printf("test_hashmap_with_destructors passed\n");
}

int main() {
    test_hashmap_insert_get();
    test_hashmap_remove();
    test_hashmap_contains();
    test_hashmap_clear();
    test_hashmap_update();
    test_hashmap_with_destructors();
    printf("\nAll hashmap tests passed\n");
    return 0;
}
