#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef unsigned int uint;

void quickSort(void* array, uint n, uint item_size, int (*compare)(const void*, const void*));

#endif