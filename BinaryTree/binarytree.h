#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @struct BinaryTreeNode 
 * @brief Represents a single node within the binary search tree.
 */
typedef struct BinaryTreeNode {
    void *data;                     /**< Pointer to dynamically allocated generic data payload */
    struct BinaryTreeNode* left;    /**< Pointer to the left child node */
    struct BinaryTreeNode* right;   /**< Pointer to the right child node */
    struct BinaryTreeNode* parent;  /**< Pointer to the parent node */
} BinaryTreeNode;

/**
 * @struct BinaryTree
 * @brief Represents the binary tree data structure controller.
 */
typedef struct BinaryTree { 
    BinaryTreeNode *root;                       /**< Pointer to the root node of the tree */
    unsigned item_size;                         /**< Size in bytes of each data item stored in nodes */ 
    unsigned nnodes;                            /**< Total count of nodes currently in the tree */
    int(*compare)(const void *, const void *);  /**< Function pointer for key comparisons */
} BinaryTree;

/**
 * @brief Allocates and initializes a new BinaryTree structure.
 * 
 * @param item_size The byte size of elements stored (e.g., sizeof(int)). Must be > 0.
 * @param compare   Pointer to comparison function returning < 0 if arg1 < arg2,
 *                  0 if arg1 == arg2, and > 0 if arg1 > arg2. Cannot be NULL.
 * 
 * @return BinaryTree* Pointer to the created tree, or NULL if allocation fails or params invalid.
 */
BinaryTree* createBinaryTree(const unsigned item_size, int(*compare)(const void*, const void*));

/**
 * @brief Inserts a new data element into the binary tree.
 * 
 * @param tree Pointer to the target BinaryTree.
 * @param data Pointer to the memory buffer holding data to insert.
 * 
 * @return true if insertion succeeded, false if tree/data is NULL or duplicate entry found.
 */
bool insertNodeBinaryTree(BinaryTree *tree, const void* data);

/**
 * @brief Searches for a node containing data matching the query item.
 * 
 * @param tree Pointer to the BinaryTree to search.
 * @param data Pointer to sample data used for comparison.
 * 
 * @return void* Pointer to the matching BinaryTreeNode if found, NULL otherwise.
 */
void* findNodeBinaryTree(BinaryTree *tree, const void* data);

/**
 * @brief Removes a node matching the target data from the binary tree.
 * 
 * Handles re-linking subtrees and updates node counts accordingly.
 * 
 * @param tree Pointer to the target BinaryTree.
 * @param data Pointer to data matching the target node to erase.
 * 
 * @return true if node was found and removed, false otherwise.
 */
bool eraseNodeBinaryTree(BinaryTree *tree, const void* data);

/**
 * @brief Performs a Pre-Order traversal (Root, Left, Right) of the tree.
 * 
 * @param tree  Pointer to the BinaryTree.
 * @param print Callback function used to print/process each node's data payload.
 */
void printNodesPreOrderBinaryTree(BinaryTree *tree, void(*print)(const void*));

/**
 * @brief Performs an In-Order traversal (Left, Root, Right) of the tree.
 * 
 * @param tree  Pointer to the BinaryTree.
 * @param print Callback function used to print/process each node's data payload.
 */
void printNodesInOrderBinaryTree(BinaryTree *tree, void(*print)(const void*));

/**
 * @brief Performs a Post-Order traversal (Left, Right, Root) of the tree.
 * 
 * @param tree  Pointer to the BinaryTree.
 * @param print Callback function used to print/process each node's data payload.
 */
void printNodesPostOrderBinaryTree(BinaryTree *tree, void(*print)(const void*));

/**
 * @brief Recursively frees all tree nodes and the BinaryTree container itself.
 * 
 * @param tree Pointer to the BinaryTree structure to deallocate.
 */
void freeBinaryTree(BinaryTree *tree);

#endif