#include "ds/ds_stack.h"
#include "ds/ds_queue.h"
#include <stdio.h>
#include <stdlib.h>

// Generate type-safe inline wrappers for int
DS_STACK_DEFINE_TYPE(int, int)
DS_QUEUE_DEFINE_TYPE(int, int)

int main() {
    printf("--- Stack and Queue Example ---\n");

    // 1. Create the stack and queue
    ds_stack_t *stack = ds_stack_create(sizeof(int), NULL, NULL, NULL);
    ds_queue_t *queue = ds_queue_create(sizeof(int), NULL, NULL, NULL);

    if (!stack || !queue) {
        fprintf(stderr, "Failed to create stack or queue\n");
        return 1;
    }

    // 2. Push elements to the stack
    printf("Pushing to stack: 10, 20, 30\n");
    ds_stack_push_int(stack, 10);
    ds_stack_push_int(stack, 20);
    ds_stack_push_int(stack, 30);

    printf("Stack size: %zu\n", ds_stack_size(stack));

    // 3. Pop elements from the stack (LIFO)
    printf("\nPopping from stack (LIFO):\n");
    int popped_val;
    while (ds_stack_pop_int(stack, &popped_val) == DS_SUCCESS) {
        printf("  Popped: %d\n", popped_val);
    }

    // 4. Enqueue elements to the queue
    printf("\nEnqueueing to queue: 100, 200, 300\n");
    ds_queue_enqueue_int(queue, 100);
    ds_queue_enqueue_int(queue, 200);
    ds_queue_enqueue_int(queue, 300);

    printf("Queue size: %zu\n", ds_queue_size(queue));

    // 5. Dequeue elements from the queue (FIFO)
    printf("\nDequeueing from queue (FIFO):\n");
    int dequeued_val;
    while (ds_queue_dequeue_int(queue, &dequeued_val) == DS_SUCCESS) {
        printf("  Dequeued: %d\n", dequeued_val);
    }

    // 6. Cleanup
    printf("\nDestroying stack and queue...\n");
    ds_stack_destroy(stack);
    ds_queue_destroy(queue);

    printf("--- Example Complete ---\n");
    return 0;
}
