#ifndef heap_h
#define heap_h
#include <stdio.h>
#define LEN 20

typedef struct{
    char string[LEN];
    int value;
}data_t;

typedef struct{
    size_t quantity;
    size_t max;
    data_t* arr;
    int (*compare)(const data_t*, const data_t*);
}heap_t;

typedef enum{
    less = 0,
    greater
}heap_cmp;

heap_t* init_heap(size_t);
int heap_empty(const heap_t*);
int heap_full(const heap_t*);
int heap_push(heap_t*, const data_t*);
data_t* heap_pop(heap_t*);
void copy_data(data_t*, const data_t*);
#endif