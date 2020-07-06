#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STR_SIZE 20

typedef struct{
    int id;
    char fname[STR_SIZE];
    char lname[STR_SIZE];
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
    stack_t stack; 
    unsigned temp;
    char c;
    data_t* pop_pointer, temp_data;

    printf("Pass the size of stack (size >= 1): ");
    while(scanf("%u", &temp) && temp < 1){
        printf("Pass valid size of stack: ");
    }
    stack.size = temp;
    if((stack.arr = (data_t*)malloc(sizeof(data_t) * stack.size)) == NULL){
        printf("Failed to alloc memory.\n");
        exit(1);
    }
    else{
        printf("Memory allocated successfully.\n%s", menu_text);
        stack.quantity = 0;
        clear_in();
        while((c = getchar()) != '6'){
            clear_in();
            switch(c){
                case '1':
                    if(!stack_full(&stack)){
                        printf("Pass the data.\nID: ");
                        scanf("%d", &temp_data.id);
                        printf("First name: ");
                        clear_in();
                        scanf("%19s", temp_data.fname);
                        clear_in();
                        printf("Last name: ");
                        scanf("%19s", temp_data.lname);
                        clear_in();
                        push(&stack, &temp_data);
                    }
                    else{
                        printf("Stack full.\n");
                    }
                break;
                case '2':
                    if(!stack_empty(&stack)){
                        pop_pointer = pop(&stack);
                        print_data(pop_pointer);
                        free(pop_pointer);
                    }
                    else{
                        printf("Stack is empty.\n");
                    }
                break;
                case '3':
                break;
                case '4':
                break;
                case '5':
                    printf("-- Stack --\n");
                    printf("size: %5zu\n", stack.size);
                    printf("elem: %5zu\n", stack.quantity);
                    printf("-----------\n\n");
                break;
                default:
                    printf("Wrong character.\nTry again:");
                    continue;
                break;
            }
            printf("%s", menu_text);
        }
        free(stack.arr);
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
    data_t* temp, *pt;
    if(stack_empty(stack)){
        return NULL;
    }
    else{
        
        if((temp = (data_t*)malloc(sizeof(data_t) * 1)) == NULL){
            return NULL;
        }
        else{
            pt = &stack->arr[--stack->quantity];
            temp->id = pt->id;
            strcpy(temp->fname, pt->fname);
            strcpy(temp->lname, pt->lname);
            return temp;
        }
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