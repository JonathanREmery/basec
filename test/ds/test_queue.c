/**
 * @file test_queue.c
 * @brief Test the queue implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "ds/basec_queue.h"

/**
 * @brief Test the queue_create function
 * 
 * @return void
 */
void test_queue_create() {
    printf("  Testing queue_create...\n");

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);

    // Check the queue properties
    printf("    Testing valid queue...\n");
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);
    assert(queue_valid->element_size == sizeof(int));
    assert(queue_valid->capacity == 10);
    assert(queue_valid->size == 0);
    assert(queue_valid->data != NULL);
    assert(queue_valid->head == queue_valid->data);
    assert(queue_valid->tail == queue_valid->data);

    // Test invalid element size
    printf("    Testing invalid element size...\n");
    Queue* queue_invalid_elem_size = NULL;
    QueueResult result_create_invalid_elem_size = queue_create(
        0,
        10,
        &queue_invalid_elem_size
    );
    assert(result_create_invalid_elem_size == QUEUE_ERROR_INVALID_ELEMENT_SIZE);
    assert(queue_invalid_elem_size == NULL);

    // Test invalid capacity
    printf("    Testing invalid capacity...\n");
    Queue* queue_invalid_capacity = NULL;
    QueueResult result_create_invalid_capacity = queue_create(
        sizeof(int),
        0,
        &queue_invalid_capacity
    );
    assert(result_create_invalid_capacity == QUEUE_ERROR_INVALID_CAPACITY);
    assert(queue_invalid_capacity == NULL);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    QueueResult result_create_null_pointer = queue_create(
        sizeof(int),
        10,
        NULL
    );
    assert(result_create_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test minimum capacity
    printf("    Testing minimum capacity...\n");
    Queue* queue_min = NULL;
    QueueResult result_create_min = queue_create(sizeof(int), 1, &queue_min);
    assert(result_create_min == QUEUE_SUCCESS);
    assert(queue_min->capacity == 1);

    // Test large capacity
    printf("    Testing large capacity...\n");
    Queue* queue_large = NULL;
    QueueResult result_create_large = queue_create(sizeof(int), 1000, &queue_large);
    assert(result_create_large == QUEUE_SUCCESS);
    assert(queue_large->capacity == 1000);

    // Manual cleanup
    free(queue_valid->data);
    free(queue_valid);
    free(queue_min->data);
    free(queue_min);
    free(queue_large->data);
    free(queue_large);
}

/**
 * @brief Test the queue_resize function
 * 
 * @return void
 */
void test_queue_resize() {
    printf("  Testing queue_resize...\n");

    // Create a queue manually
    Queue* queue = malloc(sizeof(Queue));
    queue->element_size = sizeof(int);
    queue->capacity = 10;
    queue->size = 0;
    queue->data = malloc(sizeof(int) * 10);
    queue->head = queue->data;
    queue->tail = queue->data;

    // Test invalid capacity
    printf("    Testing invalid capacity...\n");
    QueueResult result_resize_invalid_capacity = queue_resize(queue, 0);
    assert(result_resize_invalid_capacity == QUEUE_ERROR_INVALID_CAPACITY);
    assert(queue->capacity == 10);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    QueueResult result_resize_null_pointer = queue_resize(NULL, 10);
    assert(result_resize_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test resizing to a smaller capacity
    printf("    Testing resizing to a smaller capacity...\n");
    QueueResult result_resize_smaller_capacity = queue_resize(queue, 5);
    assert(result_resize_smaller_capacity == QUEUE_SUCCESS);
    assert(queue->capacity == 5);

    // Test resizing to a larger capacity
    printf("    Testing resizing to a larger capacity...\n");
    QueueResult result_resize_larger_capacity = queue_resize(queue, 15);
    assert(result_resize_larger_capacity == QUEUE_SUCCESS);
    assert(queue->capacity == 15);

    // Test resizing to the same capacity
    printf("    Testing resizing to the same capacity...\n");
    QueueResult result_resize_same_capacity = queue_resize(queue, 5);
    assert(result_resize_same_capacity == QUEUE_SUCCESS);
    assert(queue->capacity == 5);

    // Manual cleanup
    free(queue->data);
    free(queue);
}

/**
 * @brief Test the queue_size function
 * 
 * @return void
 */
void test_queue_size() {
    printf("  Testing queue_size...\n");

    // Create a queue manually
    Queue* queue = malloc(sizeof(Queue));
    queue->size = 0;
    queue->capacity = 10;
    queue->element_size = sizeof(int);
    queue->data = malloc(sizeof(int) * 10);
    queue->head = queue->data;
    queue->tail = queue->data;

    // Test the size
    printf("    Testing size...\n");
    size_t size;
    QueueResult result_size = queue_size(queue, &size);
    assert(result_size == QUEUE_SUCCESS);
    assert(size == 0);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    QueueResult result_size_null_pointer = queue_size(NULL, &size);
    assert(result_size_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL pointer for size_out
    printf("    Testing NULL pointer for size_out...\n");
    QueueResult result_size_null_pointer_size_out = queue_size(queue, NULL);
    assert(result_size_null_pointer_size_out == QUEUE_ERROR_NULL_POINTER);

    // Manual cleanup
    free(queue->data);
    free(queue);
}

/**
 * @brief Test the queue_capacity function
 * 
 * @return void
 */
void test_queue_capacity() {
    printf("  Testing queue_capacity...\n");

    // Create a queue manually
    Queue* queue = malloc(sizeof(Queue));
    queue->capacity = 10;
    queue->size = 0;
    queue->element_size = sizeof(int);
    queue->data = malloc(sizeof(int) * 10);
    queue->head = queue->data;
    queue->tail = queue->data;

    // Test the capacity
    printf("    Testing capacity...\n");
    size_t capacity;
    QueueResult result_capacity = queue_capacity(queue, &capacity);
    assert(result_capacity == QUEUE_SUCCESS);
    assert(capacity == 10);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    QueueResult result_capacity_null_pointer = queue_capacity(NULL, &capacity);
    assert(result_capacity_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL pointer for capacity_out
    printf("    Testing NULL pointer for capacity_out...\n");
    QueueResult result_capacity_null_pointer_capacity_out = queue_capacity(
        queue,
        NULL
    );
    assert(
        result_capacity_null_pointer_capacity_out == QUEUE_ERROR_NULL_POINTER
    );

    // Manual cleanup
    free(queue->data);
    free(queue);
}

/**
 * @brief Test the queue_enqueue function
 * 
 * @return void
 */
void test_queue_enqueue() {
    printf("  Testing queue_enqueue...\n");

    // Create a queue manually
    Queue* queue = malloc(sizeof(Queue));
    queue->element_size = sizeof(int);
    queue->capacity = 3;
    queue->size = 0;
    queue->data = malloc(sizeof(int) * 3);
    queue->head = queue->data;
    queue->tail = queue->data;

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    int element = 1;
    QueueResult result_enqueue_null_pointer = queue_enqueue(NULL, &element);
    assert(result_enqueue_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL element
    printf("    Testing NULL element...\n");
    QueueResult result_enqueue_null_element = queue_enqueue(queue, NULL);
    assert(result_enqueue_null_element == QUEUE_ERROR_NULL_POINTER);

    // Test enqueueing elements
    printf("    Testing enqueueing elements...\n");
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        QueueResult result_enqueue = queue_enqueue(queue, &values[i]);
        assert(result_enqueue == QUEUE_SUCCESS);
        assert(queue->size == (size_t)(i + 1));
    }

    // Test enqueue with resize
    printf("    Testing enqueue with resize...\n");
    int extra = 40;
    QueueResult result_enqueue_full = queue_enqueue(queue, &extra);
    assert(result_enqueue_full == QUEUE_SUCCESS);
    assert(queue->size == 4);
    assert(queue->capacity == 6);

    // Manual cleanup
    free(queue->data);
    free(queue);
}

/**
 * @brief Test the queue_dequeue function
 * 
 * @return void
 */
void test_queue_dequeue() {
    printf("  Testing queue_dequeue...\n");

    // Create a queue manually with one element
    Queue* queue = malloc(sizeof(Queue));
    queue->element_size = sizeof(int);
    queue->capacity = 3;
    queue->size = 1;
    queue->data = malloc(sizeof(int) * 3);
    int initial_value = 10;
    memcpy(queue->data, &initial_value, sizeof(int));
    queue->head = queue->data;
    queue->tail = queue->data + sizeof(int);

    // Test NULL pointer
    printf("    Testing NULL pointer...\n");
    int element;
    QueueResult result_dequeue_null_pointer = queue_dequeue(NULL, &element);
    assert(result_dequeue_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL element_out
    printf("    Testing NULL element_out...\n");
    QueueResult result_dequeue_null_pointer_element_out = queue_dequeue(
        queue,
        NULL
    );
    assert(result_dequeue_null_pointer_element_out == QUEUE_ERROR_NULL_POINTER);

    // Test dequeuing single element
    printf("    Testing dequeuing single element...\n");
    QueueResult result_dequeue = queue_dequeue(queue, &element);
    assert(result_dequeue == QUEUE_SUCCESS);
    assert(element == 10);
    assert(queue->size == 0);

    // Test dequeue from empty queue
    printf("    Testing dequeue from empty queue...\n");
    QueueResult result_dequeue_empty = queue_dequeue(queue, &element);
    assert(result_dequeue_empty == QUEUE_ERROR_EMPTY);

    // Manual cleanup
    free(queue->data);
    free(queue);
}

/**
 * @brief Test the queue_destroy function
 * 
 * @return void
 */
void test_queue_destroy() {
    printf("  Testing queue_destroy...\n");

    // Create a queue manually
    Queue* queue = malloc(sizeof(Queue));
    queue->data = malloc(sizeof(int) * 10);
    queue->element_size = sizeof(int);
    queue->capacity = 10;
    queue->size = 0;
    queue->head = queue->data;
    queue->tail = queue->data;

    // Test destroying the queue
    printf("    Testing destroying the queue...\n");
    QueueResult result_destroy = queue_destroy(&queue);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue == NULL);

    // Test destroying NULL pointer
    printf("    Testing destroying NULL pointer...\n");
    QueueResult result_destroy_null = queue_destroy(NULL);
    assert(result_destroy_null == QUEUE_ERROR_NULL_POINTER);

    // Test destroying already destroyed queue
    printf("    Testing destroying already destroyed queue...\n");
    QueueResult result_destroy_again = queue_destroy(&queue);
    assert(result_destroy_again == QUEUE_ERROR_NULL_POINTER);
}

/**
 * @brief Test the queue implementation
 * 
 * @return int
 */
int main() {
    printf("[basec_queue] Running tests...\n");

    // Run tests
    test_queue_create();
    test_queue_resize();
    test_queue_size();
    test_queue_capacity();
    test_queue_enqueue();
    test_queue_dequeue();
    test_queue_destroy();

    printf("[basec_queue] All tests passed!\n");

    return 0;
}
