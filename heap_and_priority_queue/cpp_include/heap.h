#ifndef heap_h
#define heap_h
#include <iostream>
#include <vector>
#include <initializer_list>

namespace data_structures{
    template<class T, class _cmp = std::greater<T>>
    class heap{
        private:
            std::size_t max;
            std::size_t quantity;
            T* arr;
            bool cmp(const T& el1, const T& el2)const{
                _cmp compare;
                return compare(el1, el2);
            }
            void shift_up(unsigned index){
                if(index > 0){
                    if(cmp(arr[index], arr[(index - 1)/2])){
                        std::swap(arr[index], arr[(index - 1)/2]);
                        shift_up((index - 1) / 2);
                    }
                }
            }
            void shift_down(unsigned index, unsigned left, unsigned right){
                if(left < quantity && right < quantity){
                    if(cmp(arr[left], arr[right])){
                        if(cmp(arr[left], arr[index])){
                            std::swap(arr[left], arr[index]);
                            shift_down(left, 2*left + 1, 2*left + 2);
                        }
                    }
                    else{
                        if(cmp(arr[right], arr[index])){
                            std::swap(arr[right], arr[index]);
                            shift_down(right, 2*right + 1, 2*right + 2);
                        }
                    }    
                }
                else if(left < quantity){ //no right child node
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
            bool empty()const{
                return quantity == 0;
            }
            bool full()const{
                return quantity == max;
            }
            bool insert(const T& el){
                if(full()){
                    return false;
                }
                else{
                    arr[quantity] = el;
                    shift_up(quantity++);
                    return true;
                }
            }
            bool extract(T& el){
                if(empty()){
                    return false;
                }
                else{
                    el = arr[0];
                    arr[0] = arr[--quantity];
                    shift_down(0, 1, 2);
                    return true;
                }
            }
    };
    
    template<class T, class _cmp = std::greater<T>>
    class priority_queue : private heap<T, _cmp>{
        private:
        public:
    };
};

#endif