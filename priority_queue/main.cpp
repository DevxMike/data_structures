#include <iostream>
#include <functional>


template<class T, typename compare = std::greater<T>>
class PriorityQueue{
private:
    std::size_t max; //max size of queue
    std::size_t quantity; //actual quantity of elements in queue
    typedef struct data_t{ 
        T item;
        data_t* next;
    }data_t;
    data_t* head; //pointer to the address of first element 
    data_t* tail;//pointer to the last element
    bool evaluate(const T& st, const T& nd)const{ //private method being used to evaluate the position of element i queue
        compare exp;
        return exp(st, nd);
    }
public:
    PriorityQueue(std::size_t max_size = 10):
        max(max_size), quantity(0), head(nullptr){} 
    ~PriorityQueue(){
        data_t* temp;
        while(head != nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    bool enqueue(const T& item){ //to do
        if(full()){
            return false;
        }
        else{
            data_t* temp = new data_t;
            temp->item = item;
            if(empty()){
                head = temp;
                head->next = nullptr;
            }
            else{
                
                
            }
            ++quantity;
            return true;
        }
    }
    bool dequeue(T& destination){ 
        if(empty()){
            return false;
        }
        else{
            data_t* temp = head; //temp pointer to head
            head = head->next; 
            destination = temp->item; //copy 1st element to destination
            delete temp; //delete the head
            --quantity;
            return true;
        }
    }
    bool empty()const{ //if quantity of elements equals to 0 then queue is empty
        return quantity == 0;
    }
    bool full()const{ //if max size of queue equals to actual quantity of elements then it is full
        return max == quantity;
    }
};

int main(){
    using std::cout;
    using std::endl;
    using std::cin;
    
    PriorityQueue<std::string, std::less<std::string>> string_queue(4); //example of usage
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