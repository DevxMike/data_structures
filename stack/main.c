#include <stdio.h>

typedef struct{
    int id;
    char fname[20];
    char lname[20];
    data_t* previous;
}data_t;

typedef struct{
    size_t size;
    size_t quantity;
    data_t* head;
}stack_t;

int main(void){
    return 0;
}