/**
 * @file basec_queue.h
 * @brief Declaration of a Queue type and functions
 */

#ifndef BASEC_QUEUE_H
#define BASEC_QUEUE_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Queue structure
 */
typedef struct {
    size_t element_size; //< The size of the elements in the queue
    size_t capacity;     //< The capacity of the queue
    size_t size;         //< The size of the queue
    void* data;          //< The data of the queue
    void* base;          //< The base of the queue
    void* head;          //< The head of the queue
    void* tail;          //< The tail of the queue
} Queue;

/**
 * @brief Result of a queue operation
 */
typedef enum {
    QUEUE_SUCCESS,                     //< The operation was successful
    QUEUE_ERROR_INVALID_ELEMENT_SIZE,  //< The element size is invalid
    QUEUE_ERROR_INVALID_CAPACITY,      //< The capacity is invalid
    QUEUE_ERROR_NULL_POINTER,          //< A NULL pointer was passed to the function
    QUEUE_ERROR_MALLOC_FAILED,         //< The memory allocation failed
    QUEUE_ERROR_REALLOC_FAILED,        //< The memory reallocation failed
    QUEUE_ERROR_MEMCPY_FAILED,         //< The memcpy failed
    QUEUE_ERROR_EMPTY,                 //< The queue is empty
} QueueResult;

/**
 * @brief Convert a QueueResult to a string
 * 
 * @param result The QueueResult to convert
 * @return The string representation of the QueueResult
 */
const char* queue_result_to_string(QueueResult result);

/**
 * @brief Create a new queue
 * 
 * @param element_size The size of the elements in the queue
 * @param capacity The capacity of the queue
 * @param queue_out The output queue
 * @return The result of the operation
 */
QueueResult queue_create(size_t element_size, size_t capacity, Queue** queue_out);

/**
 * @brief Resize the capacity of a queue
 * 
 * @param queue The queue to resize
 * @param new_capacity The new capacity
 * @return The result of the operation
 */
QueueResult queue_resize(Queue* queue, size_t new_capacity);

/**
 * @brief Get the size of the queue
 * 
 * @param queue The queue to get the size of
 * @param size_out The output size
 * @return The result of the operation
 */
QueueResult queue_size(Queue* queue, size_t* size_out);

/**
 * @brief Get the capacity of the queue
 * 
 * @param queue The queue to get the capacity of
 * @param capacity_out The output capacity
 * @return The result of the operation
 */
QueueResult queue_capacity(Queue* queue, size_t* capacity_out);

/**
 * @brief Enqueue an element into the queue
 * 
 * @param queue The queue to enqueue the element into
 * @param element The element to enqueue
 * @return The result of the operation
 */
QueueResult queue_enqueue(Queue* queue, void* element);

/**
 * @brief Dequeue an element from the queue
 * 
 * @param queue The queue to dequeue the element from
 * @param element_out The output element
 * @return The result of the operation
 */
QueueResult queue_dequeue(Queue* queue, void* element_out);

/**
 * @brief Destroy a queue
 * 
 * @param queue_ptr The queue to destroy
 * @return The result of the operation
 */
QueueResult queue_destroy(Queue** queue_ptr);

#endif