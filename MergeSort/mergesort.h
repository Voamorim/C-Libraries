#ifndef MERGESORT_H
#define MERGESORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void mergeSort(void *data, const unsigned n, const unsigned item_size, int(*compare)(const void*, const void*));

#endif