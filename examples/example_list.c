#include "ds/ds_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a custom struct to store in the list
typedef struct {
    int id;
    char name[32];
} user_t;

// Generate type-safe inline wrappers for user_t
DS_LIST_DEFINE_TYPE(user_t, user)

// A custom destructor for user_t (if it contained dynamic memory, we'd free it here)
// In this case, it's just for demonstration
void user_destructor(void *data) {
    user_t *user = (user_t *)data;
    printf("  [Destructor] Cleaning up user: %d - %s\n", user->id, user->name);
}

int main() {
    printf("--- Doubly Linked List Example ---\n");

    // 1. Create the list
    ds_list_t *list = ds_list_create(sizeof(user_t), user_destructor, NULL, NULL);
    if (!list) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    // 2. Create some users
    user_t u1 = {1, "Alice"};
    user_t u2 = {2, "Bob"};
    user_t u3 = {3, "Charlie"};
    user_t u4 = {4, "David"};

    // 3. Insert elements
    printf("Pushing elements to back and front...\n");
    ds_list_push_back_user(list, u2);
    ds_list_push_back_user(list, u3);
    ds_list_push_front_user(list, u1); // Alice goes to the front

    printf("List size: %zu\n", ds_list_size(list));

    // 4. Iterate through the list (forward)
    printf("\nIterating forward:\n");
    ds_list_node_t *node = ds_list_begin(list);
    while (node != NULL) {
        user_t *u = (user_t *)ds_list_node_data(node);
        printf("  User: %d - %s\n", u->id, u->name);
        node = ds_list_next(node);
    }

    // 5. Insert at a specific position (after the first element)
    printf("\nInserting David after Alice...\n");
    ds_list_insert_after(list, ds_list_begin(list), &u4);

    // 6. Iterate through the list (backward)
    printf("\nIterating backward:\n");
    node = ds_list_end(list);
    while (node != NULL) {
        user_t *u = (user_t *)ds_list_node_data(node);
        printf("  User: %d - %s\n", u->id, u->name);
        node = ds_list_prev(node);
    }

    // 7. Remove elements
    printf("\nPopping front and back...\n");
    user_t popped_front, popped_back;
    
    if (ds_list_pop_front_user(list, &popped_front) == DS_SUCCESS) {
        printf("  Popped front: %s\n", popped_front.name);
    }
    
    if (ds_list_pop_back_user(list, &popped_back) == DS_SUCCESS) {
        printf("  Popped back: %s\n", popped_back.name);
    }

    printf("List size after pops: %zu\n", ds_list_size(list));

    // 8. Cleanup
    // The destructor will be called for the remaining elements (Bob and David)
    printf("\nDestroying list...\n");
    ds_list_destroy(list);

    printf("--- Example Complete ---\n");
    return 0;
}
