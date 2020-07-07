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

void copy_data(data_t* destination, const data_t* source);
bool push(stack_t* stack, const data_t* data);
data_t* pop(stack_t* stack);
bool stack_full(const stack_t* stack);
bool stack_empty(const stack_t* stack);
void print_data(const data_t* data);
void clear_in();
int write_to_file(stack_t* stack, FILE* file);
int read_from_file(stack_t* stack, FILE* file, int* status, fpos_t* offset, bool* flag);
int fpeek(FILE* file);
void clear_struct(data_t* data);

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
    data_t* pop_pointer = NULL, temp_data;
    int status;
    FILE* file_out = NULL;
    FILE* file_in = NULL;
    fpos_t offset;
    bool flag = false;

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
                        clear_struct(&temp_data);
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
                        pop_pointer = NULL;
                    }
                    else{
                        printf("Stack is empty.\n");
                    }
                break;
                case '3':
                    if((file_out = fopen("default.dat", "ab")) == NULL){
                        printf("Failed while opening the file.\n");
                    }
                    else{
                        if(stack_empty(&stack)){
                            printf("Stack is empty.\n");
                        }
                        else{
                            printf("%d elements written into file.\n", write_to_file(&stack, file_out));
                        }
                        fclose(file_out);
                    }
                break;
                case '4':
                    if((file_in = fopen("default.dat", "rb")) == NULL){
                        printf("Failed while opening the file.\n");
                    }
                    else{
                        if(stack_full(&stack)){
                            printf("Stack full.\n");
                        }
                        else{
                            printf("%d elements read from file.\n", read_from_file(&stack, file_in, &status, &offset, &flag));
                            switch(status){
                                case 0:
                                    printf("End of file not reached.\n");
                                break;
                                case 1:
                                    printf("End of file reached.\n");
                                break;
                            }
                            fclose(file_in);
                        }
                    }
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
    data_t* temp = NULL;

    if(stack_full(stack)){
        return false;
    }
    else{
        temp = &stack->arr[stack->quantity++];
        copy_data(temp, data);
        return true;
    }
}

data_t* pop(stack_t* stack){
    data_t* temp = NULL, *pt = NULL;
    if(stack_empty(stack)){
        return NULL;
    }
    else{
        
        if((temp = (data_t*)malloc(sizeof(data_t) * 1)) == NULL){
            return NULL;
        }
        else{
            pt = &stack->arr[--stack->quantity];
            copy_data(temp, pt);
            clear_struct(pt);
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
void copy_data(data_t* destination, const data_t* source){
    if(destination != NULL && source != NULL){
        destination->id = source->id;
        strcpy(destination->fname, source->fname);
        strcpy(destination->lname, source->lname);
    }
}
int write_to_file(stack_t* stack, FILE* file){
    data_t* temp = NULL;
    int count = 0;
    
    while(!stack_empty(stack)){
        temp = pop(stack);
        fwrite(temp, sizeof(data_t), 1, file);
        free(temp);
        ++count;
    }
    return count;    
}
int read_from_file(stack_t* stack, FILE* file, int* status, fpos_t* offset, bool* flag){
    int count = 0;
    data_t temp;

    rewind(file);
    if(*flag){
        fsetpos(file, offset);
    }
    while(!stack_full(stack)){
        if(fpeek(file) == EOF){ 
            *status = 1;
            rewind(file);
            *flag = false;
            break;
        }
        fread(&temp, sizeof(data_t), 1, file);
        copy_data(&stack->arr[stack->quantity++], &temp);
        ++count;
    }
    fgetpos(file, offset);
    *status = *flag? 1 : 0;
    *flag = true;
    return count;
}
void clear_struct(data_t* data){
    for(int i = 0; i < STR_SIZE; ++i){
        data->fname[i] = data->lname[i] = '\0';
    }
    data->id = 0;
}
int fpeek(FILE* file){
    char c = getc(file);
    ungetc(c, file);

    return c;
}