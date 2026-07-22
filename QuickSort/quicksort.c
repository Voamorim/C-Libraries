#include "quicksort.h"

void swap(void* a, void* b, uint item_size){
    char aux[item_size];
    memcpy(aux, a, item_size);
    memcpy(a, b, item_size); 
    memcpy(b, aux, item_size);
}

uint partition(void* array, int low, int high, uint item_size, int (*compare)(const void*, const void*)){
    char* bytes = (char*) array;
    int mid = (low + high) / 2;

    void* pivot = (void*) malloc (sizeof(char) * item_size);
    memcpy(pivot, bytes + mid * item_size, item_size);

    int i = low, j = high;
    while(true){
        void* item_i = bytes + i * item_size;
        while(compare(item_i, pivot) == -1){
            i += 1;
            item_i = bytes + i * item_size;
        }

        void* item_j = bytes + j * item_size;
        while(compare(item_j, pivot) == +1){
            j -= 1;
            item_j = bytes + j * item_size;
        }

        if(i >= j) {
            free(pivot);
            return j;
        }

        swap(item_i, item_j, item_size);
        i++, j--;
    }
}

void quickSortFunc(void* array, int low, int high, uint item_size, int (*compare)(const void*, const void*)){
    if(low < high){
        int pivot_idx = partition(array, low, high, item_size, compare);

        quickSortFunc(array, low, pivot_idx, item_size, compare);
        quickSortFunc(array, pivot_idx + 1, high, item_size, compare);
    }
}

void quickSort(void* array, uint n, uint item_size, int (*compare)(const void*, const void*)){
    if(!array){
        perror("[quicksort.c][quickSort()] ERROR: Invalid argument. Array can't be NULL.\n");
        return;
    }
    if(n == 0 || item_size == 0){
        perror("[quicksort.c][quickSort()] ERROR: Invalid argument. Array positions (`n`) or item size (`item_size`) can't be equal to 0.\n");
        return;
    }
    quickSortFunc(array, 0, n-1, item_size, compare);
}