#include "../segtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

void mergeSum(void*, const void *a, const void *b);
void mergeMin(void*, const void *a, const void *b);
void updateSum(void *a, const void *b);
void updateMin(void *a, const void *b);

int min(int a, int b);
int max(int a, int b);

int calcSum(int* array, int l, int r);
int calcMin(int* array, int l, int r);

void testMinSegtree();
void testSumSegtree();

int main(){
    srand(time(NULL));

    testMinSegtree();
    testSumSegtree();

    return 0;
}

int calcSum(int* array, int l, int r){
    int ans = 0;
    for(int k = l; k <= r; ++k){
        ans += array[k];
    }
    return ans;
}

int calcMin(int* array, int l, int r){
    int ans = INT_MAX;
    for(int k = l; k <= r; ++k){
        ans = min(ans, array[k]);
    }
    return ans;
}

void testMinSegtree(){
    const int n = 100;
    const int max_val = 1000;

    int tests = 20;
    int neutral = INT_MAX;

    int* array = (int*) malloc (sizeof(int) * n);

    while(tests--){
        int queries = 20;
        for(int i = 0; i < n; ++i){
            int val = rand() % max_val;
            array[i] = val;
        }

        SegTree *segtree = segtreeCreate(n, sizeof(int), &neutral, mergeMin, updateMin);
        segtreeBuild(segtree, array, 0, n - 1, 1);

        while(queries--){
            float type_query = (float) rand() / (float) RAND_MAX;
            float point = (float) rand() / (float) RAND_MAX;

            // Ask
            if(type_query < 0.5){
                int i = (rand() % n);

                if(point < 0.5){ // Point query
                    int min_val = calcMin(array, i, i);

                    int smin;
                    segtreeQuery(segtree, &smin, i, i, 0, n-1, 1);

                    assert(min_val == smin);
                } else { // Range query
                    int j = (rand() % n);
                    int aux = i;
                    i = min(i, j);
                    j = max(aux, j);
                    
                    int min_val = calcMin(array, i, j);

                    int smin;
                    segtreeQuery(segtree, &smin, i, j, 0, n-1, 1);

                    assert(min_val == smin);
                }
            } else { // Update
                int i = (rand() % n);
                int new_val = (rand() % max_val);

                if(point < 0.5){ // Point update 
                    array[i] = new_val;
                    segtreeUpdate(segtree, i, i, &new_val, 0, n-1, 1);
                } else { // Range update 
                    int j = (rand() % n);
                    int aux = i;
                    i = min(i, j);
                    j = max(aux, j);

                    for(int k = i; k <= j; ++k){
                        array[k] = new_val;
                    }
                    segtreeUpdate(segtree, i, j, &new_val, 0, n-1, 1);
                }
            }
        }
        segtreeFree(segtree);
    }

    free(array);
    puts("All Min SegTree tests passed successfully!\n");
}

void testSumSegtree(){
    const int n = 100;
    const int max_val = 1000;

    int tests = 20;
    int neutral = 0;

    int* array = (int*) malloc (sizeof(int) * n);

    while(tests--){
        int queries = 20;
        for(int i = 0; i < n; ++i){
            int val = rand() % max_val;
            array[i] = val;
        }

        SegTree *segtree = segtreeCreate(n, sizeof(int), &neutral, mergeSum, updateSum);
        segtreeBuild(segtree, array, 0, n - 1, 1);

        while(queries--){
            float type_query = (float) rand() / (float) RAND_MAX;
            float point = (float) rand() / (float) RAND_MAX;

            // Ask
            if(type_query < 0.5){
                int i = (rand() % n);

                if(point < 0.5){ // Point query
                    int sum = calcSum(array, i, i);

                    int smin;
                    segtreeQuery(segtree, &smin, i, i, 0, n-1, 1);

                    assert(sum == smin);
                } else { // Range query
                    int j = (rand() % n);
                    int aux = i;
                    i = min(i, j);
                    j = max(aux, j);
                    
                    int sum = calcSum(array, i, j);

                    int smin;
                    segtreeQuery(segtree, &smin, i, j, 0, n-1, 1);

                    assert(sum == smin);
                }
            } else { // Update
                int i = (rand() % n);
                int new_val = (rand() % max_val);

                if(point < 0.5){ // Point update 
                    array[i] += new_val;
                    segtreeUpdate(segtree, i, i, &new_val, 0, n-1, 1);
                } else { // Range update 
                    int j = (rand() % n);
                    int aux = i;
                    i = min(i, j);
                    j = max(aux, j);

                    for(int k = i; k <= j; ++k){
                        array[k] += new_val;
                    }
                    segtreeUpdate(segtree, i, j, &new_val, 0, n-1, 1);
                }
            }
        }
        segtreeFree(segtree);
    }

    free(array);
    puts("All Sum SegTree tests passed successfully!\n");
}

void mergeSum(void* dest, const void *a, const void *b){
    int* x = (int*) a;
    int* y = (int*) b;

    int result = (*x) + (*y);
    memcpy(dest, &result, sizeof(int));

    return;
}

void mergeMin(void* dest, const void *a, const void *b){
    int* x = (int*) a;
    int* y = (int*) b;

    int ans = (*x) < (*y) ? (*x) : (*y);
    memcpy(dest, &ans, sizeof(int));

    return;
}

void updateSum(void *a, const void *b){
    int* x = (int*) a;
    int* y = (int*) b;

    int ans = *x + *y;
    memcpy(a, &ans, sizeof(int));
}

void updateMin(void *a, const void *b){
    memcpy(a, b, sizeof(int));
}

int min(int a, int b){
    if(a < b) return a;
    return b;
}

int max(int a, int b){
    if(a > b) return a;
    return b;
}