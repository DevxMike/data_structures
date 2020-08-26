#include <stdio.h>
#include <stdlib.h>
#include "c_include/heap.h"
#define QUANTITY 6

data_t test[QUANTITY] = {
    {"Coding is great!", 5},
    {"I <3 C/C++!", 6},
    {"AVR is good", 1},
    {"STM is very cool!", 0},
    {"ARM rocks!", 7},
    {"Sysdev for life!", 4}
};

int main(void){
    heap_t* heap1 = init_heap(QUANTITY, less_el);
    heap_t* heap2 = init_heap(QUANTITY, greater_el);
    data_t* temp = NULL;
    printf("Before sort:\n\n");
    for(temp = test; temp < test + QUANTITY; ++temp){
        print_data(temp);
        heap_push(heap1, temp);
        heap_push(heap2, temp);
    }
    printf("\nSorting by strings in structs.\n");
    printf("\nAfter sort (ASC):\n\n");
    while((temp = heap_pop(heap1)) != NULL){
        print_data(temp);
        free(temp);
    }
    printf("\nAfter sort (DESC):\n\n");
    while((temp = heap_pop(heap2)) != NULL){
        print_data(temp);
        free(temp);
    }
    free(heap1->arr);
    free(heap1);
    free(heap2->arr);
    free(heap2);
    return 0;
}