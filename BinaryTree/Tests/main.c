#include "../binarytree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int compareInt(const void *a, const void *b){
    int x = *((const int*) a);
    int y = *((const int*) b);

    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int traversal_output[20];
int traversal_idx = 0;

void recordPrint(const void *data){
    traversal_output[traversal_idx++] = *(const int*)data;
}

void testInitialization(void);
void testInsertionAndSearch(void);
void testTraversals(void);
void testDeletion(void);

int main(){
    testInitialization();
    puts("\nBinary Treee initialization is working properly!\n");

    testInsertionAndSearch();
    puts("\nBinary Treee insertion and search are working properly!\n");
    
    testTraversals();
    puts("\nBinary Treee traversals are working properly!\n");

    testDeletion();
    puts("\nBinary Treee deletion is working properly!\n");

    return 0;
}

void testInitialization(void){
    // Invalid parameters should return NULL
    assert(createBinaryTree(0, compareInt) == NULL);
    assert(createBinaryTree(sizeof(int), NULL) == NULL);

    // Valid tree initialization
    BinaryTree *tree = createBinaryTree(sizeof(int), compareInt);
    assert(tree != NULL);
    assert(tree->root == NULL);
    assert(tree->nnodes == 0);
    assert(tree->item_size == sizeof(int));

    freeBinaryTree(tree);
}

void testInsertionAndSearch(void){
    BinaryTree *tree = createBinaryTree(sizeof(int), compareInt);

    // Test NULL argument safety guards
    assert(insertNodeBinaryTree(NULL, &(int){10}) == false);
    assert(insertNodeBinaryTree(tree, NULL) == false);

    // Insert root
    int x = 50;
    assert(insertNodeBinaryTree(tree, &x) == true);
    assert(tree->nnodes == 1);
    assert(tree->root != NULL);

    // Insert subtrees
    int values[] = {30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 6; i++) {
        assert(insertNodeBinaryTree(tree, &values[i]) == true);
    }
    assert(tree->nnodes == 7);

    // Duplicate insertion should fail
    int duplicate = 40;
    assert(insertNodeBinaryTree(tree, &duplicate) == false);
    assert(tree->nnodes == 7);

    // Test finding existing nodes
    int find_val = 40;
    BinaryTreeNode *found = (BinaryTreeNode*)findNodeBinaryTree(tree, &find_val);
    assert(found != NULL);
    assert(*(int*)(found->data) == 40);

    // Test finding non-existing node
    int missing_val = 99;
    assert(findNodeBinaryTree(tree, &missing_val) == NULL);

    freeBinaryTree(tree);
}

void testTraversals(void){
    BinaryTree *tree = createBinaryTree(sizeof(int), compareInt);

    // Insert values out of order
    int values[] = {50, 30, 70, 20, 40};
    for (int i = 0; i < 5; i++) {
        insertNodeBinaryTree(tree, &values[i]);
    }

    traversal_idx = 0;
    printNodesInOrderBinaryTree(tree, recordPrint);

    // Binary search tree in-order traversal MUST yield sorted order
    int expected[] = {20, 30, 40, 50, 70};
    assert(traversal_idx == 5);
    for (int i = 0; i < 5; i++) {
        assert(traversal_output[i] == expected[i]);
    }

    freeBinaryTree(tree); 
}

void testDeletion(void){
    BinaryTree *tree = createBinaryTree(sizeof(int), compareInt);

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        insertNodeBinaryTree(tree, &values[i]);
    }

    // Attempting to erase from invalid or non-existent items
    int missing = 99;
    assert(eraseNodeBinaryTree(tree, &missing) == false);
    assert(eraseNodeBinaryTree(tree, NULL) == false);

    // Case 1: Delete Leaf Node 
    int target_leaf = 20;
    assert(eraseNodeBinaryTree(tree, &target_leaf) == true);
    assert(tree->nnodes == 6);
    assert(findNodeBinaryTree(tree, &target_leaf) == NULL);

    // Case 2: Delete Node with 1 Child 
    int val_25 = 25;
    insertNodeBinaryTree(tree, &val_25); 
    
    // Node 30 now has only right child (40) and left child (25)
    // Delete leaf 40 first so 30 only has 1 child (25)
    int val_40 = 40;
    eraseNodeBinaryTree(tree, &val_40);
    
    int target_one_child = 30;
    assert(eraseNodeBinaryTree(tree, &target_one_child) == true);
    assert(findNodeBinaryTree(tree, &target_one_child) == NULL);

    // Case 3: Delete Node with 2 Children 
    int target_two_children = 70;
    assert(eraseNodeBinaryTree(tree, &target_two_children) == true);
    assert(findNodeBinaryTree(tree, &target_two_children) == NULL);

    // Verify structural integrity of remaining nodes
    int val_60 = 60, val_80 = 80;
    assert(findNodeBinaryTree(tree, &val_60) != NULL);
    assert(findNodeBinaryTree(tree, &val_80) != NULL);

    // Delete Root Node
    int root_val = 50;
    assert(eraseNodeBinaryTree(tree, &root_val) == true);
    assert(findNodeBinaryTree(tree, &root_val) == NULL);

    freeBinaryTree(tree);
}