#include "ds/ds_tree.h"
#include <stdio.h>
#include <stdlib.h>

// 1. Define a custom comparison function for integers
int int_cmp(const void *k1, const void *k2) {
    int a = *(const int *)k1;
    int b = *(const int *)k2;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// 2. Generate type-safe inline wrappers for int
DS_TREE_DEFINE_TYPE(int, int)

// 3. Define a callback function for tree traversal
void print_int(const void *data) {
    printf("%d ", *(const int *)data);
}

int main() {
    printf("--- Binary Search Tree Example ---\n");

    // 4. Create the tree
    ds_tree_t *tree = ds_tree_create(sizeof(int), int_cmp, NULL, NULL, NULL);
    if (!tree) {
        fprintf(stderr, "Failed to create tree\n");
        return 1;
    }

    // 5. Insert elements
    printf("Inserting elements: 50, 30, 70, 20, 40, 60, 80\n");
    ds_tree_insert_int(tree, 50);
    ds_tree_insert_int(tree, 30);
    ds_tree_insert_int(tree, 70);
    ds_tree_insert_int(tree, 20);
    ds_tree_insert_int(tree, 40);
    ds_tree_insert_int(tree, 60);
    ds_tree_insert_int(tree, 80);

    printf("Tree size: %zu\n", ds_tree_size(tree));

    // 6. Traverse the tree
    printf("\nIn-order traversal (sorted): ");
    ds_tree_inorder(tree, print_int);
    printf("\n");

    printf("Pre-order traversal: ");
    ds_tree_preorder(tree, print_int);
    printf("\n");

    printf("Post-order traversal: ");
    ds_tree_postorder(tree, print_int);
    printf("\n");

    // 7. Find an element
    printf("\nFinding elements:\n");
    int found_val;
    if (ds_tree_find_int(tree, 40, &found_val) == DS_SUCCESS) {
        printf("  Found: %d\n", found_val);
    } else {
        printf("  40 not found.\n");
    }

    if (ds_tree_find_int(tree, 90, &found_val) == DS_SUCCESS) {
        printf("  Found: %d\n", found_val);
    } else {
        printf("  90 not found.\n");
    }

    // 8. Remove an element
    printf("\nRemoving 30...\n");
    int removed_val;
    if (ds_tree_remove_int(tree, 30, &removed_val) == DS_SUCCESS) {
        printf("  Removed: %d\n", removed_val);
    }

    printf("In-order traversal after removal: ");
    ds_tree_inorder(tree, print_int);
    printf("\n");

    // 9. Cleanup
    printf("\nDestroying tree...\n");
    ds_tree_destroy(tree);

    printf("--- Example Complete ---\n");
    return 0;
}
