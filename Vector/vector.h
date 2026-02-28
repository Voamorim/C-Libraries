#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector{
    void* data;
    int size;      // Quantidade de elementos atualmente no vector
    int capacity;  // Capacidade total do vector
    int item_size; // Quantidade de bytes ocupados por cada item do vector
} Vector;

Vector* createVector(const int initial_capacity, const int item_size);
void vectorPushBack(Vector *vector, const void* value);
void* vectorGet(const Vector* vector, int index);
void vectorSet(const Vector* vector, int index, const void* value);
int vectorSize(const Vector* vector);
int vectorCapacity(const Vector* vector);
void freeVector(Vector *vector);

#endif
