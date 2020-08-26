#ifndef heap_h
#define heap_h
#include <iostream>
#include <vector>
#include <initializer_list>

namespace data_structures{
    template<class T, class _cmp = std::greater<T>> 
    class heap{
        private:
            std::size_t max; //maximum elements quantity that can be on heap at once
            std::size_t quantity; //actual quantity of elements on heap
            T* arr; //pointer to array with elements
            bool cmp(const T& el1, const T& el2)const{ //method that compares elements (helps restoring the order on heap)
                _cmp compare;
                return compare(el1, el2);
            }
            void shift_up(unsigned index){ //restore order in heap after adding an element
                if(index > 0){ //while index is not a root index
                    if(cmp(arr[index], arr[(index - 1)/2])){ //if newly added element is greater/less than it`s parent
                        std::swap(arr[index], arr[(index - 1)/2]); //swap with parent
                        shift_up((index - 1) / 2); //check if order`s been restored, else continue swapping elements
                    }
                }
            }
            void shift_down(unsigned index, unsigned left, unsigned right){
                if(left < quantity && right < quantity){ //if element placed at index has 2 children
                    if(cmp(arr[left], arr[right])){ //check which of the children is greater/less
                        if(cmp(arr[left], arr[index])){ //check if new root is greater/less than it`s children
                            std::swap(arr[left], arr[index]); //swap elements if yes
                            shift_down(left, 2*left + 1, 2*left + 2); //continue checking the order in tree
                        }
                    }
                    else{
                        if(cmp(arr[right], arr[index])){ //same as above
                            std::swap(arr[right], arr[index]);
                            shift_down(right, 2*right + 1, 2*right + 2);
                        }
                    }    
                }
                else if(left < quantity){ //same as above, but no right child node
                    if(cmp(arr[left], arr[index])){
                        std::swap(arr[left], arr[index]);
                        shift_down(left, 2*left + 1, 2*left + 2);
                    } 
                }
            }
        public:
            heap(std::size_t _max = 50):
                quantity(0), max(_max), arr(new T[max]){}
            heap(std::initializer_list<T> list):
                quantity(0), max(list.size()), arr(new T[max]){
                    for(auto x : list){
                        insert(x);
                    }
                }
            ~heap(){
                delete[] arr;
            }
            bool empty()const{ //check if heap is empty
                return quantity == 0;
            }
            bool full()const{ //check if heap is full
                return quantity == max;
            }
            bool insert(const T& el){
                if(full()){ 
                    return false;
                }
                else{ //if heap is not full
                    arr[quantity] = el; //insert an element
                    shift_up(quantity++); //restore order in heap
                    return true;
                }
            }
            bool extract(T& el){
                if(empty()){
                    return false;
                }
                else{ //if heap is not empty
                    el = arr[0]; //return the root by reference
                    arr[0] = arr[--quantity]; //place the last element in the root place
                    shift_down(0, 1, 2); //restore order in heap
                    return true;
                }
            }
    };
};

#endif