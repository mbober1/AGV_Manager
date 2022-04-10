#include "Warehouse.hpp"


Warehouse::Warehouse(const unsigned int x, const unsigned int y): Matrix_layout_p{std::make_unique<IntMatrix>(x,y)}
{

}


void Warehouse::print()
{
    Matrix_layout_p->print();
}


void Warehouse::insert_data_matrix( std::vector<int> input_data)
{
    if(!Matrix_layout_p->insert_data(input_data))
    {
        std::cerr << "Warehouse: Problem with writing data to matrix \n";
        exit(-1);
    } 
}

bool Warehouse::add_sizes(const unsigned int x, const unsigned int y)
{
    if(this->Matrix_layout_p != nullptr)
        return false;
    
    this->Matrix_layout_p = std::make_unique<IntMatrix>(x,y);
    return true;
}




Warehouse read_from_file(const char * filename)
{
    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "read_from_file: Problem with file opening \n";
        exit(-1);
    }
    
    std::vector<int> data_buff;
    unsigned int x_size, y_size, temp_var;

    ReadFile >> x_size >> y_size;
    Warehouse WarehouseObj(x_size, y_size);

    while(!ReadFile.eof())
    {
        ReadFile >> temp_var;
        data_buff.push_back(temp_var);
    }

    if(data_buff.size() != x_size*y_size)
    {
        std::cerr << "read_from_file: Problem with declared size and amount of data \n";
        exit(-1);
    }

    WarehouseObj.insert_data_matrix(data_buff);
    return WarehouseObj;
}