#ifndef LISTA_H
#define LISTA_H

typedef struct ListNode {
    void *data;
    struct ListNode *next;
    struct ListNode *previous;
} ListNode;

typedef struct LinkedList {
    struct ListNode *head;
    struct ListNode *tail;
    int size;
} LinkedList;

// Retorna se a lista está vazia ou não
int listIsEmpty(const LinkedList *list);

// Retorna o tamanho da lista
int listSize(const LinkedList *list);

// Cria e retorna uma lista encadeada vazia
LinkedList* createList(void);

// Libera a memória de todos os nós da lista encadeada
// Não libera a memória dos dados apontados pelos nós
void freeList(LinkedList *list);

// Libera a memória de todos os nós da lista encadeada
// A função passada deve liberar a memória dos dados guardados nos nós
void freeListComplete(LinkedList *list, void (*freeData)(void*));

// Insere um novo nó no final da lista
void linkedListPushBack(LinkedList *list, void *data);

// Insere um novo nó ao início da lista
void linkedListPushFront(LinkedList *list, void *data);

// Remove o nó cabeça da lista e retorna um ponteiro para o dado que estava
// armazenado
// Não libera a memória dos dados apontados pelo nó
void* linkedListPopFront(LinkedList *list);

// Remove o nó ao final da lista e retorna um ponteiro para o dado que estava
// armazenado
// Não libera a memória dos dados apontados pelo nó
void* linkedListPopBack(LinkedList *list);

// Remove um nó em específico da lista
// Não libera a memória dos dados apontados pelo nó
void* linkedListPopNode(LinkedList *list, struct ListNode *target);

// Itera sobre todos os nós da lista executando a função passada como parâmetro
void linkedListForEach(const LinkedList *list, void(*func)(void*));

#endif
