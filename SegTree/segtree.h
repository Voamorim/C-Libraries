#ifndef SEGTREE_H
#define SEGTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned int uint;

/**
 * @struct SegTree
 * @brief Represents a generic Segment Tree object.
 *
 * Stores the linear array representing the binary segment tree along with node size,
 * identity element, and function pointers for custom operations.
 */
typedef struct SegTree{
    void* tree;         /**< Pointer to contiguous memory holding tree nodes (1-indexed). */
    unsigned node_size; /**< Size in bytes of a single node element (e.g., sizeof(int)). */
    void *identity;     /**< Pointer to the identity element for range queries (e.g., INT_MAX, 0). */
    void (*merge)(void*, const void*, const void*); /**< Function combining two nodes into a parent. */
    void (*update)(void*, const void*);             /**< Function applying an update to a node. */
} SegTree;

/**
 * @brief Allocates and initializes a new generic Segment Tree.
 *
 * @param capacity Total number of elements of the built on array.
 * @param node_size Size of a single element in bytes (e.g., sizeof(int)).
 * @param neutral Pointer to the identity element for the chosen operation (e.g., 0 for sum, INT_MAX for min).
 *                A copy of this data is stored internally.
 * @param merge Function pointer defining how two child node values combine into a parent node.
 *              Signature: void merge(void* dest, const void* left, const void* right)
 * @param update Function pointer defining how a node's value is modified.
 *               Signature: void update(void* target, const void* value)
 * 
 * @return SegTree* Pointer to the initialized SegTree instance, or NULL on allocation failure.
 */
SegTree* segtreeCreate(uint capacity, uint node_size, void* identity, void (*merge)(void*, const void*, const void*), void (*update)(void*, const void*));

/**
 * @brief Recursively builds the Segment Tree from an initial array of items.
 *
 * @param segtree Pointer to the SegTree instance.
 * @param items Contiguous array of source elements used to populate the tree.
 * @param tl Left bound of the current segment in the source array (initially 0).
 * @param tr Right bound of the current segment in the source array (initially N - 1).
 * @param node Index of the current tree node in internal storage (initially 1 for root).
 */
void segtreeBuild(SegTree* segtree, void* items, uint tl, uint tr, uint node);

/**
 * @brief Performs a point update at a target position in the Segment Tree.
 *
 * Recomputes affected segment nodes recursively up to the tree root.
 *
 * @param segtree Pointer to the SegTree instance.
 * @param pos Target array index to update in the original sequence [0 ... N-1].
 * @param value Pointer to the new value or update argument to apply.
 * @param tl Left bound of the current tree segment (initially 0).
 * @param tr Right bound of the current tree segment (initially N - 1).
 * @param node Index of the current tree node in internal storage (initially 1 for root).
 */
void segtreeUpdate(SegTree* segtree, uint l, uint r, void* value, uint tl, uint tr, uint node);

/**
 * @brief Queries the aggregated value over a range [l, r].
 *
 * Evaluates segment ranges in $O(\log N)$ time and writes the result into `output_result`.
 *
 * @param segtree Pointer to the SegTree instance.
 * @param output_result Pointer to preallocated memory where the query result will be written.
 * @param l Left bound of the query range [0 ... N-1] (inclusive).
 * @param r Right bound of the query range [0 ... N-1] (inclusive).
 * @param tl Left bound of the current tree segment (initially 0).
 * @param tr Right bound of the current tree segment (initially N - 1).
 * @param node Index of the current tree node in internal storage (initially 1 for root).
 */
void segtreeQuery(const SegTree* segtree, void* output_result, uint l, uint r, uint tl, uint tr, uint node);

/**
 * @brief Frees all dynamic memory associated with the Segment Tree.
 *
 * Safe to call on NULL pointers.
 *
 * @param segtree Pointer to the SegTree instance to destroy.
 */
void segtreeFree(SegTree* segtree);

#endif 