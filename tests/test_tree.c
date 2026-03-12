#include "ds/ds_tree.h"
#include <stdio.h>
#include <assert.h>

int int_cmp(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

void test_tree_insert_find() {
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    assert(tree != NULL);

    int vals[] = {5, 3, 7, 2, 4, 6, 8};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        ds_tree_insert(tree, &vals[i]);
    }

    assert(ds_tree_size(tree) == 7);

    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        int out;
        ds_error_t err = ds_tree_find(tree, &vals[i], &out);
        assert(err == DS_SUCCESS);
        assert(out == vals[i]);
    }

    ds_tree_destroy(tree);
    printf("test_tree_insert_find passed\n");
}

void test_tree_remove() {
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    assert(tree != NULL);

    int vals[] = {5, 3, 7, 2, 4, 6, 8};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        ds_tree_insert(tree, &vals[i]);
    }
    assert(ds_tree_size(tree) == 7);

    // Remove leaf node (2)
    int removed;
    ds_error_t err = ds_tree_remove(tree, &vals[3], &removed);
    assert(err == DS_SUCCESS && removed == 2);
    assert(ds_tree_size(tree) == 6);

    // Verify it's gone
    int out;
    err = ds_tree_find(tree, &vals[3], &out);
    assert(err != DS_SUCCESS);

    // Remove node with one child (3)
    int three = 3;
    err = ds_tree_remove(tree, &three, &removed);
    assert(err == DS_SUCCESS && removed == 3);
    assert(ds_tree_size(tree) == 5);

    // Remove root (5)
    int five = 5;
    err = ds_tree_remove(tree, &five, &removed);
    assert(err == DS_SUCCESS && removed == 5);
    assert(ds_tree_size(tree) == 4);

    ds_tree_destroy(tree);
    printf("test_tree_remove passed\n");
}

void test_tree_empty() {
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    assert(tree != NULL);

    assert(ds_tree_is_empty(tree));
    assert(ds_tree_size(tree) == 0);

    // Find in empty tree
    int val = 5;
    int out;
    ds_error_t err = ds_tree_find(tree, &val, &out);
    assert(err != DS_SUCCESS);

    ds_tree_destroy(tree);
    printf("test_tree_empty passed\n");
}

void test_tree_clear() {
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    assert(tree != NULL);

    for (int i = 1; i <= 20; i++) {
        ds_tree_insert(tree, &i);
    }
    assert(ds_tree_size(tree) == 20);

    ds_tree_clear(tree);
    assert(ds_tree_is_empty(tree));
    assert(ds_tree_size(tree) == 0);

    ds_tree_destroy(tree);
    printf("test_tree_clear passed\n");
}

void test_tree_duplicate_insertion() {
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    assert(tree != NULL);

    int val = 5;
    ds_tree_insert(tree, &val);
    assert(ds_tree_size(tree) == 1);

    // Insert duplicate
    ds_tree_insert(tree, &val);
    assert(ds_tree_size(tree) == 2);  // BST typically allows duplicates

    int val2 = 10;
    ds_tree_insert(tree, &val2);
    assert(ds_tree_size(tree) == 3);

    ds_tree_destroy(tree);
    printf("test_tree_duplicate_insertion passed\n");
}

int traversal_count = 0;

void count_callback(const void *value) {
    traversal_count++;
}

void test_tree_traversals() {
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    assert(tree != NULL);

    int vals[] = {5, 3, 7, 2, 4, 6, 8};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        ds_tree_insert(tree, &vals[i]);
    }

    // Inorder traversal
    traversal_count = 0;
    ds_tree_inorder(tree, count_callback);
    assert(traversal_count == 7);

    // Preorder traversal
    traversal_count = 0;
    ds_tree_preorder(tree, count_callback);
    assert(traversal_count == 7);

    // Postorder traversal
    traversal_count = 0;
    ds_tree_postorder(tree, count_callback);
    assert(traversal_count == 7);

    ds_tree_destroy(tree);
    printf("test_tree_traversals passed\n");
}

int main() {
    test_tree_insert_find();
    test_tree_remove();
    test_tree_empty();
    test_tree_clear();
    test_tree_duplicate_insertion();
    test_tree_traversals();
    printf("\nAll tree tests passed\n");
    return 0;
}
