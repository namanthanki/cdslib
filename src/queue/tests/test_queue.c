#include <stdio.h>
#include <string.h>
#include "queue.h"

void test_char_queue()
{
    printf("Testing char queue...\n");

    queue_t *queue = create_char_queue();
    if (!queue)
    {
        printf("Failed to create char queue\n");
        return;
    }

    char value = 'a';
    if (enqueue_char(queue, value) == QUEUE_SUCCESS)
    {
        printf("Enqueued %c onto char queue\n", value);
    }
    else
    {
        printf("Failed to enqueue %c onto char queue\n", value);
    }

    char output;
    if (peek_char(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Peeked %c from char queue\n", output);
    }
    else
    {
        printf("Failed to peek from char queue\n");
    }

    if (dequeue_char(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Dequeued %c from char queue\n", output);
    }
    else
    {
        printf("Failed to dequeue from char queue\n");
    }

    free_queue(queue);
    printf("Char queue test complete\n\n");
}

void test_int_queue()
{
    printf("Testing int queue...\n");

    queue_t *queue = create_int_queue();
    if (!queue)
    {
        printf("Failed to create int queue\n");
        return;
    }

    int value = 10;
    if (enqueue_int(queue, value) == QUEUE_SUCCESS)
    {
        printf("Enqueued %d onto int queue\n", value);
    }
    else
    {
        printf("Failed to enqueue %d onto int queue\n", value);
    }

    int output;
    if (peek_int(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Peeked %d from int queue\n", output);
    }
    else
    {
        printf("Failed to peek from int queue\n");
    }

    if (dequeue_int(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Dequeued %d from int queue\n", output);
    }
    else
    {
        printf("Failed to dequeue from int queue\n");
    }

    free_queue(queue);
    printf("Int queue test complete\n\n");
}

void test_float_queue()
{
    printf("Testing float queue...\n");

    queue_t *queue = create_float_queue();
    if (!queue)
    {
        printf("Failed to create float queue\n");
        return;
    }

    float value = 10.5f;
    if (enqueue_float(queue, value) == QUEUE_SUCCESS)
    {
        printf("Enqueued %f onto float queue\n", value);
    }
    else
    {
        printf("Failed to enqueue %f onto float queue\n", value);
    }

    float output;
    if (peek_float(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Peeked %f from float queue\n", output);
    }
    else
    {
        printf("Failed to peek from float queue\n");
    }

    if (dequeue_float(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Dequeued %f from float queue\n", output);
    }
    else
    {
        printf("Failed to dequeue from float queue\n");
    }

    free_queue(queue);
    printf("Float queue test complete\n\n");
}

void test_double_queue()
{
    printf("Testing double queue...\n");

    queue_t *queue = create_double_queue();
    if (!queue)
    {
        printf("Failed to create double queue\n");
        return;
    }

    double value = 10.5;
    if (enqueue_double(queue, value) == QUEUE_SUCCESS)
    {
        printf("Enqueued %f onto double queue\n", value);
    }
    else
    {
        printf("Failed to enqueue %f onto double queue\n", value);
    }

    double output;
    if (peek_double(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Peeked %f from double queue\n", output);
    }
    else
    {
        printf("Failed to peek from double queue\n");
    }

    if (dequeue_double(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Dequeued %f from double queue\n", output);
    }
    else
    {
        printf("Failed to dequeue from double queue\n");
    }

    free_queue(queue);
    printf("Double queue test complete\n\n");
}

void test_string_queue()
{
    printf("Testing string queue...\n");

    queue_t *queue = create_string_queue();
    if (!queue)
    {
        printf("Failed to create string queue\n");
        return;
    }

    char *value = "Hello, world!";
    if (enqueue_string(queue, value) == QUEUE_SUCCESS)
    {
        printf("Enqueued \"%s\" onto string queue\n", value);
    }
    else
    {
        printf("Failed to enqueue \"%s\" onto string queue\n", value);
    }

    char *output;
    if (peek_string(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Peeked \"%s\" from string queue\n", output);
    }
    else
    {
        printf("Failed to peek from string queue\n");
    }

    if (dequeue_string(queue, &output) == QUEUE_SUCCESS)
    {
        printf("Dequeued \"%s\" from string queue\n", output);
    }
    else
    {
        printf("Failed to dequeue from string queue\n");
    }

    free_string_queue(queue);
    printf("String queue test complete\n\n");
}

void test_string_queue_extended()
{
    printf("Extended testing of string queue...\n");

    queue_t *queue = create_string_queue();
    if (!queue)
    {
        printf("Failed to create string queue\n");
        return;
    }

    // Test peek and dequeue on empty queue
    char *output = NULL;
    if (peek_string(queue, &output) == QUEUE_UNDERFLOW)
    {
        printf("Correctly failed to peek from empty queue\n");
    }
    if (dequeue_string(queue, &output) == QUEUE_UNDERFLOW)
    {
        printf("Correctly failed to dequeue from empty queue\n");
    }

    // Enqueue multiple strings onto the queue
    const char *values[] = {"Hello", "world", "from", "the", "queue"};
    for (int i = 0; i < 5; i++)
    {
        if (enqueue_string(queue, values[i]) == QUEUE_SUCCESS)
        {
            printf("Enqueued \"%s\" onto string queue\n", values[i]);
        }
        else
        {
            printf("Failed to enqueue \"%s\" onto string queue\n", values[i]);
        }
    }

    // Peek and dequeue each string from the queue
    for (int i = 0; i < 5; i++)
    {
        if (peek_string(queue, &output) == QUEUE_SUCCESS)
        {
            printf("Peeked \"%s\" from string queue\n", output);
        }
        if (dequeue_string(queue, &output) == QUEUE_SUCCESS)
        {
            printf("Dequeued \"%s\" from string queue\n", output);
            free(output);
        }
    }

    free_string_queue(queue);
    printf("Extended string queue test complete\n\n");
}

int main()
{
    test_char_queue();
    test_int_queue();
    test_float_queue();
    test_double_queue();
    test_string_queue();
    test_string_queue_extended();

    return 0;
}