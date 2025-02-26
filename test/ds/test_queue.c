/**
 * @file test_queue.c
 * @brief Test the queue implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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
}

/**
 * @brief Test the queue_resize function
 * 
 * @return void
 */
void test_queue_resize() {
    printf("  Testing queue_resize...\n");

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);

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
    assert(queue_valid->size == 0);
    assert(queue_valid->head == queue_valid->data);
    assert(queue_valid->tail == queue_valid->data);

    // Test resizing to a larger capacity
    QueueResult result_resize_larger_capacity = queue_resize(queue_valid, 15);
    assert(result_resize_larger_capacity == QUEUE_SUCCESS);
    assert(queue_valid->capacity == 15);

    // Test resizing to the same capacity
    QueueResult result_resize_same_capacity = queue_resize(queue_valid, 5);
    assert(result_resize_same_capacity == QUEUE_SUCCESS);
    assert(queue_valid->capacity == 5);
    assert(queue_valid->size == 0);
    assert(queue_valid->head == queue_valid->data);
    assert(queue_valid->tail == queue_valid->data);

    // Destroy the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);
}

/**
 * @brief Test the queue_size function
 * 
 * @return void
 */
void test_queue_size() {
    printf("  Testing queue_size...\n");

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);

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

    // Destroy the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);
}

/**
 * @brief Test the queue_capacity function
 * 
 * @return void
 */
void test_queue_capacity() {
    printf("  Testing queue_capacity...\n");

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);

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

    // Destroy the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);
}

/**
 * @brief Test the queue_enqueue function
 * 
 * @return void
 */
void test_queue_enqueue() {
    printf("  Testing queue_enqueue...\n");

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);

    // Test NULL pointer
    int element = 1;
    QueueResult result_enqueue_null_pointer = queue_enqueue(NULL, &element);
    assert(result_enqueue_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Test NULL pointer for element
    QueueResult result_enqueue_null_pointer_element = queue_enqueue(queue_valid, NULL);
    assert(result_enqueue_null_pointer_element == QUEUE_ERROR_NULL_POINTER);

    // Test enqueueing an element
    QueueResult result_enqueue = queue_enqueue(queue_valid, &element);
    assert(result_enqueue == QUEUE_SUCCESS);
    assert(queue_valid->size == 1);
    assert(*(int*)queue_valid->head == element);

    // Test enqueueing multiple elements
    for (int i = 2; i <= 10; i++) {
        QueueResult result_enqueue = queue_enqueue(queue_valid, &i);
        assert(result_enqueue == QUEUE_SUCCESS);
        assert(queue_valid->size == (size_t)i);
        assert(*(int*)queue_valid->head == 1);
    }

    // Test enqueueing an element when the queue is full
    QueueResult result_enqueue_full = queue_enqueue(queue_valid, &element);
    assert(result_enqueue_full == QUEUE_SUCCESS);
    assert(queue_valid->size == 11);
    assert(*(int*)queue_valid->head == 1);

    // Destroy the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);
}

/**
 * @brief Test the queue_dequeue function
 * 
 * @return void
 */
void test_queue_dequeue() {
    printf("  Testing queue_dequeue...\n");

    // Test NULL pointer
    int element;
    QueueResult result_dequeue_null_pointer = queue_dequeue(NULL, &element);
    assert(result_dequeue_null_pointer == QUEUE_ERROR_NULL_POINTER);

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);

    // Test NULL pointer for element_out
    QueueResult result_dequeue_null_pointer_element_out = queue_dequeue(queue_valid, NULL);
    assert(result_dequeue_null_pointer_element_out == QUEUE_ERROR_NULL_POINTER);

    // Test enqueueing an element
    element = 1;
    QueueResult result_enqueue = queue_enqueue(queue_valid, &element);
    assert(result_enqueue == QUEUE_SUCCESS);
    assert(queue_valid->size == 1);
    assert(*(int*)queue_valid->head == element);

    // Test dequeueing an element
    QueueResult result_dequeue = queue_dequeue(queue_valid, &element);
    assert(result_dequeue == QUEUE_SUCCESS);
    assert(queue_valid->size == 0);
    assert(element == 1);

    // Test dequeueing an element when the queue is empty
    QueueResult result_dequeue_empty = queue_dequeue(queue_valid, &element);
    assert(result_dequeue_empty == QUEUE_ERROR_EMPTY);

    // Destroy the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);
}

/**
 * @brief Test the queue_destroy function
 * 
 * @return void
 */
void test_queue_destroy() {
    printf("  Testing queue_destroy...\n");

    // Create a valid queue
    Queue* queue_valid = NULL;
    QueueResult result_create_valid = queue_create(sizeof(int), 10, &queue_valid);
    assert(result_create_valid == QUEUE_SUCCESS);
    assert(queue_valid != NULL);

    // Destroy the queue
    QueueResult result_destroy = queue_destroy(&queue_valid);
    assert(result_destroy == QUEUE_SUCCESS);
    assert(queue_valid == NULL);

    // Try to destroy the queue again
    QueueResult result_destroy_again = queue_destroy(&queue_valid);
    assert(result_destroy_again == QUEUE_ERROR_NULL_POINTER);
    assert(queue_valid == NULL);
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