#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    void* data;
    int size;       // Number of elements currently in the vector
    int capacity;   // Vector total capacity
    int item_size;  // Number of bytes occupied by each item in the vector
} Vector;

Vector* vectorCreate(const unsigned int initial_capacity, const unsigned int item_size);
void vectorPushBack(Vector* vector, const void* value);
void* vectorGet(const Vector* vector, int index);
void vectorSet(const Vector* vector, int index, const void* value);
int vectorSize(const Vector* vector);
int vectorCapacity(const Vector* vector);
void vectorFree(Vector* vector);

#endif
