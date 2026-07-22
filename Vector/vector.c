#include "vector.h"

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

    v->buffer = malloc(initial_capacity * item_size);

    if (v->buffer == NULL) {
        perror(
            "[vector.c][createVector()] ERROR: Failed to allocate memory for the vector dada.\n");
        free(v);
        return NULL;
    }

    return v;
}

void vectorPushBack(Vector* vector, void* value) {
    if (vector == NULL) {
        perror("[vector.c][vectorPushBack()] WARNING: Vector object does not exist.\n");
        return;
    }

    if (vector->size == vector->capacity) {
        vector->capacity = vector->capacity * 2 > 0 ? vector->capacity * 2 : 1;
        vector->buffer = realloc(vector->buffer, vector->capacity * vector->item_size);

        if (vector->buffer == NULL) {
            perror(
                "[vector.c][vectorPushBack()] ERROR: Failed to allocate memory for the vector "
                "items.\n");
            return;
        }
    }
    // Calculates the address to which the new element should be copied
    char* dest = (char*)vector->buffer + vector->size * vector->item_size;
    memcpy(dest, value, vector->item_size);
    vector->size += 1;
}

void* vectorGet(const Vector* vector, const unsigned int index) {
    if (vector == NULL) {
        perror("[vector.c][vectorGet()] WARNING: Vector object does not exist.\n");
        return NULL;
    }

    if (index >= vector->size) {
        perror("[vector.c][vectorGet()] ERROR: Vector index out of bounds.\n");
        return NULL;
    }
    // Calculates the desired item address
    return (char*)vector->buffer + index * vector->item_size;
}

void vectorSet(Vector* vector, const unsigned int index, void* value) {
    if (vector == NULL) {
        perror("[vector.c][vectorSet()] WARNING: Vector object does not exist.\n");
        return;
    }

    if (index >= vector->size) {
        perror("[vector.c][vectorSet()] ERROR: Vector index out of bounds.\n");
        return;
    }
    // Calculates the to be modified item address
    char* dest = (char*)vector->buffer + index * vector->item_size;
    memcpy(dest, value, vector->item_size);
}

void vectorErase(Vector* vector, const unsigned int index) {
    if (vector == NULL) {
        perror("[vector.c][vectorErase()] WARNING: Vector object does not exist.\n");
        return;
    }

    if (index >= vector->size) {
        printf("[vector.c][vectorErase()] ERROR: Vector index out of bounds.\n");
        return;
    }

    // Moves next items backwards
    for (unsigned i = index + 1; i < vector->size; ++i) {
        vectorSet(vector, i - 1, vector->buffer + vector->item_size * i);
    }

    vector->size -= 1;
}

void vectorFill(Vector* vector, void* value){
    if(vector == NULL || vector->buffer) {
        perror("[vector.c][vectorFill()] WARNING: Invalid argument. Vector object or buffer can't be NULL.\n");
        return;
    }

    if(!value){
        perror("[vector.c][vectorFill()] WARNING: Value pointer can't be NULL.\n");
        return;
    }

    char* destination = (char*) vector->buffer;
    for(unsigned i = 0; i < vector->capacity; ++i){
        memcpy(destination + (i * vector->item_size), value, vector->item_size);
    }

    vector->size = vector->capacity;
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

    free(vector->buffer);
    free(vector);
}
