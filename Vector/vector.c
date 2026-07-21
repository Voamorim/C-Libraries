#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector* vectorCreate(const unsigned int initial_capacity, const unsigned int item_size) {
    Vector* v = (Vector*)malloc(sizeof(Vector));

    if (v == NULL) {
        perror(
            "[vector.c][createVector()] ERROR: Failed to allocate memory for the vector "
            "structure.\n");
        return NULL;
    }

    v->size = 0;
    v->capacity = initial_capacity;
    v->item_size = item_size;

    v->data = malloc(initial_capacity * item_size);

    if (v->data == NULL) {
        perror(
            "[vector.c][createVector()] ERROR: Failed to allocate memory for the vector dada.\n");
        free(v);
        return NULL;
    }

    return v;
}

void vectorPushBack(Vector* vector, const void* value) {
    if (vector == NULL) {
        perror("[vector.c][vectorPushBack()] WARNING: Vector object does not exist.\n");
        return;
    }

    if (vector->size == vector->capacity) {
        vector->capacity = vector->capacity * 2 > 0 ? vector->capacity * 2 : 1;
        vector->data = realloc(vector->data, vector->capacity * vector->item_size);

        if (vector->data == NULL) {
            perror(
                "[vector.c][vectorPushBack()] ERROR: Failed to allocate memory for the vector "
                "items.\n");
            return;
        }
    }
    // Calculates the address to which the new element should be copied
    char* dest = (char*)vector->data + vector->size * vector->item_size;
    memcpy(dest, value, vector->item_size);
    vector->size += 1;
}

void* vectorGet(const Vector* vector, int index) {
    if (vector == NULL) {
        perror("[vector.c][vectorGet()] WARNING: Vector object does not exist.\n");
        return NULL;
    }

    if (index >= vector->size) {
        perror("[vector.c][vectorGet()] ERROR: Vector index out of bounds.\n");
        return NULL;
    }
    // Calculates the desired item address
    return (char*)vector->data + index * vector->item_size;
}

void vectorSet(Vector* vector, int index, const void* value) {
    if (vector == NULL) {
        perror("[vector.c][vectorSet()] WARNING: Vector object does not exist.\n");
        return;
    }

    if (index >= vector->size) {
        perror("[vector.c][vectorSet()] ERROR: Vector index out of bounds.\n");
        return;
    }
    // Calculates the to be modified item address
    char* dest = (char*)vector->data + index * vector->item_size;
    memcpy(dest, value, vector->item_size);
}

int vectorSize(const Vector* vector) {
    if (vector == NULL) {
        perror("[vector.c][vectorSize()] WARNING: Vector object does not exist.\n");
        return 0;
    }
    return vector->size;
}

int vectorCapacity(const Vector* vector) {
    if (vector == NULL) {
        perror("[vector.c][vectorCapacity()] WARNING: Vector object does not exist.\n");
        return 0;
    }
    return vector->capacity;
}

void vectorFree(Vector* vector) {
    if (vector == NULL) {
        perror("[vector.c][vectorFree()] WARNING: Vector object does not exist.\n");
        return;
    }

    free(vector->data);
    free(vector);
}
