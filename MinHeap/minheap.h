#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Generic MinHeap data structure
 * 
 * Supports dynamic resizing and accepts arbitrary data types using generic void 
 * pointers and a user-defined comparator function
 */
typedef struct MinHeap{
    void* data;                                 /**< Pointer to the continuous block of heap elements. */
    unsigned item_size;                         /**< Size in bytes of each individual element. */
    unsigned size;                              /**< Current number of elements stored in the heap */
    unsigned capacity;                          /**< Total allocated capacity of the heap buffer. */
    int(*compare)(const void*, const void*);    /**< Function pointer for element comparison. */
} MinHeap;

/**
 * @brief Creates and initializes a MinHeap populated from an existing array of data.
 * 
 * Performs bottom-up heap construction algorithm (min_heapify) in O(N) time.
 * 
 * @param data Pointer to the source array containing initial data elements.
 * @param size The number of elements in the source array.
 * @param item_size The size in bytes of a single element (e.g., sizeof(int)).
 * @param compare Pointer to the function used to compare elements
 * @return Pointer to the allocated MinHeap instance, or NULL if allocation/arguments fail.
 */
MinHeap* createMinHeap(void* data, unsigned size, unsigned item_size, int(*compare)(const void*, const void*));

/**
 * @brief Creates an empty MinHeap with a specified initial capacity.
 * 
 * @param capacity Initial number of elements the heap can hold before reallocating.
 * @param item_size The size in bytes of a single element (e.g., sizeof(int)).
 * @param compare Pointer to the function used to compare elements.
 * @return Pointer to the allocated MinHeap instance, or NULL if allocation/arguments fail.
 */
MinHeap* createEmptyMinHeap(unsigned capacity, unsigned item_size, int(*compare)(const void*, const void*));

/**
 * @brief Inserts a new element into the MinHeap.
 * 
 * Expands underlying capacity automatically if the heap is full.
 * Runs in O(log N) time.
 * 
 * @param min_heap Pointer to the MinHeap data structure.
 * @param value Pointer to the value/data memory to be copied into the structure.
 */
void minHeapInsert(MinHeap* min_heap, void* value);

/**
 * @brief Removes the minimum (root) element from the heap.
 * 
 * Restores the MinHeap property via percolation down.
 * Runs in O(log N) time.
 * 
 * @param min_heap Pointer to the MinHeap data structure.
 */
void minHeapPop(MinHeap* min_heap);

/**
 * @brief Retrieves a pointer to the minimum element at the root of the heap without removing it.
 * 
 * Runs in O(1) time.
 * 
 * @param min_heap Pointer to the MinHeap data structure.
 * @return Pointer to the root element's data within the heap, or NULL if empty or invalid heap.
 */
void* minHeapTop(MinHeap* min_heap);

/**
 * @brief Frees all memory associated with the MinHeap, including its internal data array.
 * 
 * @param min_heap Pointer to the MinHeap data structured to be destroyed.
 */
void destroyMinHeap(MinHeap* min_heap);

#endif