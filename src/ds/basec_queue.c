/**
 * @file basec_queue.c
 * @brief Implementation of a Queue type and functions
 */

#include "ds/basec_queue.h"

/**
 * @brief Convert a QueueResult to a string
 * 
 * @param result QueueResult to convert
 * @return       String representation of the QueueResult
 */
const char* queue_result_to_string(QueueResult result) {
    // Switch on the result
    switch (result) {
        case QUEUE_SUCCESS:
            return "QUEUE_SUCCESS";                    //< Success
        case QUEUE_ERROR_INVALID_ELEMENT_SIZE:
            return "QUEUE_ERROR_INVALID_ELEMENT_SIZE"; //< Invalid element size
        case QUEUE_ERROR_INVALID_CAPACITY:
            return "QUEUE_ERROR_INVALID_CAPACITY";     //< Invalid capacity
        case QUEUE_ERROR_NULL_POINTER:
            return "QUEUE_ERROR_NULL_POINTER";         //< NULL pointer
        case QUEUE_ERROR_MALLOC_FAILED:
            return "QUEUE_ERROR_MALLOC_FAILED";        //< Malloc failed
        case QUEUE_ERROR_REALLOC_FAILED:
            return "QUEUE_ERROR_REALLOC_FAILED";       //< Realloc failed
        case QUEUE_ERROR_MEMCPY_FAILED:
            return "QUEUE_ERROR_MEMCPY_FAILED";        //< Memcpy failed
        case QUEUE_ERROR_EMPTY:
            return "QUEUE_ERROR_EMPTY";                //< Empty
        default:
            return "QUEUE_ERROR_UNKNOWN";              //< Unknown error
    }
}

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
) {
    // Check the validity of the element size, capacity, and queue output
    if (element_size < 1) return QUEUE_ERROR_INVALID_ELEMENT_SIZE;
    if (capacity < 1) return QUEUE_ERROR_INVALID_CAPACITY;
    if (queue_out == NULL) return QUEUE_ERROR_NULL_POINTER;

    // Allocate memory for the queue
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    // Check if allocation failed
    if (queue == NULL) return QUEUE_ERROR_MALLOC_FAILED;

    // Initialize the queue
    queue->element_size = element_size;
    queue->capacity = capacity;
    queue->size = 0;

    // Allocate memory for the data
    queue->data = malloc(element_size * capacity);

    // Check if allocation failed
    if (queue->data == NULL) {
        // Free the queue
        free(queue);

        // Set the output to NULL
        *queue_out = NULL;

        // Malloc failed
        return QUEUE_ERROR_MALLOC_FAILED;
    }

    // Initialize the head and tail
    queue->head = queue->data;
    queue->tail = queue->head;

    // Set the output queue
    *queue_out = queue;

    // Success
    return QUEUE_SUCCESS;
}

/**
 * @brief Resize the capacity of a queue
 * 
 * @param queue        Queue to resize
 * @param new_capacity New capacity
 * @return             Result of the operation
 */
QueueResult queue_resize(Queue* queue, size_t new_capacity) {
    // Check the validity of the queue and new capacity
    if (queue == NULL) return QUEUE_ERROR_NULL_POINTER;
    if (new_capacity < 1) return QUEUE_ERROR_INVALID_CAPACITY;

    // Check if same memory can be used
    if (queue->capacity >= new_capacity) {
        // Update the capacity
        queue->capacity = new_capacity;

        // Check if size is greater than capacity
        if (queue->size > queue->capacity) {
            // Update the size and tail
            queue->size = queue->capacity;
            queue->tail = queue->head + (
                (queue->size - 1) * queue->element_size
            );
        }

        // Success
        return QUEUE_SUCCESS;
    }

    // Calculate head and tail offsets
    uint64_t head_offset = queue->head - queue->data;
    uint64_t tail_offset = queue->tail - queue->data;

    // Resize the data
    void* new_data = realloc(queue->data, new_capacity * queue->element_size);

    // Check if reallocation failed
    if (new_data == NULL) return QUEUE_ERROR_REALLOC_FAILED;

    // Update the data
    queue->data = new_data;

    // Update the head and tail
    queue->head = queue->data + head_offset;
    queue->tail = queue->data + tail_offset;

    // Update the capacity
    queue->capacity = new_capacity;

    // Success
    return QUEUE_SUCCESS;
}

/**
 * @brief Get the size of the queue
 * 
 * @param queue    Queue to get the size of
 * @param size_out Output size
 * @return         Result of the operation
 */
QueueResult queue_size(Queue* queue, size_t* size_out) {
    // Check for NULL pointers
    if (queue == NULL || size_out == NULL) return QUEUE_ERROR_NULL_POINTER;

    // Set the size
    *size_out = queue->size;

    // Success
    return QUEUE_SUCCESS;
}

/**
 * @brief Get the capacity of the queue
 * 
 * @param queue        Queue to get the capacity of
 * @param capacity_out Output capacity
 * @return             Result of the operation
 */
QueueResult queue_capacity(Queue* queue, size_t* capacity_out) {
    // Check for NULL pointers
    if (queue == NULL || capacity_out == NULL) return QUEUE_ERROR_NULL_POINTER;
    
    // Set the capacity
    *capacity_out = queue->capacity;

    // Success
    return QUEUE_SUCCESS;
}

/**
 * @brief Enqueue an element into the queue
 * 
 * @param queue   Queue to enqueue the element into
 * @param element Element to enqueue
 * @return        Result of the operation
 */
QueueResult queue_enqueue(Queue* queue, void* element) {
    // Check for NULL pointers
    if (queue == NULL || element == NULL) return QUEUE_ERROR_NULL_POINTER;

    // Check if the queue is full
    if (queue->size >= queue->capacity) {
        // Resize the queue to double its capacity
        QueueResult result_resize = queue_resize(queue, queue->capacity * 2);

        // Check if resize failed
        if (result_resize != QUEUE_SUCCESS) {
            // Resize failed
            return result_resize;
        }
    }

    // Copy the element to the tail
    void* memcpy_result = memcpy(queue->tail, element, queue->element_size);

    // Check if the copy failed
    if (memcpy_result == NULL) return QUEUE_ERROR_MEMCPY_FAILED;

    // Update the tail if the queue is not full
    if (queue->size < queue->capacity) {
        queue->tail += queue->element_size;
    }

    // Update the size
    queue->size++;

    // Success
    return QUEUE_SUCCESS;
}

/**
 * @brief Dequeue an element from the queue
 * 
 * @param queue       Queue to dequeue the element from
 * @param element_out Output element
 * @return            Result of the operation
 */
QueueResult queue_dequeue(Queue* queue, void* element_out) {
    // Check the validity of the queue and element output
    if (queue == NULL || element_out == NULL) return QUEUE_ERROR_NULL_POINTER;

    // Check if the queue is empty
    if (queue->size == 0) return QUEUE_ERROR_EMPTY;

    // Copy the element to the output
    void* memcpy_result = memcpy(element_out, queue->head, queue->element_size);

    // Check if the copy failed
    if (memcpy_result == NULL) return QUEUE_ERROR_MEMCPY_FAILED;

    // Update the size
    queue->size--;

    // Check if the queue is now empty
    if (queue->size == 0) {
        // Reset the head and tail
        queue->head = queue->data;
        queue->tail = queue->data;
    } else {
        // Update the head
        queue->head += queue->element_size;
    }

    // Success
    return QUEUE_SUCCESS;
}

/**
 * @brief Destroy a queue
 * 
 * @param queue_ptr Queue to destroy
 * @return          Result of the operation
 */
QueueResult queue_destroy(Queue** queue_ptr) {
    // Check for NULL pointers
    if (queue_ptr == NULL || *queue_ptr == NULL) {
        // NULL pointer
        return QUEUE_ERROR_NULL_POINTER;
    }

    // Free the queue data and structure
    free((*queue_ptr)->data);
    free(*queue_ptr);
    *queue_ptr = NULL;

    // Success
    return QUEUE_SUCCESS;
}