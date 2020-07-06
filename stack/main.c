#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int id;
    char fname[20];
    char lname[20];
}data_t;

typedef struct{
    size_t size;
    size_t quantity;
    data_t* arr;
}stack_t;

void push(stack_t* stack, const data_t* data);
data_t* pop(stack_t* stack);
bool stack_full(const stack_t* stack);
bool stack_empty(const stack_t* stack);
void print_data(const data_t* data);
void free_stack(stack_t* stack);
void clear_in();


const char* menu_text = 
"[1].Push data to stack.\n"
"[2].Pop data from stack.\n"
"[3].Push data on stack to binary file.\n"
"[4].Load data from binary file to stack.\n"
"[5].End.\n";

int main(void){
    stack_t* data;
    unsigned temp;
    char c;

    printf("Pass the size of stack (size >= 1): ");
    while(scanf("%u", &temp) && temp < 1){
        printf("Pass valid size of stack: ");
    }
    data->size = temp;
    if((data->arr = (data_t*)malloc(sizeof(data_t) * data->size)) == NULL){
        printf("Failed to alloc memory.\n");
        exit(1);
    }
    else{
        printf("Memory allocated successfully.\n%s", menu_text);
        clear_in();
        while((c = getchar()) != '5'){
            clear_in();
            switch(c){
                case '1':
                break;
                case '2':
                break;
                case '3':
                break;
                case '4':
                break;
                default:
                    printf("Wrong character.\nTry again:");
                    continue;
                break;
            }
            printf("%s", menu_text);
        }
    }
    return 0;
}

void clear_in(){
    char c;
    while((c = getchar()) != '\n') 
        continue;
}