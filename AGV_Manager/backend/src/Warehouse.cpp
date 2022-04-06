#include "Warehouse.hpp"


Warehouse::Warehouse(const unsigned int x, const unsigned int y): Matrix_layout_p{std::make_unique<IntMatrix>(x,y)}
{

}


void Warehouse::print()
{
    Matrix_layout_p->print();
}


Warehouse::Warehouse(const unsigned int x, const unsigned int y, std::vector<int> input_data): 
                                                                Matrix_layout_p{std::make_unique<IntMatrix>(x,y)}
{
    if(!Matrix_layout_p->insert_data(input_data))
    {
        std::cerr << "Warehouse: Problem with writing data to matrix \n";
        exit(-1);
    } 
}




/*
 * method reading data to matrix from file
 */
bool read_from_file(const char * filename);