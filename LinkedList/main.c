#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void printInt(void* data) { printf("%d\n", *(int*)data); }

void testForEach() {
    LinkedList* list = createList();
    int values[] = {5, 10, 15};

    for (int i = 0; i < 3; i++) {
        linkedListPushBack(list, &values[i]);
    }

    linkedListForEach(list, printInt);  // Deve imprimir 5, 10, 15
    freeList(list);
}

int main() {
    LinkedList* list = createList();
    int values[] = {10, 20, 30};

    for (int i = 0; i < 3; i++) {
        linkedListPushBack(list, &values[i]);
    }

    // Remove o segundo nó (valor 20)
    ListNode* target = list->head->next;
    linkedListPopNode(list, target);

    assert(listSize(list) == 2);
    assert(list->head->data == &values[0]);
    assert(list->tail->data == &values[2]);

    freeList(list);

    testForEach();

    return 0;
}
