#include <iostream>
#include <functional>


template<class T, typename compare = std::less<T>>
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
            if(empty()){ //if queue is empty
                head = tail = temp;
                head->next = nullptr;
            }
            else{
                data_t* pt1 = head; 
                if(!evaluate(pt1->item, temp->item)){ //if item to be enqueued has a higher/lesser priority than head
                    temp->next = pt1; //head is replaced with new element
                    head = temp;
                }
                else{ //else we have to find the element, that will have same or lesser/higher priority than the one to be enqueued
                    while(pt1->next != nullptr && evaluate(pt1->next->item, temp->item)){
                        pt1 = pt1->next; //while pt1->next is not pointing to null and next item has higher/lesser priority 
                    }//continue the search
                    temp->next = pt1->next; //replace elements in queue
                    pt1->next = temp;
                }
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

void clr(){ //clear the input
    while(std::cin.get() != '\n'){
        continue;
    }
}

using data = struct{ //some random struct 
    std::string some_string;
    int id;
};
bool operator<(const data& d1, const data& d2){ //operator < defined to compare 2 different structs
    return d1.id < d2.id;
}
bool operator>(const data& d1, const data& d2){ //operator > (same as above)
    return !(d1 < d2);
}


int main(){
    using std::cout;
    using std::endl;
    using std::cin;
    data temp;
    PriorityQueue<data, std::greater<data>> data_queue(3);
    while(!data_queue.full()){
        cout << "Pass ID: ";
        cin >> temp.id;
        clr();
        cout << "Pass a string: ";
        getline(cin, temp.some_string);
        data_queue.enqueue(temp);
    }
    
    cout << "Items in queue: " << endl;

    while(!data_queue.empty()){
        data_queue.dequeue(temp);
        cout << "ID: " << temp.id << endl;
        cout << "String: " << temp.some_string << endl << endl;
    }
    return 0;
}