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
    size_t element_size; //< Size of the elements
    size_t capacity;     //< Capacity of the queue
    size_t size;         //< Size of the queue
    void* data;          //< Data pointer
    void* head;          //< Head pointer
    void* tail;          //< Tail pointer
} Queue;

/**
 * @brief Result of a queue operation
 */
typedef enum {
    QUEUE_SUCCESS,                    //< Success
    QUEUE_ERROR_INVALID_ELEMENT_SIZE, //< Invalid element size
    QUEUE_ERROR_INVALID_CAPACITY,     //< Invalid capacity
    QUEUE_ERROR_NULL_POINTER,         //< NULL pointer
    QUEUE_ERROR_MALLOC_FAILED,        //< Malloc failed
    QUEUE_ERROR_REALLOC_FAILED,       //< Realloc failed
    QUEUE_ERROR_MEMCPY_FAILED,        //< Memcpy failed
    QUEUE_ERROR_EMPTY,                //< Empty
} QueueResult;

/**
 * @brief Convert a QueueResult to a string
 * 
 * @param result QueueResult to convert
 * @return       String representation of the QueueResult
 */
const char* queue_result_to_string(QueueResult result);

/**
 * @brief Create a new queue
 * 
 * @param element_size Size of the elements
 * @param capacity     Capacity of the queue
 * @param queue_out    Output queue
 * @return             Result of the operation
 */
QueueResult queue_create(
    size_t element_size,
    size_t capacity,
    Queue** queue_out
);

/**
 * @brief Resize the capacity of a queue
 * 
 * @param queue        Queue to resize
 * @param new_capacity New capacity
 * @return             Result of the operation
 */
QueueResult queue_resize(Queue* queue, size_t new_capacity);

/**
 * @brief Get the size of the queue
 * 
 * @param queue    Queue to get the size of
 * @param size_out Output size
 * @return         Result of the operation
 */
QueueResult queue_size(Queue* queue, size_t* size_out);

/**
 * @brief Get the capacity of the queue
 * 
 * @param queue        Queue to get the capacity of
 * @param capacity_out Output capacity
 * @return             Result of the operation
 */
QueueResult queue_capacity(Queue* queue, size_t* capacity_out);

/**
 * @brief Enqueue an element into the queue
 * 
 * @param queue   Queue to enqueue the element into
 * @param element Element to enqueue
 * @return        Result of the operation
 */
QueueResult queue_enqueue(Queue* queue, void* element);

/**
 * @brief Dequeue an element from the queue
 * 
 * @param queue       Queue to dequeue the element from
 * @param element_out Output element
 * @return            Result of the operation
 */
QueueResult queue_dequeue(Queue* queue, void* element_out);

/**
 * @brief Destroy a queue
 * 
 * @param queue_ptr Queue to destroy
 * @return          Result of the operation
 */
QueueResult queue_destroy(Queue** queue_ptr);

#endif