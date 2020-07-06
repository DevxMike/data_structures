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
    std::size_t size;
    std::size_t quantity;
    T* arr;
public:
    explicit MyStack(std::size_t stack_size = 10);
    ~MyStack(){
        delete[] arr;
    }
    bool push(const T& item);
    bool pop(T& destination);
    bool empty()const;
    bool full()const;
};

template<class T>
MyStack<T>::MyStack(std::size_t stack_size):
    size(stack_size), quantity(0), arr(new T[size]){}
template<class T>
bool MyStack<T>::empty()const{
    return quantity == 0;
}
template<class T>
bool MyStack<T>::full()const{
    return quantity == size;
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
    char** arr;
public:
    explicit MyStack(std::size_t stack_size = 10);
    ~MyStack(){
        for(std::size_t i = 0; i < quantity; ++i){
            delete[] arr[i];
        }
        delete[] arr;
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
        arr[quantity] = new char[std::strlen(item) + 1];
        std::strcpy(arr[quantity++], item);
        return true;
    }
}
bool MyStack<const char*>::pop(char*& destination){ //need to use delete[] on returned pt
    if(empty()){
        return false;
    }
    else{
        destination = new char[std::strlen(arr[--quantity]) + 1];
        std::strcpy(destination, arr[quantity]);
        delete[] arr[quantity];
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