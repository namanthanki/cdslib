#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_int_vector()
{
    printf("Testing int vector...\n");
    vector_t *vec = create_int_vector();
    assert(vec != NULL);
    assert(vector_size(vec) == 0);
    assert(vector_is_empty(vec));

    // Push back
    for (int i = 0; i < 20; i++)
    {
        push_back_int(vec, i);
    }
    assert(vector_size(vec) == 20);
    assert(!vector_is_empty(vec));

    int val;
    get_int(vec, 0, &val);
    assert(val == 0);
    get_int(vec, 19, &val);
    assert(val == 19);

    // Pop back
    pop_back_int(vec, &val);
    assert(val == 19);
    assert(vector_size(vec) == 19);

    // Insert
    insert_int(vec, 5, 999);
    get_int(vec, 5, &val);
    assert(val == 999);
    assert(vector_size(vec) == 20);

    // Remove
    remove_int(vec, 5, &val);
    assert(val == 999);
    assert(vector_size(vec) == 19);
    get_int(vec, 5, &val);
    assert(val == 5); // Should be back to original

    free_int_vector(vec);
    printf("Int vector passed.\n");
}

void test_string_vector()
{
    printf("Testing string vector...\n");
    vector_t *vec = create_string_vector();
    
    push_back_string(vec, "Hello");
    push_back_string(vec, "World");
    
    assert(vector_size(vec) == 2);
    
    char *str;
    get_string(vec, 0, &str);
    assert(strcmp(str, "Hello") == 0);
    
    get_string(vec, 1, &str);
    assert(strcmp(str, "World") == 0);
    
    pop_back_string(vec, &str);
    assert(strcmp(str, "World") == 0);
    free(str); // User is responsible for freeing output of pop
    
    assert(vector_size(vec) == 1);
    
    free_string_vector(vec);
    printf("String vector passed.\n");
}

int main()
{
    test_int_vector();
    test_string_vector();
    printf("All vector tests passed!\n");
    return 0;
}
