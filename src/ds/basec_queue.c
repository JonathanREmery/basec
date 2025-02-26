/**
 * @file basec_queue.c
 * @brief Implementation of a Queue type and functions
 */

#include "ds/basec_queue.h"

/**
 * @brief Convert a QueueResult to a string
 * 
 * @param result The QueueResult to convert
 * @return The string representation of the QueueResult
 */
const char* queue_result_to_string(QueueResult result) {
    switch (result) {
        case QUEUE_SUCCESS:
            return "QUEUE_SUCCESS";
        case QUEUE_ERROR_INVALID_ELEMENT_SIZE:
            return "QUEUE_ERROR_INVALID_ELEMENT_SIZE";
        case QUEUE_ERROR_INVALID_CAPACITY:
            return "QUEUE_ERROR_INVALID_CAPACITY";
        case QUEUE_ERROR_NULL_POINTER:
            return "QUEUE_ERROR_NULL_POINTER";
        case QUEUE_ERROR_MALLOC_FAILED:
            return "QUEUE_ERROR_MALLOC_FAILED";
        case QUEUE_ERROR_REALLOC_FAILED:
            return "QUEUE_ERROR_REALLOC_FAILED";
        case QUEUE_ERROR_MEMCPY_FAILED:
            return "QUEUE_ERROR_MEMCPY_FAILED";
        case QUEUE_ERROR_EMPTY:
            return "QUEUE_ERROR_EMPTY";
        default:
            return "QUEUE_ERROR_UNKNOWN";
    }
}

/**
 * @brief Create a new queue
 * 
 * @param element_size The size of the elements in the queue
 * @param capacity The capacity of the queue
 * @param queue_out The output queue
 * @return The result of the operation
 */
QueueResult queue_create(size_t element_size, size_t capacity, Queue** queue_out) {
    // Check if element size is valid
    if (element_size < 1) {
        return QUEUE_ERROR_INVALID_ELEMENT_SIZE;
    }

    // Check if capacity is valid
    if (capacity < 1) {
        return QUEUE_ERROR_INVALID_CAPACITY;
    }

    // Check for NULL pointer
    if (queue_out == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Create the queue
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        return QUEUE_ERROR_MALLOC_FAILED;
    }

    // Initialize the queue
    queue->element_size = element_size;
    queue->capacity = capacity;
    queue->size = 0;

    // Initialize the data
    queue->data = malloc(element_size * capacity);
    if (queue->data == NULL) {
        free(queue);
        return QUEUE_ERROR_MALLOC_FAILED;
    }

    // Initialize the base, head, and tail
    queue->base = queue->data;
    queue->head = queue->base;
    queue->tail = queue->head;

    // Return the queue
    *queue_out = queue;
    return QUEUE_SUCCESS;
}

/**
 * @brief Resize the capacity of a queue
 * 
 * @param queue The queue to resize
 * @param new_capacity The new capacity
 * @return The result of the operation
 */
QueueResult queue_resize(Queue* queue, size_t new_capacity) {
    // Check for NULL pointer
    if (queue == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Check for invalid capacity
    if (new_capacity < 1) {
        return QUEUE_ERROR_INVALID_CAPACITY;
    }

    // Check for invalid element size
    if (queue->element_size < 1) {
        return QUEUE_ERROR_INVALID_ELEMENT_SIZE;
    }

    // Check if memory needs to be reallocated
    if (queue->capacity >= new_capacity) {
        // Update the capacity
        queue->capacity = new_capacity;

        // Check if size is greater than capacity
        if (queue->size > queue->capacity) {
            // Update the size and tail
            queue->size = queue->capacity;
            queue->tail = queue->head + ((queue->size - 1) * queue->element_size);
        }

        // Return the success result
        return QUEUE_SUCCESS;
    }

    // Calculate head and tail offsets
    uint64_t head_offset = queue->head - queue->base;
    uint64_t tail_offset = queue->tail - queue->base;

    // Resize the data
    void* new_data = realloc(queue->data, new_capacity * queue->element_size);
    if (new_data == NULL) {
        return QUEUE_ERROR_REALLOC_FAILED;
    }

    // Update the data
    queue->data = new_data;

    // Update the base, head, and tail
    queue->base = queue->data;
    queue->head = queue->base + head_offset;
    queue->tail = queue->base + tail_offset;

    // Update the capacity
    queue->capacity = new_capacity;

    // Return the success result
    return QUEUE_SUCCESS;
}

/**
 * @brief Get the size of the queue
 * 
 * @param queue The queue to get the size of
 * @param size_out The output size
 * @return The result of the operation
 */
QueueResult queue_size(Queue* queue, size_t* size_out) {
    // Check for NULL pointers
    if (queue == NULL || size_out == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Set the size
    *size_out = queue->size;

    // Return the success result
    return QUEUE_SUCCESS;
}

/**
 * @brief Get the capacity of the queue
 * 
 * @param queue The queue to get the capacity of
 * @param capacity_out The output capacity
 * @return The result of the operation
 */
QueueResult queue_capacity(Queue* queue, size_t* capacity_out) {
    // Check for NULL pointers
    if (queue == NULL || capacity_out == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }
    
    // Set the capacity
    *capacity_out = queue->capacity;

    // Return the success result
    return QUEUE_SUCCESS;
}

/**
 * @brief Enqueue an element into the queue
 * 
 * @param queue The queue to enqueue the element into
 * @param element The element to enqueue
 * @return The result of the operation
 */
QueueResult queue_enqueue(Queue* queue, void* element) {
    // Check for NULL pointers
    if (queue == NULL || element == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Check if the queue is full
    if (queue->size >= queue->capacity) {
        // Resize the queue to double its capacity
        QueueResult result_resize = queue_resize(queue, queue->capacity * 2);
        if (result_resize != QUEUE_SUCCESS) {
            return result_resize;
        }
    }

    // Copy the element to the tail
    void* memcpy_result = memcpy(queue->tail, element, queue->element_size);
    if (memcpy_result == NULL) {
        return QUEUE_ERROR_MEMCPY_FAILED;
    }

    // Update the tail if the queue is not full
    if (queue->size < queue->capacity) {
        queue->tail += queue->element_size;
    }

    // Update the size
    queue->size++;

    // Return the success result
    return QUEUE_SUCCESS;
}

/**
 * @brief Dequeue an element from the queue
 * 
 * @param queue The queue to dequeue the element from
 * @param element_out The output element
 * @return The result of the operation
 */
QueueResult queue_dequeue(Queue* queue, void* element_out) {
    // Check for NULL pointers
    if (queue == NULL || element_out == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Check if the queue is empty
    if (queue->size == 0) {
        return QUEUE_ERROR_EMPTY;
    }
    
    // Copy the element to the output
    void* memcpy_result = memcpy(element_out, queue->head, queue->element_size);
    if (memcpy_result == NULL) {
        return QUEUE_ERROR_MEMCPY_FAILED;
    }

    // Update the size
    queue->size--;

    // Check if the queue is now empty
    if (queue->size == 0) {
        // Reset the head and tail
        queue->head = queue->base;
        queue->tail = queue->base;
    } else {
        // Update the head
        queue->head += queue->element_size;
    }

    // Return the success result
    return QUEUE_SUCCESS;
}

/**
 * @brief Destroy a queue
 * 
 * @param queue_ptr The queue to destroy
 * @return The result of the operation
 */
QueueResult queue_destroy(Queue** queue_ptr) {
    // Check for NULL pointers
    if (queue_ptr == NULL || *queue_ptr == NULL) {
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Free the queue data and structure
    free((*queue_ptr)->data);
    free(*queue_ptr);
    *queue_ptr = NULL;

    // Return the success result
    return QUEUE_SUCCESS;
}
