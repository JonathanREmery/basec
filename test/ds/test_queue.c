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
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);
    assert(queue_valid->element_size == sizeof(int));
    assert(queue_valid->capacity == 10);
    assert(queue_valid->size == 0);
    assert(queue_valid->data != NULL);
    assert(queue_valid->head == queue_valid->data);
    assert(queue_valid->tail == queue_valid->data);

    // Test invalid element size
    Queue* queue_invalid_elem_size = NULL;
    QueueResult result_create_invalid_elem_size = queue_create(0, 10, &queue_invalid_elem_size);
    assert(result_create_invalid_elem_size == QUEUE_ERROR_INVALID_ELEMENT_SIZE);
    assert(queue_invalid_elem_size == NULL);

    // Test invalid capacity
    Queue* queue_invalid_capacity = NULL;
    QueueResult result_create_invalid_capacity = queue_create(sizeof(int), 0, &queue_invalid_capacity);
    assert(result_create_invalid_capacity == QUEUE_ERROR_INVALID_CAPACITY);
    assert(queue_invalid_capacity == NULL);

    // Test NULL pointer
    QueueResult result_create_null_pointer = queue_create(sizeof(int), 10, NULL);
    assert(result_create_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test minimum capacity
    Queue* queue_min = NULL;
    QueueResult result_create_min = queue_create(sizeof(int), 1, &queue_min);
    assert(result_create_min == QUEUE_SUCCESS);
    assert(queue_min->capacity == 1);
    queue_destroy(&queue_min);

    // Test large capacity
    Queue* queue_large = NULL;
    QueueResult result_create_large = queue_create(sizeof(int), 1000, &queue_large);
    assert(result_create_large == QUEUE_SUCCESS);
    assert(queue_large->capacity == 1000);
    queue_destroy(&queue_large);
}

/**
 * @brief Test the queue_resize function
 * 
 * @return void
 */
void test_queue_resize() {
    printf("  Testing queue_resize...\n");

    // Create a queue manually
    Queue* queue_valid = malloc(sizeof(Queue));
    queue_valid->element_size = sizeof(int);
    queue_valid->capacity = 10;
    queue_valid->size = 0;
    queue_valid->data = malloc(sizeof(int) * 10);
    queue_valid->base = queue_valid->data;
    queue_valid->head = queue_valid->data;
    queue_valid->tail = queue_valid->data;

    // Test invalid capacity
    QueueResult result_resize_invalid_capacity = queue_resize(queue_valid, 0);
    assert(result_resize_invalid_capacity == QUEUE_ERROR_INVALID_CAPACITY);
    assert(queue_valid->capacity == 10);

    // Test NULL pointer
    QueueResult result_resize_null_pointer = queue_resize(NULL, 10);
    assert(result_resize_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test resizing to a smaller capacity
    QueueResult result_resize_smaller_capacity = queue_resize(queue_valid, 5);
    assert(result_resize_smaller_capacity == QUEUE_SUCCESS);
    assert(queue_valid->capacity == 5);

    // Test resizing to a larger capacity
    QueueResult result_resize_larger_capacity = queue_resize(queue_valid, 15);
    assert(result_resize_larger_capacity == QUEUE_SUCCESS);
    assert(queue_valid->capacity == 15);

    // Test resizing to the same capacity
    QueueResult result_resize_same_capacity = queue_resize(queue_valid, 5);
    assert(result_resize_same_capacity == QUEUE_SUCCESS);
    assert(queue_valid->capacity == 5);

    // Manual cleanup
    free(queue_valid->data);
    free(queue_valid);
}

/**
 * @brief Test the queue_size function
 * 
 * @return void
 */
void test_queue_size() {
    printf("  Testing queue_size...\n");

    // Create a queue manually
    Queue* queue_valid = malloc(sizeof(Queue));
    queue_valid->size = 0;
    queue_valid->capacity = 10;
    queue_valid->element_size = sizeof(int);
    queue_valid->data = malloc(sizeof(int) * 10);
    queue_valid->base = queue_valid->data;
    queue_valid->head = queue_valid->data;
    queue_valid->tail = queue_valid->data;

    // Test the size
    size_t size;
    QueueResult result_size = queue_size(queue_valid, &size);
    assert(result_size == QUEUE_SUCCESS);
    assert(size == 0);

    // Test NULL pointer
    QueueResult result_size_null_pointer = queue_size(NULL, &size);
    assert(result_size_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL pointer for size_out
    QueueResult result_size_null_pointer_size_out = queue_size(queue_valid, NULL);
    assert(result_size_null_pointer_size_out == QUEUE_ERROR_NULL_POINTER);

    // Manual cleanup
    free(queue_valid->data);
    free(queue_valid);
}

/**
 * @brief Test the queue_capacity function
 * 
 * @return void
 */
void test_queue_capacity() {
    printf("  Testing queue_capacity...\n");

    // Create a queue manually
    Queue* queue_valid = malloc(sizeof(Queue));
    queue_valid->capacity = 10;
    queue_valid->size = 0;
    queue_valid->element_size = sizeof(int);
    queue_valid->data = malloc(sizeof(int) * 10);
    queue_valid->base = queue_valid->data;
    queue_valid->head = queue_valid->data;
    queue_valid->tail = queue_valid->data;

    // Test the capacity
    size_t capacity;
    QueueResult result_capacity = queue_capacity(queue_valid, &capacity);
    assert(result_capacity == QUEUE_SUCCESS);
    assert(capacity == 10);

    // Test NULL pointer
    QueueResult result_capacity_null_pointer = queue_capacity(NULL, &capacity);
    assert(result_capacity_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL pointer for capacity_out
    QueueResult result_capacity_null_pointer_capacity_out = queue_capacity(queue_valid, NULL);
    assert(result_capacity_null_pointer_capacity_out == QUEUE_ERROR_NULL_POINTER);

    // Manual cleanup
    free(queue_valid->data);
    free(queue_valid);
}

/**
 * @brief Test the queue_enqueue function
 * 
 * @return void
 */
void test_queue_enqueue() {
    printf("  Testing queue_enqueue...\n");

    // Create a queue manually
    Queue* queue_valid = malloc(sizeof(Queue));
    queue_valid->element_size = sizeof(int);
    queue_valid->capacity = 3;
    queue_valid->size = 0;
    queue_valid->data = malloc(sizeof(int) * 3);
    queue_valid->base = queue_valid->data;
    queue_valid->head = queue_valid->data;
    queue_valid->tail = queue_valid->data;

    // Test NULL pointer
    int element = 1;
    QueueResult result_enqueue_null_pointer = queue_enqueue(NULL, &element);
    assert(result_enqueue_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL element
    QueueResult result_enqueue_null_element = queue_enqueue(queue_valid, NULL);
    assert(result_enqueue_null_element == QUEUE_ERROR_NULL_POINTER);

    // Test enqueueing elements
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) {
        QueueResult result_enqueue = queue_enqueue(queue_valid, &values[i]);
        assert(result_enqueue == QUEUE_SUCCESS);
        assert(queue_valid->size == (size_t)(i + 1));
    }

    // Test enqueue with resize
    int extra = 40;
    QueueResult result_enqueue_full = queue_enqueue(queue_valid, &extra);
    assert(result_enqueue_full == QUEUE_SUCCESS);
    assert(queue_valid->size == 4);
    assert(queue_valid->capacity == 6);

    // Manual cleanup
    free(queue_valid->data);
    free(queue_valid);
}

/**
 * @brief Test the queue_dequeue function
 * 
 * @return void
 */
void test_queue_dequeue() {
    printf("  Testing queue_dequeue...\n");

    // Create a queue manually with one element
    Queue* queue_valid = malloc(sizeof(Queue));
    queue_valid->element_size = sizeof(int);
    queue_valid->capacity = 3;
    queue_valid->size = 1;
    queue_valid->data = malloc(sizeof(int) * 3);
    int initial_value = 10;
    memcpy(queue_valid->data, &initial_value, sizeof(int));
    queue_valid->base = queue_valid->data;
    queue_valid->head = queue_valid->data;
    queue_valid->tail = queue_valid->data + sizeof(int);

    // Test NULL pointer
    int element;
    QueueResult result_dequeue_null_pointer = queue_dequeue(NULL, &element);
    assert(result_dequeue_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL element_out
    QueueResult result_dequeue_null_pointer_element_out = queue_dequeue(queue_valid, NULL);
    assert(result_dequeue_null_pointer_element_out == QUEUE_ERROR_NULL_POINTER);

    // Test dequeuing single element
    QueueResult result_dequeue = queue_dequeue(queue_valid, &element);
    assert(result_dequeue == QUEUE_SUCCESS);
    assert(element == 10);
    assert(queue_valid->size == 0);

    // Test dequeue from empty queue
    QueueResult result_dequeue_empty = queue_dequeue(queue_valid, &element);
    assert(result_dequeue_empty == QUEUE_ERROR_EMPTY);

    // Manual cleanup
    free(queue_valid->data);
    free(queue_valid);
}

/**
 * @brief Test the queue_destroy function
 * 
 * @return void
 */
void test_queue_destroy() {
    printf("  Testing queue_destroy...\n");

    // Create a queue manually
    Queue* queue_valid = malloc(sizeof(Queue));
    queue_valid->data = malloc(sizeof(int) * 10);
    queue_valid->element_size = sizeof(int);
    queue_valid->capacity = 10;
    queue_valid->size = 0;
    queue_valid->base = queue_valid->data;
    queue_valid->head = queue_valid->data;
    queue_valid->tail = queue_valid->data;

    // Test destroying the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);

    // Test destroying NULL pointer
    QueueResult result_destroy_null = queue_destroy(NULL);
    assert(result_destroy_null == QUEUE_ERROR_NULL_POINTER);

    // Test destroying already destroyed queue
    QueueResult result_destroy_again = queue_destroy(&queue_valid);
    assert(result_destroy_again == QUEUE_ERROR_NULL_POINTER);
}

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
