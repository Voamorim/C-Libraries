#include "minheap.h"

void minHeapify(MinHeap* min_heap, const unsigned index);
void _swap(void* a, void* b, const unsigned item_size);

MinHeap* createMinHeap(void* data, unsigned size, unsigned item_size, int(*compare)(const void*, const void*)){
    if(!data || !size){
        fprintf(stderr, "[ERROR] createMinHeap: Invalid data pointer or size 0.\n");
        return NULL;
    }

    if(!compare){
        fprintf(stderr, "[ERROR] createMinHeap: Comparator function pointer is NULL.\n"); 
        return NULL;
    }

    MinHeap* min_heap = (MinHeap*) malloc (sizeof(MinHeap));
    if(!min_heap){
        fprintf(stderr, "[ERROR] createMinHeap: Memory allocation failed for heap data structure.\n");
        return NULL;
    }

    min_heap->capacity = size * 2;
    min_heap->item_size = item_size;
    min_heap->size = size;
    min_heap->compare = compare;

    min_heap->data = (void*) malloc (item_size * min_heap->capacity);
    if(!min_heap->data){
        fprintf(stderr, "[ERROR] createMinHeap(): Memory allocation failed for heap data structure buffer.\n");
        free(min_heap);
        return NULL;
    }

    memcpy(min_heap->data, data, item_size * size);

    if(size > 0){
        for(int i = (int) (size / 2) - 1; i >= 0; --i){
            minHeapify(min_heap, (unsigned) i);
        }
    }
    return min_heap;
}

MinHeap* createEmptyMinHeap(unsigned capacity, unsigned item_size, int(*compare)(const void*, const void*)){
    if(!compare){
        fprintf(stderr, "[ERROR] createEmptyMinHeap: Comparator function pointer is NULL.\n");
        return NULL;
    }

    MinHeap *min_heap = (MinHeap*) malloc (sizeof(MinHeap));
    if(!min_heap){
        fprintf(stderr, "[ERROR] createEmptyMinHeap: Memory allocation failed for heap data structure.\n");
        return NULL;
    }
    min_heap->data = (void*) malloc (item_size * capacity);
    if(!min_heap->data){
        fprintf(stderr, "[ERROR] createEmptyMinHeap: Memory allocation failed for heap data structure buffer.\n");
        free(min_heap);
        return NULL;
    }

    min_heap->capacity = capacity;
    min_heap->size = 0;
    min_heap->item_size = item_size;
    min_heap->compare = compare;

    return min_heap;
}

void minHeapInsert(MinHeap* min_heap, void* value){
    if(!min_heap || !min_heap->data){
        fprintf(stderr, "[WARNING] minHeapInsert: MinHeap or underlying data is NULL.\n");
        return;
    }

    if(min_heap->size == min_heap->capacity){
        unsigned new_capacity = min_heap->capacity == 0 ? 1 : min_heap->capacity * 2;

        void* temp = realloc(min_heap->data, min_heap->item_size * new_capacity);
        if(!min_heap->data){
            fprintf(stderr, "[ERROR] minHeapInsert: Reallocation failed when expanding heap capacity.\n");
            return;
        }

        min_heap->capacity = new_capacity;
        min_heap->data = temp;
    }

    char* end_pos = (char*) min_heap->data + (min_heap->item_size * min_heap->size);
    memcpy(end_pos, value, min_heap->item_size);
    min_heap->size += 1;

    int i = (int) min_heap->size - 1;
    if(i <= 0) return;

    char* parent = (char*) min_heap->data + (min_heap->item_size * ((i - 1) / 2 ));
    char* curr = (char*) min_heap->data + (min_heap->item_size * i);

    while(min_heap->compare(parent, curr) == 1){
        _swap(parent, curr, min_heap->item_size);
        i = (i - 1) / 2;

        if(i <= 0) break;

        parent = (char*) min_heap->data + (min_heap->item_size * ((i - 1) / 2 ));
        curr = (char*) min_heap->data + (min_heap->item_size * i);
    }
}

void minHeapPop(MinHeap* min_heap){
    if(!min_heap || !min_heap->data){
        fprintf(stderr, "[WARNING] minHeapPop: MinHeap or underlying data is NULL.\n");
        return;
    }

    if(!min_heap->size){
        fprintf(stderr, "[WARNING] minHeapPop: Attempted to pop from an empty heap\n");
        return;
    }

    char* last_element = (char*) min_heap->data + (min_heap->size-1) * min_heap->item_size;
    char* top_element = (char*) min_heap->data;

    _swap(last_element, top_element, min_heap->item_size);
    min_heap->size -= 1;

    minHeapify(min_heap, 0);
}

void* minHeapTop(MinHeap* min_heap){
    if(!min_heap || !min_heap->data){
        fprintf(stderr, "[WARNING] minHeapTop: MinHeap or underlying data is NULL.\n");
        return NULL;
    }

    if(!min_heap->size){
        fprintf(stderr, "[WARNING] minHeapTop: Heap is empty.\n");
        return NULL;
    }
    return min_heap->data;
}

void destroyMinHeap(MinHeap* min_heap){
    if(!min_heap) return;
    if(min_heap->data) free(min_heap->data);
    free(min_heap);
}

void minHeapify(MinHeap* min_heap, const unsigned index){
    if(!min_heap || !min_heap->data) return;

    void* curr = (char*) min_heap->data + (index * min_heap->item_size);
    void* smallest = curr; 
    unsigned smallest_idx = index;

    unsigned l = 2 * index + 1;
    unsigned r = 2 * index + 2;

    if(l >= min_heap->size) return;

    void* l_child = (char*) min_heap->data + (l * min_heap->item_size);
    if(min_heap->compare(l_child, smallest) < 0){
        smallest = l_child;        
        smallest_idx = l;
    }

    if(r < min_heap->size){
        void *r_child = (char*) min_heap->data + (r * min_heap->item_size);
        if(min_heap->compare(r_child, smallest) < 0){
            smallest = r_child;        
            smallest_idx = r;
        }
    } 

    if(smallest_idx != index){
        _swap(curr, smallest, min_heap->item_size);
        minHeapify(min_heap, smallest_idx);
    }
}

void _swap(void* a, void* b, const unsigned item_size){
    char aux[item_size];
    memcpy(aux, a, item_size);
    memcpy(a, b, item_size);
    memcpy(b, aux, item_size);
}