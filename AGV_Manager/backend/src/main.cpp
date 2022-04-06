#include <iostream>
#include <memory>
#include "Warehouse.hpp"

int main(){

    std::cout << "example of 2d matrix" << std::endl;
    
    std::vector<int> data_to_send;

    for(auto i = 0; i < 100; i++)
    {
        data_to_send.push_back(i);
    }

    const int N = 10;
    const int M = 10;
    Warehouse Warehouse_object(N,M, data_to_send);
    Warehouse_object.print();


    return 0;
}
