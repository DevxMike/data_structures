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
    int size;
    int quantity;
    T* arr;
public:
    explicit MyStack(int stack_size = 10);
    ~MyStack(){
        delete[] arr;
    }
    bool push(const T& item);
    bool pop(T& destination);
    bool is_empty()const;
    bool is_full()const;
};

template<class T>
MyStack<T>::MyStack(int stack_size):
    size(stack_size), quantity(0){
    arr = new T[size];
}
template<class T>
bool MyStack<T>::is_empty()const{
    return quantity == 0;
}
template<class T>
bool MyStack<T>::is_full()const{
    return quantity == size;
}
template<class T>
bool MyStack<T>::push(const T& item){
    if(is_full()){
        return false;
    }
    else{
        arr[quantity++] = item;
        return true;
    }
}
template<class T>
bool MyStack<T>::pop(T& destination){
    if(is_empty()){
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
    int size;
    int quantity;
    char** arr;
public:
    explicit MyStack(int stack_size = 10);
    ~MyStack(){
        for(int i = 0; i < quantity; ++i){
            delete[] arr[i];
        }
        delete[] arr;
    }
    bool push(const char* item);
    char* pop();
    bool is_empty()const;
    bool is_full()const;
};

MyStack<const char*>::MyStack(int stack_size) :
    size(stack_size), quantity(0){
    arr = new char*[size];
}
bool MyStack<const char*>::is_empty()const{
    return quantity == 0;
}
bool MyStack<const char*>::is_full()const{
    return quantity == size;
}
bool MyStack<const char*>::push(const char* item){
    if(is_full()){
        return false;
    }
    else{
        arr[quantity] = new char[std::strlen(item) + 1];
        std::strcpy(arr[quantity++], item);
        return true;
    }
}
char* MyStack<const char*>::pop(){ //need to use delete[] on returned pt
    if(is_empty()){
        return nullptr;
    }
    else{
        char* destination = new char[std::strlen(arr[--quantity]) + 1];
        std::strcpy(destination, arr[quantity]);
        return destination;
    }
}

int main(){
    using std::cout;
    using std::endl;

    std::srand(std::time(NULL));

    MyStack<int> int_stack;
    int temp;
    
    while(!int_stack.is_full()){
        int_stack.push(std::rand() % 10);
    }
    std::vector<int> numbers;
    while(!int_stack.is_empty()){
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
        if(words_stack.is_full()) break;
        stream << x << " ";
        words_stack.push(stream.str().c_str());
    }
    
    cout << endl << "words stack: " << endl;
    char* pt;
    while(!words_stack.is_empty()){
        pt = words_stack.pop();
        cout << pt << endl;
        delete[] pt;
    }
    return 0;
}