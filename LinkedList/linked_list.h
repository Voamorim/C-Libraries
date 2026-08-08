#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** 
 * @struct ListNode
 * @brief Represents an individual node within the doubly linked list.
 */
typedef struct ListNode {
    void* data;                 /**< Pointer to the user-defined data payload. */
    struct ListNode* next;      /**< Pointer to the next node in the list. */
    struct ListNode* previous;  /**< Pointer to the previous node in the list. */
} ListNode;

/**
 * @struct LinkedList
 * @brief Represents the main LinkedList struct for managing the list.
 */
typedef struct LinkedList {
    struct ListNode* head;  /**< Pointer to the first node in the list. */
    struct ListNode* tail;  /**< Pointer to the last node in the list. */
    unsigned size;          /**< Total number of nodes currently stored in the list. */
} LinkedList;

/**
 * @brief Checks whether the linked list is empty or unintialized.
 * 
 * @param list Pointer to the LinkedList instance.
 * @return true if the list is NULL, head is NULL, or size is 0; false otherwise.
 */
bool listIsEmpty(const LinkedList* list);

/**
 * @brief Retrieves the current number of elements in the linked list.
 * 
 * @param list Pointer to the LinkedList instance.
 * @return Total element count, or 0 if the list pointer is NULL.
 */
unsigned listSize(const LinkedList* list);

/**
 * @brief Allocates and initializes a new, empty LinkedList instance on the heap.
 * 
 * @return Pointer to the newly allocated LinkedList, or NULL if memory allocation fails.
 */
LinkedList* createList(void);

/**
 * @brief Deallocates all list nodes and the LinkedList control structure itself.
 * 
 * @note This function frees list node memory, but doesn't free user data
 * payloads pointed by `data`. Use freeListComplete() if payload deallocation is
 * required.
 * 
 * @param list Pointer to the LinkedList instance to be freed.
 */
void freeList(LinkedList* list);

/**
 * @brief Deallocates all list nodes, user data payloads, and the LinkedList 
 * structure.
 * 
 * @param list Pointer to the LinkedList instance to be freed.
 * @param freeData Callback function used to free the memory of each node's 
 * `data` payload.
 */
void freeListComplete(LinkedList* list, void (*freeData)(void*));

/**
 * @brief Appends a new data element to the end (tail) of the list.
 * 
 * @param list Pointer to the LinkedList instance.
 * @param data Pointer to the payload to be stored.
 */
void linkedListPushBack(LinkedList* list, void* data);

/**
 * @brief Appends a new data ellmement to the end (tail) of the list.
 * 
 * @param list Pointer to the LinkedList instance.
 * @param data Pointer to the payload to be stored.
 */
void linkedListPushFront(LinkedList* list, void* data);

/**
 * @brief Removes the first element (head) from the list and returns its data 
 * payload.
 * 
 * @param list Pointer to the LinkedList instance.
 * @return Pointer to the data payload, or NULL if the list is empty or NULL.
 */
void* linkedListPopFront(LinkedList* list);

/**
 * @brief Removes the last element (tail) from the list and returns its data
 * payload.
 * 
 * @param list Pointer to the LinkedList instance.
 * @return Pointer to the data payload, or NULL if the list is empty or NULL.
 */
void* linkedListPopBack(LinkedList* list);

/**
 * @brief Removes a specific target node from the list and returns its data 
 * paylaod.
 * 
 * @param list Pointer to the LinkedList instance.
 * @param target Pointer to the specific ListNode to be removed.
 * @return Pointer to the data payload, or NULL if the target or list is invalid.
 */
void* linkedListPopNode(LinkedList* list, struct ListNode* target);

/**
 * @brief Retrieves the data payload stored at a specific 0-based index.
 *   
 * @param list Pointer to the LinkedList instance.
 * @param pos Zero-based position index of the element to retrieve.
 * @return Pointer to data payload at target position, or NULL if index is out 
 * of bounds.
 */
void* linkedListGet(LinkedList* list, unsigned pos);

/**
 * @brief Inserts a new data element at a specific 0-based position in the list.
 * 
 * @param list Pointer to the LinkedList instance.
 * @param data Pointer to the payload to be stored.
 * @param pos Zero-based position index where the new element will be placed.
 */
void linkedListInsertAt(LinkedList* list, void* data, unsigned pos);

/**
 * @brief Searches for an element matching `target_data` using a comparison 
 * function.
 * 
 * @param list Pointer to the LinkedList instance.
 * @param target_data Pointer to the value/data object being searched for.
 * @param compare Pointer to the comparison function returning 0 on match.
 * @return Zero-based index or the first matching element, or -1 if not found.
 */
int linkedListFind(const LinkedList* list, const void* target_data, int(*compare)(const void*, const void*));

/**
 * @brief Iterates through every element in the list, executing `func` on each 
 * data payload.
 * 
 * @param list Pointer to the LinkedList instance.
 * @param func Callback function executed for each element's `data` payload.
 */
void linkedListForEach(const LinkedList* list, void (*func)(void*));

#endif