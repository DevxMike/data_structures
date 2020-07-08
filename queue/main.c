#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int number; //some random data to be stored
    char string[40];
    data_t* next; //pointer to the next element 
}data_t;

typedef struct{
    size_t size; //max size of the queue
    size_t quantity; //elements stored in queue
    data_t* head; //pointer to the head of the queue
}queue_t;

bool enqueue(queue_t* queue, const data_t* element); //adds an element to our data structure
data_t* dequeue(queue_t* queue); //pops first element from queue and returns pointer to newly allocated memory
bool queue_empty(const queue_t* queue); //checks if queue is empty
bool queue_full(const queue_t* queue); //checks if queue is full

int main(void){

    return 0;
}