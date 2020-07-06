#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

bool push(stack_t* stack, const data_t* data);
data_t* pop(stack_t* stack);
bool stack_full(const stack_t* stack);
bool stack_empty(const stack_t* stack);
void print_data(const data_t* data);
void clear_in();


const char* menu_text = 
"[1].Push data to stack.\n"
"[2].Pop data from stack.\n"
"[3].Push data on stack to binary file.\n"
"[4].Load data from binary file to stack.\n"
"[5].Stack info.\n"
"[6].End.\n";

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
        data->quantity = 0;
        clear_in();
        while((c = getchar()) != '6'){
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
                case '5':
                    printf("-- Stack --\n");
                    printf("size: %5zu\n", data->size);
                    printf("elem: %5zu\n", data->quantity);
                    printf("-----------\n\n");
                break;
                default:
                    printf("Wrong character.\nTry again:");
                    continue;
                break;
            }
            printf("%s", menu_text);
        }
        free(data->arr);
    }
    return 0;
}

void clear_in(){
    char c;
    while((c = getchar()) != '\n') 
        continue;
}
bool push(stack_t* stack, const data_t* data){
    data_t* temp;

    if(stack_full(stack)){
        return false;
    }
    else{
        temp = &stack->arr[stack->quantity++];
        temp->id = data->id;
        strcpy(temp->fname, data->fname);
        strcpy(temp->lname, data->lname);
        return true;
    }
}

data_t* pop(stack_t* stack){
    if(stack_empty(stack)){
        return NULL;
    }
    else{
        
    }
}
bool stack_full(const stack_t* stack){
    return stack->size == stack->quantity;
}
bool stack_empty(const stack_t* stack){
    return stack->quantity == 0;
}
void print_data(const data_t* data){
    printf("id: %d\nfirst name: %s\nlast name: %s\n", data->id, data->fname, data->lname);
}