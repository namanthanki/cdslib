#include "hash_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_BUCKETS 16
#define LOAD_FACTOR 0.75

// DJB2 hash function
static unsigned long hash_function(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

hash_map_t *create_hash_map(size_t element_size)
{
    hash_map_t *map = malloc(sizeof(hash_map_t));
    if (!map) return NULL;

    map->buckets = calloc(INITIAL_BUCKETS, sizeof(hash_map_entry_t *));
    if (!map->buckets)
    {
        free(map);
        return NULL;
    }

    map->bucket_count = INITIAL_BUCKETS;
    map->size = 0;
    map->element_size = element_size;

    return map;
}

static hash_map_error_t resize_map(hash_map_t *map)
{
    size_t new_count = map->bucket_count * 2;
    hash_map_entry_t **new_buckets = calloc(new_count, sizeof(hash_map_entry_t *));
    if (!new_buckets) return HASH_MAP_MEMORY_ERROR;

    for (size_t i = 0; i < map->bucket_count; i++)
    {
        hash_map_entry_t *entry = map->buckets[i];
        while (entry)
        {
            hash_map_entry_t *next = entry->next;
            
            // Rehash
            unsigned long hash = hash_function(entry->key);
            size_t index = hash % new_count;

            entry->next = new_buckets[index];
            new_buckets[index] = entry;

            entry = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->bucket_count = new_count;

    return HASH_MAP_SUCCESS;
}

hash_map_error_t hash_map_put(hash_map_t *map, const char *key, void *value)
{
    if (!map || !key) return HASH_MAP_NULL_KEY;

    if ((float)map->size / map->bucket_count >= LOAD_FACTOR)
    {
        if (resize_map(map) != HASH_MAP_SUCCESS)
        {
            return HASH_MAP_MEMORY_ERROR;
        }
    }

    unsigned long hash = hash_function(key);
    size_t index = hash % map->bucket_count;

    hash_map_entry_t *entry = map->buckets[index];
    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            // Update existing
            if (map->element_size > 0)
            {
                memcpy(entry->value, value, map->element_size);
            }
            else
            {
                entry->value = value;
            }
            return HASH_MAP_SUCCESS;
        }
        entry = entry->next;
    }

    // New entry
    hash_map_entry_t *new_entry = malloc(sizeof(hash_map_entry_t));
    if (!new_entry) return HASH_MAP_MEMORY_ERROR;

    new_entry->key = strdup(key);
    if (!new_entry->key)
    {
        free(new_entry);
        return HASH_MAP_MEMORY_ERROR;
    }

    if (map->element_size > 0)
    {
        new_entry->value = malloc(map->element_size);
        if (!new_entry->value)
        {
            free(new_entry->key);
            free(new_entry);
            return HASH_MAP_MEMORY_ERROR;
        }
        memcpy(new_entry->value, value, map->element_size);
    }
    else
    {
        new_entry->value = value;
    }

    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->size++;

    return HASH_MAP_SUCCESS;
}

hash_map_error_t hash_map_get(hash_map_t *map, const char *key, void *output)
{
    if (!map || !key) return HASH_MAP_NULL_KEY;

    unsigned long hash = hash_function(key);
    size_t index = hash % map->bucket_count;

    hash_map_entry_t *entry = map->buckets[index];
    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            if (output)
            {
                if (map->element_size > 0)
                {
                    memcpy(output, entry->value, map->element_size);
                }
                else
                {
                    *(void **)output = entry->value;
                }
            }
            return HASH_MAP_SUCCESS;
        }
        entry = entry->next;
    }

    return HASH_MAP_KEY_NOT_FOUND;
}

hash_map_error_t hash_map_remove(hash_map_t *map, const char *key, void *output)
{
    if (!map || !key) return HASH_MAP_NULL_KEY;

    unsigned long hash = hash_function(key);
    size_t index = hash % map->bucket_count;

    hash_map_entry_t *entry = map->buckets[index];
    hash_map_entry_t *prev = NULL;

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            if (prev)
            {
                prev->next = entry->next;
            }
            else
            {
                map->buckets[index] = entry->next;
            }

            if (output)
            {
                if (map->element_size > 0)
                {
                    memcpy(output, entry->value, map->element_size);
                }
                else
                {
                    *(void **)output = entry->value;
                }
            }

            free(entry->key);
            if (map->element_size > 0)
            {
                free(entry->value);
            }
            free(entry);
            map->size--;
            return HASH_MAP_SUCCESS;
        }
        prev = entry;
        entry = entry->next;
    }

    return HASH_MAP_KEY_NOT_FOUND;
}

int hash_map_contains(hash_map_t *map, const char *key)
{
    return hash_map_get(map, key, NULL) == HASH_MAP_SUCCESS;
}

size_t hash_map_size(hash_map_t *map)
{
    return map ? map->size : 0;
}

void free_hash_map(hash_map_t *map)
{
    if (!map) return;

    for (size_t i = 0; i < map->bucket_count; i++)
    {
        hash_map_entry_t *entry = map->buckets[i];
        while (entry)
        {
            hash_map_entry_t *next = entry->next;
            free(entry->key);
            if (map->element_size > 0)
            {
                free(entry->value);
            }
            free(entry);
            entry = next;
        }
    }

    free(map->buckets);
    free(map);
}
