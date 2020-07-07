#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>

template<class T> //stack for types with defined operator=()
class MyStack{
private:
    std::size_t size; //max size of the stack
    std::size_t quantity; //actual size of stack
    T* arr; //pointer to array of stack elements
public:
    explicit MyStack(std::size_t stack_size = 10); //stack constructor
    ~MyStack(){ 
        delete[] arr; //delete array of values
    }
    bool push(const T& item); //add an element
    bool pop(T& destination); //pop an element from stack
    bool empty()const; //check whether stack is empty
    bool full()const; //-||- is full
};

template<class T>
MyStack<T>::MyStack(std::size_t stack_size):
    size(stack_size), quantity(0), arr(new T[size]){}
template<class T>
bool MyStack<T>::empty()const{
    return quantity == 0; //if the actual size of stack equals 0 then it is empty
}
template<class T>
bool MyStack<T>::full()const{
    return quantity == size; //if actual size of stack equals its maximal size then it is full
}
template<class T>
bool MyStack<T>::push(const T& item){
    if(full()){
        return false;
    }
    else{
        arr[quantity++] = item;
        return true;
    }
}
template<class T>
bool MyStack<T>::pop(T& destination){
    if(empty()){
        return false;
    }
    else{
        destination = arr[--quantity];
        return true;
    }
}

template<>
class MyStack<const char*>{//const char* type stack
private:
    std::size_t size;
    std::size_t quantity;
    char** arr; //if we want to store this type on stack, we simply need a matrix (pointer to array of pointers)
public:
    explicit MyStack(std::size_t stack_size = 10);
    ~MyStack(){
        for(std::size_t i = 0; i < quantity; ++i){//delete arrays
            delete[] arr[i];
        }
        delete[] arr; //delete array of previously deleted pointers
    }
    bool push(const char* item);
    bool pop(char*& destination);
    bool empty()const;
    bool full()const;
};

MyStack<const char*>::MyStack(std::size_t stack_size) :
    size(stack_size), quantity(0), arr(new char*[size]){}
bool MyStack<const char*>::empty()const{
    return quantity == 0;
}
bool MyStack<const char*>::full()const{
    return quantity == size;
}
bool MyStack<const char*>::push(const char* item){
    if(full()){
        return false;
    }
    else{
        arr[quantity] = new char[std::strlen(item) + 1]; //allocate a new array of lenght of the C string + 1 (for a NULL char)
        std::strcpy(arr[quantity++], item); //copy string to newly allocated memory
        return true;
    }
}
bool MyStack<const char*>::pop(char*& destination){ //need to use delete[] on returned pt
    if(empty()){
        return false;
    }
    else{
        destination = new char[std::strlen(arr[--quantity]) + 1]; //allocate memory which will be pointed by argument passed to the method
        std::strcpy(destination, arr[quantity]); //copy string
        delete[] arr[quantity]; //delete not used memory
        return true;
    }
}
int main(){
    using std::cout;
    using std::endl;

    std::srand(std::time(NULL)); 

    MyStack<int> int_stack;
    int temp;
    
    while(!int_stack.full()){
        int_stack.push(std::rand() % 10);
    }
    std::vector<int> numbers;
    while(!int_stack.empty()){
        int_stack.pop(temp);
        numbers.push_back(temp);
    }
    cout << "int stack: " << endl;
    std::for_each(numbers.begin(),
        numbers.end(), [](int n){
        cout << n << endl;
    });
    
    MyStack<const char*> words_stack;
    std::stringstream stream;
    stream << "word";
    for(auto x : numbers){
        if(words_stack.full()) break;
        stream << x << " ";
        words_stack.push(stream.str().c_str());
    }
    
    cout << endl << "words stack: " << endl;
    char* pt;
    while(!words_stack.empty()){
        words_stack.pop(pt);
        cout << pt << endl;
        delete[] pt;
    }
    return 0;
}