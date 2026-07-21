#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

int listIsEmpty(const LinkedList* list) {
    return list == NULL || list->head == NULL || list->size == 0;
}

int listSize(const LinkedList* list) { return list == NULL ? 0 : list->size; }

LinkedList* createList(void) {
    // Cria uma nova lista encadeada e insere um nó inicial nela
    LinkedList* new_list = (LinkedList*)malloc(sizeof(LinkedList));

    // Verifica se foi possível alocar memória para a lista encadeada
    if (new_list == NULL) {
        printf("Erro ao alocar memoria para lista encadeada.");
        return NULL;
    }

    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

void freeList(LinkedList* list) {
    // Verifica se a lista já se encontra vazia
    if (list == NULL) return;

    struct ListNode* curr = list->head;
    struct ListNode* next;

    // Realiza a remoção dos nós a partir do início
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    free(list);
}

void freeListComplete(LinkedList* list, void (*freeData)(void*)) {
    // Verifica se a função passada é válida
    if (freeData == NULL) {
        printf("Erro. A funcao passada nao e valida.\n");
        return;
    }

    // Verifica se a lista já se encontra vazia
    if (list == NULL) return;

    struct ListNode* curr = list->head;
    struct ListNode* next;

    while (curr != NULL) {
        next = curr->next;

        // Verifica se o dado armazenado existe
        if (curr->data != NULL) freeData(curr->data);

        free(curr);
        curr = next;
    }

    free(list);
}

void linkedListPushBack(LinkedList* list, void* data) {
    struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));

    // Verifica se o novo nó foi alocado com sucesso
    if (new_node == NULL) {
        printf("Erro ao alocar memoria para um novo no.\n");
        return;
    }

    struct ListNode* curr = list->tail;

    // Verifica se existe algum nó na lista
    if (curr) {
        curr->next = new_node;

        new_node->data = data;
        new_node->next = NULL;
        new_node->previous = curr;

        list->tail = new_node;

        list->size += 1;
    } else {
        // Caso a lista não possua nó cabeça, é chamada linkedListPushFront para
        // fazer a inserção no início

        free(new_node);  // Libera o nó alocado anteriormente
        linkedListPushFront(list, data);
    }
}

void linkedListPushFront(LinkedList* list, void* data) {
    struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));

    // Verifica se a memória foi alocada com sucesso para o novo nó
    if (new_node == NULL) {
        printf("Erro ao alocar memoria para um novo no.\n");
        return;
    }

    new_node->previous = NULL;  // Nó cabeça não possui antecessor
    new_node->data = data;

    // Verifica se a lista possuí um nó cabeça
    if (list->head) {
        new_node->next = list->head;
        list->head->previous = new_node;
        list->head = new_node;

    } else {
        // Caso não tenha nó cabeça, insere o primeiro nó na lista
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
    }

    list->size += 1;
}

void* linkedListPopFront(LinkedList* list) {
    if (listIsEmpty(list)) {
        printf("Erro ao tentar remover em uma lista vazia.\n");
        return NULL;
    }

    struct ListNode* curr = list->head;
    list->head = list->head->next;

    // Verifica se o posterior ao nó cabeça existe
    if (list->head != NULL) {
        // Faz com que o novo nó cabeça não aponte para nenhum anterior
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
    // Verifica se a lista está vazia
    if (listIsEmpty(list)) {
        printf("Erro ao remover no da lista. A lista esta vazia.\n");
        return NULL;
    }

    struct ListNode* curr = list->tail;

    // Verifica se o último nó da lista possui antecessor
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
    // Verifica se a lista está vazia
    if (listIsEmpty(list)) {
        printf("Erro ao tentar remover no da lista. A lista esta vazia.\n");
        return NULL;
    }

    struct ListNode* curr;

    // Caso o nó a ser removido esteja entre dois nós existentes
    if (target->next && target->previous) {
        // Faz os nós entre o nó a ser removido apontarem um para o outro
        curr = target->next;
        target->previous->next = curr;
        curr->previous = target->previous;

    } else if (target->next) {
        // Se o nó a ser removido apenas possuir posterior, ele é o nó cabeça
        list->head = target->next;
        list->head->previous = NULL;
    } else if (target->previous) {
        // Se o nó a ser removido possuir apenas anterior, ele é o nó final
        // da lista
        target->previous->next = NULL;
        list->tail = target->previous;
    } else {
        // Caso o nó não possuir antecessor nem posterior, ele é o último nó
        // da lista
        list->head = NULL;
    }

    void* data = target->data;

    free(target);
    list->size -= 1;

    return data;
}

void linkedListForEach(const LinkedList* list, void (*func)(void*)) {
    // Verifica se a lista está vazia ou se a função é inválida
    if (listIsEmpty(list) || func == NULL) {
        printf("Erro. A lista esta vazia ou a funcao passada e invalida.\n");
        return;
    }

    struct ListNode* curr = list->head;

    // Itera sobre os nós da lista executando a função
    while (curr != NULL) {
        func(curr->data);
        curr = curr->next;
    }
}
