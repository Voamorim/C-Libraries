#include "linked_list.h"

bool listIsEmpty(const LinkedList* list) {
    if(!list){
        fprintf(stderr, "[linked_list.c][listIsEmpty()] WARNING: List pointer is NULL.\n");
        return true;
    }
    return list->size == 0;
}

unsigned listSize(const LinkedList* list) { 
    if(!list){
        fprintf(stderr, "[linked_list.c][listSize()] WARNING: List pointer is NULL.\n");
        return 0;
    }
    return list->size; 
}

LinkedList* createList(void) {
    LinkedList* new_list = (LinkedList*)malloc(sizeof(LinkedList));

    if (new_list == NULL) {
        perror("[linked_list.c][createList()] ERROR: Failed to allocate memory for Linked List data structure.\n");
        return NULL;
    }

    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

void freeList(LinkedList* list) {
    if (!list){
        fprintf(stderr, "[linked_list.c][freeList()] WARNING: List pointer is NULL.\n");
        return;
    } 

    struct ListNode* curr = list->head;
    struct ListNode* next;

    // Removes nodes starting from the beginning 
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    free(list);
}

void freeListComplete(LinkedList* list, void (*freeData)(void*)) {
    if (!list){
        fprintf(stderr, "[linked_list.c][freeListComplete()] WARNING: List pointer is NULL.\n");
        return;
    } 
   
    // Checks if the provided function pointer is valid
    if (!freeData) {
        fprintf(stderr, "[linked_list.c][freeListComplete()] ERROR: Invalid pointer to free function.\n");
        return;
    }

    struct ListNode* curr = list->head;
    struct ListNode* next;

    while (curr != NULL) {
        next = curr->next;

        // Checks if the stored data exists 
        if (curr->data != NULL) 
            freeData(curr->data);

        free(curr);
        curr = next;
    }

    free(list);
}

void linkedListPushBack(LinkedList* list, void* data) {
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListPushBack()] ERROR: List pointer is NULL.\n");
        return;
    }
   
    // If the list is empty, delegate directly to push front to avoid useless
    // allocation    
    if(list->tail == NULL){
        linkedListPushFront(list, data);
        return;
    }

    struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
    
    if (new_node == NULL) {
        perror("[linked_list.c][linkedListPushBack()] ERROR: Failed to allocate memory for Linked List node.\n");
        return;
    }

    struct ListNode* curr = list->tail;
    curr->next = new_node;

    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = curr;

    list->tail = new_node;
    list->size += 1;
    return;
}

void linkedListPushFront(LinkedList* list, void* data) {
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListPushFront()] ERROR: List pointer is NULL\n");
        return;
    }

    struct ListNode* new_node = (struct ListNode*) malloc (sizeof(struct ListNode));

    if (new_node == NULL) {
        perror("[linked_list.c][linkedListPushFront()] ERROR: Failed to allocate memory for Linked List node.\n");
        return;
    }

    new_node->previous = NULL;  // Head node has no predecessor 
    new_node->data = data;

    // Checks if the list has no head node 
    if (list->head) {
        new_node->next = list->head;
        list->head->previous = new_node;
        list->head = new_node;
    } else {
        // If it does not have a head node, inserts the first node into the list 
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
    }

    list->size += 1;
}

void* linkedListPopFront(LinkedList* list) {
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListPopFront()] ERROR: List pointer is NULL.\n");
        return NULL;
    }

    if(listIsEmpty(list)){
        fprintf(stderr, "[linked_list.c][linkedListPopFront()] WARNING: Failed to pop front node. List is empty.\n");
        return NULL;
    }

    struct ListNode* curr = list->head;
    list->head = list->head->next;

    // Checks if the node following the head node exists 
    if (list->head != NULL) {
        // Ensures the new head node does not point to any previous node 
        list->head->previous = NULL;
        list->size -= 1;
    } else {
        list->tail = NULL;
        list->size = 0;
    }

    void* data = curr->data;
    free(curr);
    return data;
}

void* linkedListPopBack(LinkedList* list) {
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListPopBack()] ERROR: List pointer is NULL.\n");
        return NULL;
    }

    if(listIsEmpty(list)){
        fprintf(stderr, "[linked_list.c][linkedListPopBack()] WARNING: Failed to pop back node. List is empty.\n");
        return NULL;
    }

    struct ListNode* curr = list->tail;

    // Checks if the last node of the list has a predecessor 
    if (curr->previous) {
        void* data = curr->data;
        curr = curr->previous;

        free(curr->next);
        curr->next = NULL;
        list->tail = curr;
        list->size -= 1;
        return data;
    } else {
        void* data = curr->data;
        free(curr);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return data;
    }
}

void* linkedListPopNode(LinkedList* list, struct ListNode* target) {
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListPopNode()] ERROR: List pointer is NULL.\n");
        return NULL;
    }

    if(!target){
        fprintf(stderr, "[linked_list.c][linkedListPopNode()] ERROR: Target node pointer is NULL.\n");
        return NULL;
    }

    if(listIsEmpty(list)){
        fprintf(stderr, "[linked_list.c][linkedListPopNode()] WARNING: Failed to pop target node. List is empty.\n");
        return NULL;
    }

    struct ListNode* curr;

    // If the node to be removed is between two existing nodes
    if (target->next && target->previous) {
        // Makes the surrounding nodes point to each other 
        curr = target->next;
        target->previous->next = curr;
        curr->previous = target->previous;
    } else if (target->next) {
        // If the node to be removed only has a next node, it's the head node 
        list->head = target->next;
        list->head->previous = NULL;
    } else if (target->previous) {
        // If the node to be removed only has a previous node, it's the tail node
        // of the list
        target->previous->next = NULL;
        list->tail = target->previous;
    } else {
        // If the node has neither a predecessor nor a sucessor, it's the last
        // remaining node in the list 
        list->head = NULL;
        list->tail = NULL;
    }

    void* data = target->data;

    free(target);
    list->size -= 1;

    return data;
}

void* linkedListGet(LinkedList* list, unsigned pos){
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListGet()] ERROR: List pointer is NULL.\n");
        return NULL;
    }

    if(pos >= list->size){
        fprintf(stderr, "[linked_list.c][linkedListGet()] WARNING: Index out of bounds.\n");
        return NULL;
    }

    struct ListNode* curr;

    // Optimize traversal direction based on position
    if(pos < list->size / 2){
        curr = list->head;
        for(unsigned i = 0; i < pos; ++i){
            curr = curr->next;
        }
    } else {
        curr = list->tail;
        for(unsigned i = list->size - 1; i > pos; --i){
            curr = curr->previous;
        }
    }

    return curr->data;
}

void linkedListInsertAt(LinkedList* list, void* data, unsigned pos){
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListInsertAt()] ERROR: List pointer is NULL.\n");
        return;
    }

    if(pos > list->size){
        fprintf(stderr, "[linked_list.c][linkedListInsertAt()] WARNING: Index out of bounds.\n");
        return;
    }

    // Delegate head insertion
    if(pos == 0){
        linkedListPushFront(list, data);
        return;
    }

    // Delegate tail insertion
    if(pos == list->size){
        linkedListPushBack(list, data);
        return;
    }

    ListNode* new_node = (ListNode*) malloc (sizeof(ListNode));

    if(new_node == NULL){
        fprintf(stderr, "[linked_list.c][linkedListInsertAt()] ERROR: Failed to allocate memory for Linked List node.\n");
        return;
    }

    // Traverse to the node currently at pos
    ListNode* target;
    if(pos < list->size / 2){
        target = list->head;
        for(unsigned i = 0; i < pos; ++i){
            target = target->next;
        }
    } else {
        target = list->tail;
        for(unsigned i = list->size - 1; i > pos; --i){
            target = target->previous;
        }
    }

    new_node->data = data;
    new_node->previous = target->previous;
    new_node->next = target;
    
    target->previous->next = new_node;
    target->previous = new_node;

    list->size += 1;
}

int linkedListFind(const LinkedList* list, const void* target_data, int(*compare)(const void*, const void*)){
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListFind()] ERROR: List pointer is NULL.\n");
        return -1;
    }

    if(!compare){
        fprintf(stderr, "[linked_list.c][linkedListFind()] ERROR: Compare function pointer is NULL.\n");
        return -1;
    }

    if(listIsEmpty(list)) return -1;

    ListNode* curr = list->head;
    int idx = 0;

    while(curr != NULL){
        if(compare(curr->data, target_data) == 0){
            return idx;
        }
        curr = curr->next;
        idx += 1;
    }
    return -1;
}

void linkedListForEach(const LinkedList* list, void (*func)(void*)) {
    if(!list){
        fprintf(stderr, "[linked_list.c][linkedListForEach()] WARNING: List pointer is NULL.\n");
        return;
    }

    if(!func){
        fprintf(stderr, "[linked_list.c][linkedListForEach()] ERROR: Function pointer is NULL.\n");
    }

    if(listIsEmpty(list)){
        fprintf(stderr, "[linked_list.c][linkedListForEach()] WARNING: Failed to perform for each. List is empty.\n");
        return;
    }
   
    struct ListNode* curr = list->head;

    // Iterated through the list node executing the function 
    while (curr != NULL) {
        func(curr->data);
        curr = curr->next;
    }
}