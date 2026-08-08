#include "../linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void testCreateAndEmpty(void);
void testPushAndPopFront(void);
void testPushAndPopBack(void);
void testPopNode(void);
void testForEach(void);
void testFreeComplete(void);
void testNullAndEdgeCases(void);
void testGetElement(void);
void testInsertAt(void);
void testFind(void);

void calcSum(void* data);
void customFreeFunc(void* data);
int compareInt(const void* a, const void* b);

int sum = 0;

int main(){
    testCreateAndEmpty();
    testPushAndPopFront();
    testPushAndPopBack();
    testPopNode();
    testForEach();
    testFreeComplete();
    testNullAndEdgeCases();
    testGetElement();
    testInsertAt();
    testFind();

    puts("All tests are completed!!");

    return 0;
}

void testCreateAndEmpty(void){
    LinkedList* list = createList();
    assert(list != NULL);
    assert(listIsEmpty(list) == true);
    assert(listSize(list) == 0);

    freeList(list);
}

void testPushAndPopFront(void){
    LinkedList* list = createList();
    int a = 10, b = 20, c = 30;

    linkedListPushFront(list, &a); 
    assert(listSize(list) == 1);
    assert(listIsEmpty(list) == false);

    linkedListPushFront(list, &b);
    linkedListPushFront(list, &c);
    assert(listSize(list) == 3);

    int* x = (int*) linkedListPopFront(list);
    assert(x != NULL && *x == 30);
    assert(listSize(list) == 2);

    int* y = (int*) linkedListPopFront(list);
    assert(y != NULL && *y == 20);

    int* z = (int*) linkedListPopFront(list);
    assert(z != NULL && *z == 10);

    assert(listIsEmpty(list) == true);
    assert(listSize(list) == 0);

    freeList(list);
}

void testPushAndPopBack(void){
    LinkedList* list = createList();
    int a = 1, b = 2, c = 3;

    linkedListPushBack(list, &a);
    linkedListPushBack(list, &b);
    linkedListPushBack(list, &c);   
    assert(listSize(list) == 3);

    int* x = (int*)linkedListPopBack(list);
    assert(x != NULL && *x == 3);
    
    int* y = (int*)linkedListPopBack(list);
    assert(y != NULL && *y == 2);
    
    int* z = (int*)linkedListPopBack(list);
    assert(z != NULL && *z == 1);

    assert(listIsEmpty(list) == true);
    assert(listSize(list) == 0);

    freeList(list);
}

void testPopNode(void){
    LinkedList* list = createList();
    int a = 100, b = 200, c = 300;

    linkedListPushBack(list, &a);
    linkedListPushBack(list, &b);
    linkedListPushBack(list, &c);

    ListNode* middle = list->head->next;
    int* x = (int*) linkedListPopNode (list, middle);
    assert(x != NULL && *x == 200);
    assert(listSize(list) == 2);

    ListNode* tail = list->tail;
    int* y = (int*) linkedListPopNode (list, tail);
    assert(y != NULL && *y == 300);
    assert(listSize(list) == 1);

    ListNode *head = list->head;
    int* z = (int*) linkedListPopNode (list, head);
    assert(z != NULL && *z == 100);

    assert(listIsEmpty(list) == true);
    assert(listSize(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);

    freeList(list);
}

void testForEach(void){
    LinkedList *list = createList();
    int a = 5, b = 10, c = 15;

    linkedListPushBack(list, &a);
    linkedListPushBack(list, &b);
    linkedListPushBack(list, &c);

    sum = 0;
    linkedListForEach(list, calcSum);
    assert(sum == 30);

    freeList(list);
}

void testFreeComplete(void){
    LinkedList *list = createList();

    int* x = (int*) malloc (sizeof(int));
    int* y = (int*) malloc (sizeof(int));
    *x = 50; *y = 100;

    linkedListPushBack(list, x);
    linkedListPushBack(list, y);

    freeListComplete(list, customFreeFunc);
}

void testNullAndEdgeCases(void){
    assert(listIsEmpty(NULL) == true);
    assert(listSize(NULL) == 0);
    assert(linkedListPopFront(NULL) == NULL);
    assert(linkedListPopBack(NULL) == NULL);
    assert(linkedListPopNode(NULL, NULL) == NULL);

    LinkedList* list = createList();
    assert(linkedListPopFront(list) == NULL);
    assert(linkedListPopBack(list) == NULL);

    freeList(list);
}

void testGetElement(void){
    LinkedList* list = createList();
    int a = 10, b = 20, c = 30, d = 40;

    linkedListPushBack(list, &a);
    linkedListPushBack(list, &b);
    linkedListPushBack(list, &c);
    linkedListPushBack(list, &d);

    assert(*(int*) linkedListGet(list, 0) == 10);
    assert(*(int*) linkedListGet(list, 1) == 20);
    assert(*(int*) linkedListGet(list, 2) == 30);
    assert(*(int*) linkedListGet(list, 3) == 40);

    assert(linkedListGet(list, 4) == NULL);
    assert(linkedListGet(list, 100) == NULL);
    assert(linkedListGet(NULL, 0) == NULL);

    freeList(list);
}

void testInsertAt(void){
    LinkedList* list = createList();
    int a = 10, b = 20, c = 30, d = 99;

    linkedListInsertAt(list, &a, 0);
    linkedListInsertAt(list, &c, 1);
    linkedListInsertAt(list, &b, 1);

    assert(*(int*) linkedListGet(list, 0) == 10);
    assert(*(int*) linkedListGet(list, 1) == 20);
    assert(*(int*) linkedListGet(list, 2) == 30);
    assert(listSize(list) == 3);

    linkedListInsertAt(list, &d, 1);
    assert(*(int*) linkedListGet(list, 1) == 99);
    assert(*(int*) linkedListGet(list, 2) == 20);
    assert(listSize(list) == 4);

    linkedListInsertAt(list, &d, 100);
    assert(listSize(list) == 4);

    freeList(list);
}

void testFind(void){
    LinkedList *list = createList();
    int a = 10, b = 20, c = 30, target = 20, missing = 50;

    linkedListPushBack(list, &a);
    linkedListPushBack(list, &b);
    linkedListPushBack(list, &c);

    int idx = linkedListFind(list, &target, compareInt);
    assert(idx == 1);

    int not_found = linkedListFind(list, &missing, compareInt);
    assert(not_found == -1);

    assert(linkedListFind(NULL, &target, compareInt) == -1);
    assert(linkedListFind(list, &target, NULL) == -1);

    freeList(list);
}

void calcSum(void* data){
    if(data) sum += *(int*) data;
}

void customFreeFunc(void* data){
    free(data);
}

int compareInt(const void* a, const void* b){
    if(!a || !b) return -1;
    const int* x = (const int*) a;
    const int* y = (const int*) b;

    if(*x < *y) return -1;
    if(*x > *y) return 1;
    return 0;
}
