#include <iostream>
#include "cpp_include/heap.h"
#include <ctime>
#include <stdlib.h>

int main(){
    std::srand(std::time(NULL));
    data_structures::heap<int> integer_heap(20);
    int temp;
    std::cout << "Before sort:\n";
    while(integer_heap.insert((temp = std::rand()%100))){
        std::cout << temp << " ";
    }
    std::cout << std::endl << "After sort:\n";
    while(integer_heap.extract(temp)){
        std::cout << temp << " ";
    }
    std::cout << std::endl << "end\n";
    return 0;
}