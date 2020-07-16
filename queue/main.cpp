#include <iostream>
#include <string>

template<class T> //queue for types with defined operator=() 
class MyQueue{
private:
    std::size_t max; //size of queue
    std::size_t quantity; //actual quantity of elements
    typedef struct data_t{
        T item;
        data_t* next;
    }data_t;
    data_t* head;
    data_t* tail;
public:
    MyQueue(std::size_t max_size = 10):
        max(max_size), quantity(0), head(nullptr), tail(nullptr){}
    ~MyQueue();
    bool full()const;
    bool empty()const;
    bool enqueue(const T& data);
    bool dequeue(T& destination);
};
template<class T>
bool MyQueue<T>::full()const{ //if max equals to quantity of elements then queue is full
    return max == quantity;
}
template<class T>
bool MyQueue<T>::empty()const{ //if quantity equals to 0 then queue is empty
    return quantity == 0;
}
template<class T>
bool MyQueue<T>::enqueue(const T& data){
    if(full()){
        return false;
    }
    else{
        data_t* temp = new data_t; //newly allocated memory for our new element in queue
        temp->item = data; //copying the data
        temp->next = nullptr; //temp is the last element of queue

        if(head == nullptr){ //if queue is empty
            head = tail = temp;
        }
        else{
            tail->next = temp; //copying the data
            tail = tail->next;
        }
        ++quantity;
        return true;
    }
}
template<class T>
bool MyQueue<T>::dequeue(T& destination){
    if(empty()){
        return false;
    }
    else{
        data_t* temp = head; 
        head = head->next; //moving the queue to the next element
        destination = temp->item; //dequeue by reference
        delete temp; //delete unused memory
        --quantity;
        return true;
    }
}
template<class T>
MyQueue<T>::~MyQueue(){
    data_t* temp;
    while(head != nullptr){ //while there are elements in our queue
        temp = head; //get head address
        head = head->next; //move queue to the next element
        delete temp; //delete head
    } //while head points to a valid address
}

int main(){
    using std::cout;
    using std::endl;
    using std::cin;
    
    MyQueue<std::string> string_queue(4); //example of usage
    std::string temp;
    while(!string_queue.full()){
        cout << "Pass a string in: ";
        getline(cin, temp);
        string_queue.enqueue(temp);
    }

    cout << "Items in queue:" << endl;
    while(!string_queue.empty()){
        string_queue.dequeue(temp);
        cout << temp << endl;
    }
    
    return 0;
}