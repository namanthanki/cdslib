#include "ds/ds_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Define a custom destructor for our dynamically allocated strings
void string_destructor(void *elem) {
    char **str = (char **)elem;
    if (*str) {
        printf("  [Destructor] Freeing string: %s\n", *str);
        free(*str);
    }
}

// 2. Generate type-safe inline wrappers for 'char*'
DS_VECTOR_DEFINE_TYPE(char*, string)

int main() {
    printf("--- Vector Example ---\n");

    // 3. Create a vector of string pointers (char*)
    // We pass our custom destructor so the vector automatically frees the strings
    // when they are removed or when the vector is destroyed.
    ds_vector_t *vec = ds_vector_create(sizeof(char*), string_destructor, NULL, NULL);
    if (!vec) {
        fprintf(stderr, "Failed to create vector\n");
        return 1;
    }

    // 4. Allocate some strings and push them into the vector
    char *s1 = strdup("Apple");
    char *s2 = strdup("Banana");
    char *s3 = strdup("Cherry");

    printf("Pushing elements...\n");
    ds_vector_push_back_string(vec, s1);
    ds_vector_push_back_string(vec, s2);
    ds_vector_push_back_string(vec, s3);

    // 5. Iterate and print the elements
    printf("\nVector contents (size: %zu, capacity: %zu):\n", 
           ds_vector_size(vec), ds_vector_capacity(vec));
           
    for (size_t i = 0; i < ds_vector_size(vec); i++) {
        char *val;
        ds_vector_get_string(vec, i, &val);
        printf("  [%zu]: %s\n", i, val);
    }

    // 6. Remove an element (this will trigger the destructor for "Banana")
    printf("\nRemoving element at index 1...\n");
    ds_vector_remove(vec, 1, NULL); // Passing NULL for out_value triggers the destructor

    printf("\nVector contents after removal (size: %zu):\n", ds_vector_size(vec));
    for (size_t i = 0; i < ds_vector_size(vec); i++) {
        char *val;
        ds_vector_get_string(vec, i, &val);
        printf("  [%zu]: %s\n", i, val);
    }

    // 7. Destroy the vector (this will trigger the destructor for the remaining elements)
    printf("\nDestroying vector...\n");
    ds_vector_destroy(vec);

    printf("--- Example Complete ---\n");
    return 0;
}
