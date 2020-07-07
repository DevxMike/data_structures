#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STR_SIZE 20

typedef struct{ //definition of type to be stored
    int id;
    char fname[STR_SIZE];
    char lname[STR_SIZE];
}data_t;

typedef struct{ //definition of stack type
    size_t size;
    size_t quantity;
    data_t* arr;
}stack_t;

void copy_data(data_t* destination, const data_t* source); //function able to copy data_t structs
bool push(stack_t* stack, const data_t* data); //function used to push an element onto stack
data_t* pop(stack_t* stack); //function used to pop an element from stack
bool stack_full(const stack_t* stack); //checks if the stack is full
bool stack_empty(const stack_t* stack); //checks if stack is empty
void print_data(const data_t* data); //prints a single structure
void clear_in(); //function useful to clear stdin buff after input operations
int write_to_file(stack_t* stack, FILE* file); //function used to write the whole stack to binary file
int read_from_file(stack_t* stack, FILE* file, int* status, fpos_t* offset, bool* flag); //function useful to read data from binary file 
                                                                                         //till stack is full or EOF is reached
int fpeek(FILE* file); // returns 1 byte from file (1 byte behind the file pointer, directed towards the EOF)
void clear_struct(data_t* data); //useful to fill the whole struct data_t fields with 0 values

const char* menu_text = 
"[1].Push data to stack.\n"
"[2].Pop data from stack.\n"
"[3].Push data on stack to binary file.\n"
"[4].Load data from binary file to stack.\n"
"[5].Stack info.\n"
"[6].End.\n";

int main(void){
    stack_t stack; //stack variable
    unsigned temp; //temporary variable used to store size of the stack
    char c; //character used to store the user choice
    data_t* pop_pointer = NULL, temp_data; //pointer used to store pop() return value, struct used to store temp data which has to be pushed onto stack
    int status; //variable used to store the file status
    FILE* file_out = NULL; //file_out pointer
    FILE* file_in = NULL; //file_in pointer
    fpos_t offset; //information about current position in file used to read
    bool flag = false; //helpful to set position in file being read

    printf("Pass the size of stack (size >= 1): ");
    while(scanf("%u", &temp) && temp < 1){
        printf("Pass valid size of stack: ");
    }
    stack.size = temp;
    if((stack.arr = (data_t*)malloc(sizeof(data_t) * stack.size)) == NULL){ //if allocation of the memory used to store data on the stack after failed
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
                    if(!stack_full(&stack)){ //if the stack is not full we can push an element 
                        clear_struct(&temp_data); //we get the data into the temporary data_t variable
                        printf("Pass the data.\nID: ");
                        scanf("%d", &temp_data.id);
                        printf("First name: ");
                        clear_in();
                        scanf("%19s", temp_data.fname);
                        clear_in();
                        printf("Last name: ");
                        scanf("%19s", temp_data.lname);
                        clear_in();
                        push(&stack, &temp_data); //then the data is being pushed onto stack
                    }
                    else{
                        printf("Stack full.\n");
                    }
                break;
                case '2':
                    if(!stack_empty(&stack)){ //if the stack is not empty
                        pop_pointer = pop(&stack); //we can pop the data from it  
                        print_data(pop_pointer); //the data is being printed
                        free(pop_pointer); //and previously allocated memory is beeing freed
                        pop_pointer = NULL;
                    }
                    else{
                        printf("Stack is empty.\n");
                    }
                break;
                case '3':
                    if((file_out = fopen("default.dat", "ab")) == NULL){ //if file is not opened
                        printf("Failed while opening the file.\n");
                    }
                    else{ //else if opened
                        if(stack_empty(&stack)){
                            printf("Stack is empty.\n");
                        }
                        else{
                            printf("%d elements written into file.\n", write_to_file(&stack, file_out)); //write data on stack to file
                        }
                        fclose(file_out); //close the file
                    }
                break;
                case '4':
                    if((file_in = fopen("default.dat", "rb")) == NULL){ //if the file is not opened
                        printf("Failed while opening the file.\n");
                    }
                    else{ //else if opened
                        if(stack_full(&stack)){
                            printf("Stack full.\n");
                        }
                        else{
                            printf("%d elements read from file.\n", read_from_file(&stack, file_in, &status, &offset, &flag)); //read the data
                            switch(status){ //and display some additional info
                                case 0:
                                    printf("End of file not reached.\n");
                                break;
                                case 1:
                                    printf("End of file reached.\n");
                                break;
                            }
                            fclose(file_in); //close the file
                        }
                    }
                break;
                case '5': //print simple info about stack
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
    while((c = getchar()) != '\n') //I think there is no need to explain that
        continue;
}

bool push(stack_t* stack, const data_t* data){
    data_t* temp = NULL; //temporary pointer

    if(stack_full(stack)){ 
        return false;
    }
    else{ //if stack is not full
        temp = &stack->arr[stack->quantity++]; //use temp as a pointer to our destination on stack
        copy_data(temp, data); //copy data from source (data passed as argument) to destination (temp)
        return true;
    }
}

data_t* pop(stack_t* stack){
    data_t* temp = NULL, *pt = NULL; //temporary pointers
    if(stack_empty(stack)){
        return NULL;
    }
    else{
        
        if((temp = (data_t*)malloc(sizeof(data_t) * 1)) == NULL){ //if allocation failed
            return NULL;
        }
        else{ //if not
            pt = &stack->arr[--stack->quantity]; //use pt as pointer to struct which will be our source
            copy_data(temp, pt); //copy data from source (pt) to destination (temp)
            clear_struct(pt); //fill *pt fields wtih 0 
            return temp; //return allocated memory address
        }
    }
}
bool stack_full(const stack_t* stack){
    return stack->size == stack->quantity; //if quantity equals to max size of stack then it is full
}
bool stack_empty(const stack_t* stack){
    return stack->quantity == 0; //if quantity equals 0 then stack is empty
}
void print_data(const data_t* data){
    printf("id: %d\nfirst name: %s\nlast name: %s\n", data->id, data->fname, data->lname); //print data
}
void copy_data(data_t* destination, const data_t* source){
    if(destination != NULL && source != NULL){
        destination->id = source->id; //copy id
        strcpy(destination->fname, source->fname); //copy strings
        strcpy(destination->lname, source->lname);
    }
}
int write_to_file(stack_t* stack, FILE* file){ 
    data_t* temp = NULL; //variable used to get the result of pop() return value
    int count = 0; 
    
    while(!stack_empty(stack)){ //while stack is not empty
        temp = pop(stack); //pop data from stack
        fwrite(temp, sizeof(data_t), 1, file); //write one struct to file
        free(temp); //free the memory allocated by pop() function
        ++count;
    }
    return count; //return count of written structs into the file 
}
int read_from_file(stack_t* stack, FILE* file, int* status, fpos_t* offset, bool* flag){
    int count = 0; //variable used to store quantity of items read from file
    data_t temp; //temporary struct used to read data from file

    rewind(file); //set file position to beginning
    if(*flag){ //if the flag is set
        fsetpos(file, offset); //set the position of file
                               //else it has to begin from beginning of the file
    }
    while(!stack_full(stack)){ //while the charakter after the file pointer is not a an EOF char and the stack is not full
        if(fpeek(file) == EOF){ 
            *status = 1; //set status var to 1
            rewind(file); //set file position to beginning
            *flag = false; //set flag to false
            break;
        }
        fread(&temp, sizeof(data_t), 1, file); //read one struct from binary file
        copy_data(&stack->arr[stack->quantity++], &temp); //copy data from temporary variable to stack struct stored in an array
        ++count;
    }
    fgetpos(file, offset); //get position of file
    *status = *flag? 0 : 1; //set status 
    *flag = true; //set flag to true, because position is yet set and status indirectly returned
    return count; //return count of read structs
}
void clear_struct(data_t* data){
    for(int i = 0; i < STR_SIZE; ++i){
        data->fname[i] = data->lname[i] = '\0'; //fill the char arrays with \0 char
    }
    data->id = 0; //set id to 0
}
int fpeek(FILE* file){
    char c = getc(file); //get a character
    ungetc(c, file); //and when stored in a variable push it back into file

    return c;
}