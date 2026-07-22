#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

void testVector();

int main(){
    srand(time(NULL));
    int tests = 5;

    while(tests--)
        testVector();

    puts("All tests completed successfully!");

    return 0;
}

void testVector(){
    const int n = 100;
    const int max_value = 1000;

    Vector* vector = vectorCreate(n, sizeof(int));

    assert(vectorCapacity(vector) == n);

    int* array = (int*) malloc (sizeof(int) * n);

    for(int i = 0; i < n; ++i){
        int value = rand() % max_value;
        vectorPushBack(vector, &value);
        array[i] = value;
    }
 
    for(int i = 0; i < n; ++i){
        int* value = (int*) vectorGet(vector, i);
        assert(*value == array[i]);
    }


    int updates = 20;
    while(updates--){
        int value = rand() % max_value;
        int pos = rand() % n;

        array[pos] = value;
        vectorSet(vector, pos, &value);
    }
    for(int i = 0; i < n; ++i){
        int* value = (int*) vectorGet(vector, i);
        assert(*value == array[i]);
    }

    int fills = 5; 
    while(fills--){
        int x = rand() % max_value;
        vectorFill(vector, &x);
        for(int i = 0; i < n; ++i)
            array[i] = x;
        
        for(int i = 0; i < n; ++i){
            int* value = (int*) vectorGet(vector, i);
            assert(*value == array[i]);
        }
    }

    assert(vectorSize(vector) == n);

    int erases = 10;
    int m = n;
    while(erases--){
        int pos = rand() % m;

        for(int i = pos + 1; i < m; ++i){
            array[i-1] = array[i];
        }
        m -= 1;

        vectorErase(vector, pos);

        for(int i = 0; i < m; ++i){
            int* value = (int*) vectorGet(vector, i);
            assert(*value == array[i]);
        }
    }

    vectorFree(vector);
    free(array);
}