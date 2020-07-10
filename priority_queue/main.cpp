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
    bool evaluate(const data_t* st, const data_t* nd)const{ //private method being used to evaluate the position of element i queue
        compare exp;
        return exp(st->item, nd->item);
    }
public:
    PriorityQueue(std::size_t max_size = 10):
        max(max_size), quantity(0), head(nullptr) {} 
    ~PriorityQueue(){}
    bool enqueue(const T& item){ //to do
        if(full()){
            return false;
        }
        else{

            return true;
        }
    }
    bool dequeue(T& destination){ //to do
        if(empty()){
            return false;
        }
        else{

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

    return 0;
}