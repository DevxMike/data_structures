#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct{ //definition of struct that stores our data
    int number; //some random data to be stored
    char string[40];
}data_t; //just change this definition, copy_data() and print_struct() for other uses

typedef struct queue_data_t{
    data_t data;
    struct queue_data_t* next; //pointer to the next element 
}queue_data_t;

typedef struct{
    size_t size; //max size of the queue
    size_t quantity; //elements stored in queue
    queue_data_t* head; //pointer to the head of the queue
    queue_data_t* tail; //pointer to the last element of the queue
}queue_t;

bool enqueue(queue_t* queue, const data_t* element); //adds an element to our data structure
data_t* dequeue(queue_t* queue); //pops first element from queue and returns pointer to newly allocated memory
bool queue_empty(const queue_t* queue); //checks if queue is empty
bool queue_full(const queue_t* queue); //checks if queue is full
void copy_data(data_t* destination, const data_t* source); //copies the data
void print_struct(const data_t* data); //prints data
void free_queue(queue_t* queue);

int main(void){
    int i = 0, j;
    queue_t queue = {3, 0, NULL}; //queue init
    data_t s[5] = {
        {1, "customer 1"},
        {2, "customer 2"},
        {3, "customer 3"},
        {4, "customer 4"},
        {5, "customer 5"}
    }, *temp;

    printf("Adding customers to a queue.\n");
    while(enqueue(&queue, &s[i++])){
        continue;
    }
    printf("Added %d customers, processing!\n", --i);
    while((temp = dequeue(&queue)) != NULL){
        print_struct(temp);
        free(temp);
    }
    printf("Adding the rest of customers to a queue.\n");
    for(j = i; j < 5; ++j){
        enqueue(&queue, &s[j]);
    }
    printf("Added %d customers, processing!\n", j - i);
    while((temp = dequeue(&queue)) != NULL){
        print_struct(temp);
        free(temp);
    }
    free_queue(&queue);
    return 0;
}

bool enqueue(queue_t* queue, const data_t* element){
    queue_data_t* temp = NULL;

    if(queue_full(queue)){ //if queue is full, we can`t push an element to it`s end
        return false;
    }
    else{
        if((temp = (queue_data_t*) malloc(sizeof(queue_data_t))) == NULL){
            return false;
        }
        else{
            temp->next = NULL; //that`s the last element of queue
            copy_data(&temp->data, element); //copy data 
            if(queue->head == NULL){ //if head is equal to NULL val then the element to be enqueued is our new head
                queue->head = queue->tail = temp; 
            }
            else{
                queue->tail->next = temp;
                queue->tail = queue->tail->next;
            }
            ++queue->quantity; 
            return true;
        }
    }
}

data_t* dequeue(queue_t* queue){
    data_t* temp = NULL;
    queue_data_t* pt = NULL;

    if(queue_empty(queue)){ //if queue is empty, the element can`t be taken down from the queue
        return NULL;
    }
    else{
        if((temp = (data_t*) malloc(sizeof(data_t))) == NULL){
            return NULL;
        }
        else{
            copy_data(temp, &queue->head->data); //copy data to newly allocated memory
            pt = queue->head; //delete old head
            queue->head = pt->next;
            free(pt); //free allocated memory (not used anymore)
            --queue->quantity;
            return temp; //return data
        }
    }
}
bool queue_empty(const queue_t* queue){
    return queue->quantity == 0; //if quantity of elements in queue is equal to 0 then queue is empty
}
bool queue_full(const queue_t* queue){
    return queue->size == queue->quantity; //if quantity of elements in queue is equal to it`s size then queue is full
}
void copy_data(data_t* destination, const data_t* source){
    destination->number = source->number; 
    strcpy(destination->string, source->string);
}
void print_struct(const data_t* data){
    printf("ID: %d\nString: %s\n", data->number, data->string);
}
void free_queue(queue_t* queue){
    queue_data_t* temp = NULL;

    if(!queue_empty(queue)){
        while(queue->head != NULL){
            temp = queue->head;
            queue->head = temp->next;
            free(temp);
        }
    }
}