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

    const char * file_name = "warehouse_layout.txt";

    Warehouse Warehouse_object = read_from_file(file_name);
    Warehouse_object.print();


    return 0;
}
