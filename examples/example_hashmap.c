#include "ds/ds_hashmap.h"
#include <stdio.h>
#include <string.h>

// 1. Define a custom hash function for strings (djb2 algorithm)
size_t string_hash(const void *key) {
    const char *str = *(const char **)key;
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// 2. Define a custom comparison function for strings
int string_cmp(const void *k1, const void *k2) {
    const char *s1 = *(const char **)k1;
    const char *s2 = *(const char **)k2;
    return strcmp(s1, s2);
}

// 3. Generate type-safe inline wrappers for key: char*, value: int
DS_HASHMAP_DEFINE_TYPE(char*, int, str_int)

int main() {
    printf("--- Hash Map Example ---\n");

    // 4. Create the hash map
    // Keys are char* (string pointers), Values are int
    ds_hashmap_t *map = ds_hashmap_create(
        sizeof(char*), 
        sizeof(int), 
        string_hash, 
        string_cmp, 
        NULL, // No key destructor (we use string literals)
        NULL, // No value destructor (ints don't need freeing)
        NULL, 
        NULL
    );

    if (!map) {
        fprintf(stderr, "Failed to create hash map\n");
        return 1;
    }

    // 5. Insert some key-value pairs
    printf("Inserting elements...\n");
    ds_hashmap_insert_str_int(map, "Alice", 25);
    ds_hashmap_insert_str_int(map, "Bob", 30);
    ds_hashmap_insert_str_int(map, "Charlie", 35);

    printf("Map size: %zu\n", ds_hashmap_size(map));

    // 6. Retrieve values
    printf("\nRetrieving elements:\n");
    
    char *search_keys[] = {"Alice", "Bob", "David"};
    for (int i = 0; i < 3; i++) {
        int val;
        char *key = search_keys[i];
        
        if (ds_hashmap_get_str_int(map, key, &val) == DS_SUCCESS) {
            printf("  Found '%s': %d\n", key, val);
        } else {
            printf("  Key '%s' not found in map.\n", key);
        }
    }

    // 7. Check if a key exists
    printf("\nChecking existence:\n");
    if (ds_hashmap_contains_str_int(map, "Charlie")) {
        printf("  'Charlie' is in the map.\n");
    }

    // 8. Remove an element
    printf("\nRemoving 'Bob'...\n");
    ds_hashmap_remove_str_int(map, "Bob", NULL);
    printf("Map size after removal: %zu\n", ds_hashmap_size(map));

    // 9. Cleanup
    printf("\nDestroying map...\n");
    ds_hashmap_destroy(map);

    printf("--- Example Complete ---\n");
    return 0;
}
