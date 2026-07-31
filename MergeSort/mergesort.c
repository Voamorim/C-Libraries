#include "mergesort.h"

void _merge(void *data, const unsigned left, const unsigned right, const unsigned item_size, int(*compare)(const void*, const void*)){
    unsigned mid = (left + right) / 2;

    unsigned nL = mid - left + 1, nR = right - mid;

    char L[nL * item_size];
    char R[nR * item_size];

    memcpy(L, data + left * item_size, item_size * nL);
    memcpy(R, data + (mid + 1) * item_size, item_size * nR);

    unsigned i = left;
    unsigned iL = 0, iR = 0; 
    char *pos, *L_val, *R_val;
    while(iL < nL && iR < nR){
        pos = (char*) data + i * item_size;
        L_val = (char*) L + iL * item_size;
        R_val = (char*) R + iR * item_size;

        if(compare(L_val, R_val) <= 0){
            memcpy(pos, L_val, item_size);
            iL += 1;
        } else {
            memcpy(pos, R_val, item_size);
            iR += 1;
        }
        i += 1;
    }

    while(iL < nL){
        pos = (char*) data + i * item_size;
        L_val = (char*) L + iL * item_size;
        memcpy(pos, L_val, item_size);
        iL += 1;
        i += 1;
    }

    while(iR < nR){
        pos = (char*) data + i * item_size;
        R_val = (char*) R + iR * item_size;
        memcpy(pos, R_val, item_size);
        iR += 1;
        i += 1;
    }
}

void _mergeSort(void *data, const unsigned left, const unsigned right, const unsigned item_size, int(*compare)(const void*, const void*)){
    if(left >= right) return;

    unsigned mid = (left + right) / 2;

    _mergeSort(data, left, mid, item_size, compare);
    _mergeSort(data, mid + 1, right, item_size, compare);
    _merge(data, left, right, item_size, compare);
}

void mergeSort(void *data, const unsigned n, const unsigned item_size, int(*compare)(const void*, const void*)){
    _mergeSort(data, 0, n-1, item_size, compare);
}