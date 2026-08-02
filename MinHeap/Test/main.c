#include "../minheap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

typedef struct Person {
    int priority;
    char name[20];
} Person;

int compareInt(const void *a, const void *b);
int comparePersons(const void *a, const void *b);

void testCreateEmptyAndInsert();
void testCreateFromArrayAndPop();
void testCustomStruct();
void testEdgeCasesAndErrorHandling();

int main(){
    srand(time(NULL));

    testCreateEmptyAndInsert();
    testCreateFromArrayAndPop();
    testCustomStruct();
    testEdgeCasesAndErrorHandling();    

    puts("All tests have passed!!!");

    return 0;
}

void testCreateEmptyAndInsert(){
    MinHeap* heap = createEmptyMinHeap(2, sizeof(int), compareInt);
    assert(heap != NULL);
    assert(heap->size == 0);

    int values[] = {50, 20, 30, 10, 5, 40};
    int num_values = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_values; i++) {
        minHeapInsert(heap, &values[i]);
    }

    assert(heap->size == num_values);
    assert(*(int*)minHeapTop(heap) == 5);

    destroyMinHeap(heap);
}

void testCreateFromArrayAndPop(){
    int values[] = {45, 12, 89, 3, 27, 60, 1};
    unsigned count = sizeof(values) / sizeof(values[0]);

    MinHeap* heap = createMinHeap(values, count, sizeof(int), compareInt);
    assert(heap != NULL);
    assert(heap->size == count);

    int expected[] = {1, 3, 12, 27, 45, 60, 89};
    for (unsigned i = 0; i < count; i++) {
        int* current_min = (int*)minHeapTop(heap);
        assert(*current_min == expected[i]);
        minHeapPop(heap);
    }

    assert(heap->size == 0);
    destroyMinHeap(heap);
}

void testCustomStruct(){
    MinHeap* heap = createEmptyMinHeap(4, sizeof(Person), comparePersons);

    Person p1 = {3, "Joao"};
    Person p2 = {1, "Lucas"};
    Person p3 = {2, "Pedro"};

    minHeapInsert(heap, &p1);
    minHeapInsert(heap, &p2);
    minHeapInsert(heap, &p3);

    Person* top_person = (Person*) minHeapTop(heap);
    assert(top_person->priority == 1);
    assert(strcmp(top_person->name, "Lucas") == 0);

    minHeapPop(heap);
    top_person = (Person*)minHeapTop(heap);
    assert(top_person->priority == 2);

    destroyMinHeap(heap);
}

void testEdgeCasesAndErrorHandling(){
    assert(createEmptyMinHeap(10, sizeof(int), NULL) == NULL);
    assert(createMinHeap(NULL, 5, sizeof(int), compareInt) == NULL);

    MinHeap* heap = createEmptyMinHeap(2, sizeof(int), compareInt);

    assert(minHeapTop(heap) == NULL);
    minHeapPop(heap);

    destroyMinHeap(heap);
}

int compareInt(const void *a, const void *b){
    int x = *(const int*) a;
    int y = *(const int*) b;

    if(x < y) return -1;
    else if (x > y) return 1;
    return 0;
}

int comparePersons(const void *a, const void *b){
    const Person* x = (const Person*) a;
    const Person* y = (const Person*) b;

    if(x->priority < y->priority) return -1;
    if(x->priority > y->priority) return 1;
    return 0;
}