#include "vector.h"
#include <stdlib.h>
#include <string.h>

Vector* createVector(const int initial_capacity, const int item_size){
    Vector* v = (Vector*) malloc (sizeof(Vector));

    if(v == NULL){
        printf("Erro ao alocar memoria para a estrutura vector.\n");
        return NULL;
    }

    v->size = 0;
    v->capacity = initial_capacity;
    v->item_size = item_size;

    v->data = malloc(initial_capacity * item_size);

    if(v->data == NULL){
        printf("Erro ao alocar memoria para os dados do vector.\n");
        free(v);
        return NULL;
    }

    return v;
}

void vectorPushBack(Vector *vector, const void *value){
    if(vector->size == vector->capacity){
        vector->capacity = vector->capacity * 2 > 0 ? vector->capacity * 2 : 1;
        vector->data = realloc(vector->data, vector->capacity * vector->item_size);

        if(vector->data == NULL){
            printf("Erro ao alocar memoria para os itens do vector.\n");
            exit(1);
        }
    }
    // Calcula o endereço para o qual o novo elemento deve ser copiado
    char *dest = (char*) vector->data + vector->size * vector->item_size;
    memcpy(dest, value, vector->item_size);
    vector->size += 1;
}

void* vectorGet(const Vector *vector, int index){
    if(index >= vector->size){
        printf("Erro: indice fora dos limites do vector.\n");
        exit(1);
    }
    // Calcula o endereço do elemento desejado
    return (char*) vector->data + index * vector->item_size;
}

void vectorSet(Vector* vector, int index, const void *value){
    if(index >= vector->size){
        printf("Erro: indice fora dos limites do vector.\n");
        exit(1);
    }
    // Calcula o endereço do elemento a ser modificado
    char* dest = (char*) vector->data + index * vector->item_size;
    memcpy(dest, value, vector->item_size);
}

int vectorSize(const Vector *vector){
    return vector->size;
}

int vectorCapacity(const Vector *vector){
    return vector->capacity;
}

void freeVector(Vector *vector){
    free(vector->data);
    free(vector);
}

