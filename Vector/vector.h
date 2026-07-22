#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Vector
 * @brief Generic dynamic array implementation that can store elements of any type.
 */
typedef struct Vector {
    void* buffer;      /**< Pointer to the allocated memory buffer storing elements. */
    unsigned int size;        /**< Number of elements currently stored in the vector. */
    unsigned int capacity;    /**< Total number of elements the vector can hold before reallocating. */
    unsigned int item_size;   /**< Size in bytes of a single element (e.g., sizeof(int)). */
} Vector;

/**
 * @brief Allocates and initializes a new generic Vector object.
 *
 * @param initial_capacity Initial number of elements space is reserved for.
 * @param item_size Size in bytes of each stored element (e.g., `sizeof(int)`).
 * @return Vector* Pointer to the newly allocated Vector, or NULL on allocation failure.
 */
Vector* vectorCreate(const unsigned int initial_capacity, const unsigned int item_size);

/**
 * @brief Appends a new element to the end of the vector.
 *
 * Automatically resizes the underlying buffer if capacity is reached.
 *
 * @param vector Pointer to the Vector struct.
 * @param value Pointer to the value/data to copy into the vector.
 */
void vectorPushBack(Vector* vector, void* value);

/**
 * @brief Retrieves a pointer to the element at the specified index.
 *
 * @param vector Pointer to the Vector struct.
 * @param index Zero-based index of the element to retrieve.
 * @return void* Pointer to the element in the vector, or NULL if out of bounds.
 */
void* vectorGet(const Vector* vector, const unsigned int index);

/**
 * @brief Overwrites the element at a specific index with a new value.
 *
 * @param vector Pointer to the Vector struct.
 * @param index Zero-based index where the element will be overwritten.
 * @param value Pointer to the new value to copy into the vector.
 */
void vectorSet(Vector* vector, const unsigned int index, void* value);

/**
 * @brief Removes the element at the specified index, shifting subsequent elements left.
 *
 * @param vector Pointer to the Vector struct.
 * @param index Zero-based index of the element to remove.
 */
void vectorErase(Vector* vector, const unsigned int index);

/**
 * @brief Fills the entire capacity of the vector with copies of a given value.
 *
 * Iterates through all available capacity slots and uses `memcpy` to copy the 
 * provided element into each index. Updates the vector's size to match its capacity.
 *
 * @param vector Pointer to the Vector struct.
 * @param value Pointer to the value/data to fill the vector with.
 */
void vectorFill(Vector* vector, void* value);

/**
 * @brief Gets the current number of elements in the vector.
 *
 * @param vector Pointer to the Vector struct.
 * @return int Number of active elements.
 */
int vectorSize(const Vector* vector);

/**
 * @brief Gets the total capacity reserved in memory for the vector.
 *
 * @param vector Pointer to the Vector struct.
 * @return int Total element capacity available before next reallocation.
 */
int vectorCapacity(const Vector* vector);

/**
 * @brief Deallocates the vector and its internal buffer from memory.
 *
 * Note: If stored elements are pointers to dynamically allocated memory, 
 * those elements must be freed individually prior to calling this function.
 *
 * @param vector Pointer to the Vector struct to free.
 */
void vectorFree(Vector* vector);

#endif
