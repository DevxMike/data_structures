#include "heap.h"
#include <stdlib.h>
#include <string.h>

int greater(const data_t* d1, const data_t* d2){
    if(strcmp(d1->string, d2->string) >= 0){ //if first string is greater return 1
        return 1;
    }
    else{
        return 0; //else return 0
    }
}

int less(const data_t* d1, const data_t* d2){
    return !greater(d1, d2); //return opposite of greater() result  
}

heap_t* init_heap(size_t max, heap_cmp cmp){
    heap_t* temp_heap = NULL;
    data_t* temp_data = NULL;
    if(((temp_heap = (heap_t*)malloc(sizeof(heap_t))) == NULL) || ((temp_data = (data_t*)malloc(sizeof(data_t)* max)) == NULL)){ //if memory allocation failed
        return NULL;
    }
    else{
        temp_heap->arr = temp_data; //set struct data
        temp_heap->quantity = 0;
        temp_heap->max = max;
        
        if(cmp == less_el || cmp == greater_el){ //to avoid errors
            temp_heap->compare = (cmp == less_el? less : greater); //set compare function
        }
        else{
            temp_heap->compare = greater;
        }

        return temp_heap;
    }
}
int heap_empty(const heap_t* heap){ //return 1 if heap is empty 
    return heap->quantity == 0;
}
int heap_full(const heap_t* heap){ //return 1 if heap is full
    return heap->quantity == heap->max;
}
void shift_up(heap_t* heap, unsigned index){
    if(index > 0){ //while index is not an index of root
        if(heap->compare(&heap->arr[index], &heap->arr[(index - 1) / 2])){ //if condition is met
            swap_data(&heap->arr[index], &heap->arr[(index - 1) / 2]); //swap data
            shift_up(heap, (index - 1) / 2); //go up the tree
        }
    }
}
int heap_push(heap_t* heap, const data_t* data){
    if(heap_full(heap)){ //if heap is full return 0
        return 0;
    }
    else{
        copy_data(&heap->arr[heap->quantity], data); //insert data as last element on heap
        shift_up(heap, heap->quantity++); //restore heap`s order
        return 1;
    }
}
void shift_down(heap_t* heap, unsigned index, unsigned left, unsigned right){

}
data_t* heap_pop(heap_t* heap){
    data_t* temp = NULL;
    
    if((temp = (data_t*)malloc(sizeof(data_t))) == NULL){ //if memory alloc failed
        return NULL;
    }
    else{
        copy_data(temp, &heap->arr[--heap->quantity]); //else copy struct 
        shift_down(heap, 0, 1, 2); //restore heap`s order
        return temp;
    }
}
void copy_data(data_t* d1, const data_t* d2){ //copy struct
    strcpy(d1->string, d2->string);
    d1->value = d2->value;
}
void swap_data(data_t* d1, data_t* d2){ //swap 2 structs
    data_t temp;
    copy_data(&temp, d1);
    copy_data(d1, d2);
    copy_data(d2, &temp);
}
void print_data(const data_t* data){ //print struct data
    printf("%19s\t%13s\n%19s\t%13d\n",
        "String:",
        "Integer val:",
        data->string,
        data->value
    );
}