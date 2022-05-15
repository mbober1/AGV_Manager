#include "Stage.hpp"

Stage::Stage(const char * filename_warehouse, const char* filename_tasks, vehicle_num option)
{
    this->Warehouse_object= read_from_file(filename_warehouse);
    this->read_tasks_from_file(filename_tasks);
    std::cout << "opcja: " <<  option << std::endl;
    this->add_vehicles(option);
}

void Stage::print_info()
{
    this->Warehouse_object.print();
    for(const auto& it: this->tasks_to_do)
    {
        std::cout << "task id: " << it.task_id << " target: " << it.target << std::endl;
    }

    for(auto& it: this->AGV_vehicles)
    {
        it.print_info();
    }
}

bool Stage::read_tasks_from_file(const char * filename)
{   

    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "Stage::read_tasks_from_file: Problem with file opening \n";
        return false;
    }

    this->tasks_to_do.clear();
    Task temp_task;

    while(ReadFile >> temp_task.task_id && ReadFile >> temp_task.target)
    {
        this->tasks_to_do.push_back(temp_task);
    }

    ReadFile.close();

    return true;
}


void Stage::add_vehicles(vehicle_num option)
{
    
    for(auto i = 0; i < option; i++)
    {
        AGV temp_object(i, STAR_POSITION);
        AGV_vehicles.push_back(std::move(temp_object));
    }
}