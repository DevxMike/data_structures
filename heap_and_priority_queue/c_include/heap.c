#include "heap.h"
#include <stdlib.h>
#include <string.h>

heap_t* init_heap(size_t max){
    return NULL;
}
int heap_empty(const heap_t* heap){
    return heap->quantity == 0;
}
int heap_full(const heap_t* heap){
    return heap->quantity == heap->max;
}
int heap_push(heap_t* heap, const data_t* data){

    return 0;
}
data_t* heap_pop(heap_t* heap){
    return NULL;
}
void copy_data(data_t* d1, const data_t* d2){
    strcpy(d1->string, d2->string);
    d1->value = d2->value;
}
void swap_data(data_t* d1, data_t* d2){
    data_t temp;
    copy_data(&temp, d1);
    copy_data(d1, d2);
    copy_data(d2, &temp);
}