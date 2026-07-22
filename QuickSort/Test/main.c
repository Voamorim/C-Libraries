#include "../quicksort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Pair{
    int first;
    int second;
} Pair;

int comparePair(const void* a, const void* b){
    Pair* x = (Pair*) a;
    Pair* y = (Pair*) b;

    if(x->first > y->first){
        return 1;
    } else if (x->first < y->first){
        return -1;
    } 

    if(x->second > y->second){
        return 1;
    } else if (x->second < y->second){
        return -1;
    }

    return 0;
}

bool compareArraysPair(Pair* v, Pair* w, int n, int m){
    if(n != m) return false;

    for(int i = 0; i < n; ++i){
        void* a = v + i; 
        void* b = w + i;

        if(comparePair(a, b) != 0){ 
            printf("Mismatch at position %d\n", i);
            return false;
        }
    }
    return true;
}

int main(){
    srand(time(NULL));

    int n = 100;

    Pair* array = (Pair*) malloc (sizeof(Pair) * n);
    Pair* v = (Pair*) malloc (sizeof(Pair) * n);
    Pair* w = (Pair*) malloc (sizeof(Pair) * n);

    int tests = 50;

    const int weight = 100;
    while(tests--){
        for(int i = 0; i < n; ++i){
            array[i].first = ((float) rand() / (float) RAND_MAX) * weight;
            array[i].second = ((float) rand() / (float) RAND_MAX) * weight;
        }    

        memcpy(v, array, n * sizeof(Pair));
        memcpy(w, array, n * sizeof(Pair));

        qsort(v, n, sizeof(Pair), comparePair);
        quickSort(w, n, sizeof(Pair), comparePair);

        bool comparison = compareArraysPair(v, w, n, n);
        assert(comparison == true);
    }

    puts("quickSort() works properly.\n");

    free(v), free(w), free(array);
    return 0;
}