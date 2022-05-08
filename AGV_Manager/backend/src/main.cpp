#include <iostream>
#include <memory>
#include "Warehouse.hpp"

int main(){

    const char * file_name = "warehouse_1.txt";

    Warehouse Warehouse_object = read_from_file(file_name);
    Warehouse_object.print();

    Warehouse_object.compute_path_Dijkstra(0, 48);


    return 0;
}
