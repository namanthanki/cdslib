# cdslib - Data Structures & Algorithms Library

A clean, modular, opaque, namespaced, memory-safe, and production-grade Data Structures and Algorithms library written in C. 

This library provides a generic `void*` core with type-safe macro wrappers, ensuring high performance and flexibility without sacrificing type safety or encapsulation.

## Features

* **Opaque Types**: Complete encapsulation. Internal struct details are hidden from the public API.
* **Unified Namespace**: All symbols and functions are prefixed with `ds_` to prevent global namespace pollution.
* **Memory-Safe & Extensible**: Every structure supports custom allocators (`malloc`/`free` overrides) and optional element destructors for automatic memory management of complex types.
* **Type-Safe Macro Wrappers**: Generate inline, type-safe wrappers for any data type without duplicating core logic or polluting the symbol table.
* **Production-Grade**: Built with strict compiler flags (`-Wall -Wextra -Werror -pedantic -std=c99`), memory sanitizers, and comprehensive test coverage.

## Included Components

### Data Structures
* **Vector** (`ds_vector`): Dynamic array with automatic resizing.
* **Array** (`ds_array`): Static, fixed-capacity array.
* **Stack** (`ds_stack`): LIFO data structure (wraps Vector).
* **Queue** (`ds_queue`): FIFO data structure (implemented as a high-performance circular buffer).
* **Linked List** (`ds_list`): Doubly linked list with iterator support.
* **Hash Map** (`ds_hashmap`): Separate chaining hash map with custom hash/compare functions and automatic rehashing.
* **Tree** (`ds_tree`): Binary Search Tree with in-order, pre-order, and post-order traversals.

### Algorithms (`ds_algo`)
* Quicksort
* Mergesort
* Binary Search
* Heapify

## Getting Started

### Prerequisites
* GCC or Clang
* Make (GNU Make or mingw32-make on Windows)

### Building the Library

Build the static library (`libds.a`):
```bash
make
```

Build and run the test suite:
```bash
make test
```

Build and run the examples:
```bash
make examples
```

Build with debug symbols and sanitizers:
```bash
make debug
```

Build for release (optimized):
```bash
make release
```

Clean build artifacts:
```bash
make clean
```

## Examples

The `examples/` directory contains complete, runnable examples for each data structure. You can build and run them all using `make examples`.

- `example_vector.c`: Demonstrates dynamic arrays with custom destructors.
- `example_list.c`: Shows doubly linked list operations and iteration.
- `example_hashmap.c`: Illustrates key-value storage with custom hash and comparison functions.
- `example_tree.c`: Covers binary search tree insertion, removal, and traversals.
- `example_stack_queue.c`: Demonstrates LIFO and FIFO data structures.

## Usage Example

Here is a quick example of how to use the Vector structure with type-safe macros:

```c
#include "ds/ds_vector.h"
#include <stdio.h>

// Generate type-safe inline wrappers for 'int'
DS_VECTOR_DEFINE_TYPE(int, int)

int main() {
    // Create a vector of integers. 
    // NULLs indicate default malloc/free and no element destructor.
    ds_vector_t *vec = ds_vector_create(sizeof(int), NULL, NULL, NULL);

    // Use the generated type-safe push function
    ds_vector_push_back_int(vec, 42);
    ds_vector_push_back_int(vec, 100);

    // Retrieve values safely
    int val;
    ds_vector_get_int(vec, 0, &val);
    printf("First element: %d\n", val); // Outputs 42

    // Cleanup
    ds_vector_destroy(vec);
    return 0;
}
```

## Memory Management

Every data structure allows you to pass a custom `destructor` function upon creation. If provided, the library will automatically call this destructor on elements when they are removed, popped, or when the structure itself is destroyed or cleared.

## Thread Safety

**Note:** This library is **not thread-safe**. Like the C++ STL, it does not use internal mutexes or atomic operations. If you intend to use these data structures across multiple threads, you must provide your own external synchronization (e.g., wrapping operations in `pthread_mutex_lock` / `pthread_mutex_unlock`).

```c
void my_string_destructor(void *elem) {
    char **str = (char **)elem;
    free(*str);
}

// The vector will now automatically free() strings when they are removed
ds_vector_t *vec = ds_vector_create(sizeof(char*), my_string_destructor, NULL, NULL);
```

## License

This project is open-source and available under the MIT License.
