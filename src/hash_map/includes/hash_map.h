#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>

typedef enum
{
    HASH_MAP_SUCCESS,
    HASH_MAP_MEMORY_ERROR,
    HASH_MAP_KEY_NOT_FOUND,
    HASH_MAP_NULL_KEY
} hash_map_error_t;

typedef struct hash_map_entry
{
    char *key;
    void *value;
    struct hash_map_entry *next; // For separate chaining
} hash_map_entry_t;

typedef struct
{
    hash_map_entry_t **buckets;
    size_t bucket_count;
    size_t size;
    size_t element_size; // Size of the value, for copying if needed, or just 0 if storing pointers
} hash_map_t;

// Create a hash map. If element_size > 0, values are copied. If 0, pointer is stored.
hash_map_t *create_hash_map(size_t element_size);

hash_map_error_t hash_map_put(hash_map_t *map, const char *key, void *value);
hash_map_error_t hash_map_get(hash_map_t *map, const char *key, void *output);
hash_map_error_t hash_map_remove(hash_map_t *map, const char *key, void *output);
int hash_map_contains(hash_map_t *map, const char *key);
size_t hash_map_size(hash_map_t *map);
void free_hash_map(hash_map_t *map);

// Macro for type-safe wrappers could be added here similar to vector/list
// For now, we'll stick to the core generic implementation for simplicity as per plan.

#endif // HASH_MAP_H
