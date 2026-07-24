#include "binarytree.h"

void freeBinaryTreeNode(BinaryTreeNode *node);

BinaryTree* createBinaryTree(const unsigned item_size, int(*compare)(const void*, const void*)){
    if (item_size == 0) {
        fprintf(stderr, "[binarytree.c][createBinaryTree()] WARNING: item_size can't be equal to 0.\n");
        return NULL;
    }

    if (!compare) {
        fprintf(stderr, "[binarytree.c][createBinaryTree()] WARNING: Comparison function pointer can't be NULL.\n");
        return NULL;
    }    
    
    BinaryTree *tree = (BinaryTree*) malloc (sizeof(BinaryTree));

    if(!tree){
        perror("[binarytree.c][binaryTreeCreate()] ERROR: Failed to allocate memory for BinaryTree data structure.");
        return NULL;
    }

    tree->item_size = item_size;
    tree->compare = compare;
    tree->nnodes = 0;
    tree->root = NULL;

    return tree;
}

BinaryTreeNode* createBinaryTreeNode(const void* data, const unsigned item_size, BinaryTreeNode* parent){
    BinaryTreeNode* node = (BinaryTreeNode*) malloc (sizeof(BinaryTreeNode));

    if(!node){
        perror("[binarytree.c][createBinaryTreeNode()] ERROR: Failed to allocate memory for BinaryTree node.");
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;
    node->parent = parent;

    node->data = (void*) malloc (item_size);

    if(!node->data){
        perror("[binarytree.c][createBinaryTreeNode()] ERROR: Failed to allocate memory for BinaryTree node data.");
        free(node);
        return NULL;
    }

    memcpy(node->data, data, item_size);
    return node;
}

bool insertNodeBinaryTree(BinaryTree *tree, const void* data){
    if (!tree) {
        fprintf(stderr, "[binarytree.c][insertNodeBinaryTree()] WARNING: Invalid argument. The BinaryTree data structure can't be NULL.\n");
        return false;
    }
    if (!data) {
        fprintf(stderr, "[binarytree.c][insertNodeBinaryTree()] WARNING: Invalid argument. The data pointer can't be NULL.\n");
        return false;
    }

    if(!tree->root){
        BinaryTreeNode *root = createBinaryTreeNode(data, tree->item_size, NULL);
        
        if(!root) return false;

        tree->root = root;
        tree->nnodes = 1;
        return true;
    }

    BinaryTreeNode *curr = tree->root;
    while(1){
        int comparison = tree->compare(data, curr->data);

        if(comparison == 0) return false;

        if(comparison < 0){
            if(curr->left) 
                curr = curr->left;
            else {
                BinaryTreeNode* new_node = createBinaryTreeNode(data, tree->item_size, curr);
                if(!new_node) return false;

                curr->left = new_node;
                tree->nnodes += 1;
                return true;
            }
        } else {
            if(curr->right) 
                curr = curr->right;
            else {
                BinaryTreeNode* new_node = createBinaryTreeNode(data, tree->item_size, curr);
                if(!new_node) return false;

                curr->right = new_node;
                tree->nnodes += 1;
                return true;
            }
        }
    }
}

void* findNodeBinaryTree(BinaryTree *tree, const void* data){
   if (!tree) {
        fprintf(stderr, "[binarytree.c][findNodeBinaryTree()] WARNING: Invalid argument. The BinaryTree data structure can't be NULL.\n");
        return NULL;
    }

    if (!data) {
        fprintf(stderr, "[binarytree.c][findNodeBinaryTree()] WARNING: Invalid argument. Search data pointer can't be NULL.\n");
        return NULL;
    }

    if (!tree->root) {
        fprintf(stderr, "[binarytree.c][findNodeBinaryTree()] WARNING: Couldn't find corresponding node because tree is empty.\n");
        return NULL; 
    }

    BinaryTreeNode *curr = tree->root;
    while(curr){
        int comparison = tree->compare(data, curr->data);
        
        if(comparison == 0) return curr;

        if(comparison < 0){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

bool eraseNodeBinaryTree(BinaryTree *tree, const void* data){
    if (!tree) {
        fprintf(stderr, "[binarytree.c][eraseNodeBinaryTree()] WARNING: Invalid argument. The BinaryTree structure can't be NULL.\n");
        return false;
    }

    if (!data) {
        fprintf(stderr, "[binarytree.c][eraseNodeBinaryTree()] WARNING: Invalid argument. Target data pointer can't be NULL.\n");
        return false;
    }

    if (!tree->root) {
        fprintf(stderr, "[binarytree.c][eraseNodeBinaryTree()] WARNING: Can't erase node because the tree is empty.\n");
        return false;
    }
    BinaryTreeNode *curr = tree->root;

    while(curr){
        int comparison = tree->compare(data, curr->data);

        if(comparison == 0) break;

        if(comparison < 0) 
            curr = curr->left;
        else 
            curr = curr->right;
    }

    if(!curr) return false;
 
    // Case 1: Node has 2 childs 
    if(curr->left && curr->right) {
        BinaryTreeNode *predecessor = curr->left;
        while(predecessor->right){
            predecessor = predecessor->right;
        }

        memcpy(curr->data, predecessor->data, tree->item_size);

        curr = predecessor;
    }
    
    BinaryTreeNode *parent = curr->parent;    

    // Case 2: Node has 1 child
    if(curr->left || curr->right){
        BinaryTreeNode *child = curr->left ? curr->left : curr->right;

        if(!parent){
            child->parent = NULL;
            tree->root = child;
        } else if (parent->left == curr){
            child->parent = parent;
            parent->left = child;
        } else {
            child->parent = parent;
            parent->right = child;
        }
        
        tree->nnodes -= 1;
        if(curr->data) free(curr->data);
        free(curr);
        return true;
    }

    // Case 3: Node has 0 children
    if(parent){
        if(parent->left == curr)
            parent->left = NULL;
        else 
            parent->right = NULL;
    } else {
        tree->root = NULL;
    }
    tree->nnodes -= 1;

    if(curr->data) free(curr->data);
    free(curr);
    return true;
}

void printNodesPreOrderBinaryTreeNode(BinaryTreeNode *node, void(*print)(const void*)){
    if(!node) return;

    print(node->data);
    printNodesPreOrderBinaryTreeNode(node->left, print);
    printNodesPreOrderBinaryTreeNode(node->right, print);
}

void printNodesPreOrderBinaryTree(BinaryTree *tree, void(*print)(const void*)){
    if (!tree) {
        fprintf(stderr, "[binarytree.c][printNodesPreOrderBinaryTree()] WARNING: Invalid argument. BinaryTree can't be NULL.\n");
        return;
    }

    if (!print) {
        fprintf(stderr, "[binarytree.c][printNodesPreOrderBinaryTree()] WARNING: Print function pointer can't be NULL.\n");
        return;
    }

    printNodesPreOrderBinaryTreeNode(tree->root, print);
}

void printNodesInOrderBinaryTreeNode(BinaryTreeNode *node, void(*print)(const void*)){
    if(!node) return;

    printNodesInOrderBinaryTreeNode(node->left, print);
    print(node->data);
    printNodesInOrderBinaryTreeNode(node->right, print);
}

void printNodesInOrderBinaryTree(BinaryTree *tree, void(*print)(const void*)){
    if (!tree) {
        fprintf(stderr, "[binarytree.c][printNodesInOrderBinaryTree()] WARNING: Invalid argument. BinaryTree can't be NULL.\n");
        return;
    }

    if (!print) {
        fprintf(stderr, "[binarytree.c][printNodesInOrderBinaryTree()] WARNING: Print function pointer can't be NULL.\n");
        return;
    }

    printNodesInOrderBinaryTreeNode(tree->root, print);
}

void printNodesPostOrderBinaryTreeNode(BinaryTreeNode *node, void(*print)(const void*)){
    if(!node) return;

    printNodesPostOrderBinaryTreeNode(node->left, print);
    printNodesPostOrderBinaryTreeNode(node->right, print);
    print(node->data);
}

void printNodesPostOrderBinaryTree(BinaryTree *tree, void(*print)(const void*)){
    if (!tree) {
        fprintf(stderr, "[binarytree.c][printNodesPostOrderBinaryTree()] WARNING: Invalid argument. BinaryTree can't be NULL.\n");
        return;
    }
    if (!print) {
        fprintf(stderr, "[binarytree.c][printNodesPostOrderBinaryTree()] WARNING: Print function pointer can't be NULL.\n");
        return;
    }

    printNodesPostOrderBinaryTreeNode(tree->root, print);
}

void freeBinaryTreeNode(BinaryTreeNode *node){
    if(!node) return;

    freeBinaryTreeNode(node->left);
    freeBinaryTreeNode(node->right);

    if(node->data)
        free(node->data);
    free(node);
    return;
}

void freeBinaryTree(BinaryTree *tree){
    if(!tree) return;
    
    freeBinaryTreeNode(tree->root);
    free(tree);
    return;
}