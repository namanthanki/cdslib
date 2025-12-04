#include "hash_map.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_int_map()
{
    printf("Testing int map...\n");
    hash_map_t *map = create_hash_map(sizeof(int));
    assert(map != NULL);
    assert(hash_map_size(map) == 0);

    // Put
    int val = 100;
    assert(hash_map_put(map, "key1", &val) == HASH_MAP_SUCCESS);
    val = 200;
    assert(hash_map_put(map, "key2", &val) == HASH_MAP_SUCCESS);
    assert(hash_map_size(map) == 2);

    // Get
    int output;
    assert(hash_map_get(map, "key1", &output) == HASH_MAP_SUCCESS);
    assert(output == 100);
    assert(hash_map_get(map, "key2", &output) == HASH_MAP_SUCCESS);
    assert(output == 200);
    assert(hash_map_get(map, "key3", &output) == HASH_MAP_KEY_NOT_FOUND);

    // Update
    val = 300;
    assert(hash_map_put(map, "key1", &val) == HASH_MAP_SUCCESS);
    assert(hash_map_get(map, "key1", &output) == HASH_MAP_SUCCESS);
    assert(output == 300);

    // Remove
    assert(hash_map_remove(map, "key1", &output) == HASH_MAP_SUCCESS);
    assert(output == 300);
    assert(hash_map_size(map) == 1);
    assert(hash_map_get(map, "key1", &output) == HASH_MAP_KEY_NOT_FOUND);

    free_hash_map(map);
    printf("Int map passed.\n");
}

void test_string_map()
{
    printf("Testing string map (pointer storage)...\n");
    // Size 0 means we store the pointer itself, not copy the content
    hash_map_t *map = create_hash_map(0); 
    
    char *val1 = "value1";
    char *val2 = "value2";

    assert(hash_map_put(map, "k1", val1) == HASH_MAP_SUCCESS);
    assert(hash_map_put(map, "k2", val2) == HASH_MAP_SUCCESS);

    char *out;
    assert(hash_map_get(map, "k1", &out) == HASH_MAP_SUCCESS);
    assert(strcmp(out, "value1") == 0);
    // Ensure we got the exact same pointer back
    assert(out == val1);

    free_hash_map(map);
    printf("String map passed.\n");
}

int main()
{
    test_int_map();
    test_string_map();
    printf("All hash map tests passed!\n");
    return 0;
}
