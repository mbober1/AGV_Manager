#include "inc/Stage.hpp"

Stage::Stage(const char * filename)
{
    this->Warehouse_object= read_from_file(filename);
}

void Stage::print_info()
{
    this->Warehouse_object.print();
}

bool Stage::read_tasks_from_file(const char * filename)
{
    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "Stage::read_tasks_from_file: Problem with file opening \n";
        return false;
    }

    return true;
}