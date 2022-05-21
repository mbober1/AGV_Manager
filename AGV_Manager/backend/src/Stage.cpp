#include "Stage.hpp"

Stage::Stage(const char * filename_warehouse, const char* filename_tasks, vehicle_num option)
{
    this->Warehouse_object= read_from_file(filename_warehouse);
    this->read_tasks_from_file(filename_tasks);
    this->add_vehicles(option);
}

void Stage::print_info()
{
/*     this->Warehouse_object.print();
    for(const auto& it: this->tasks_to_do)
    {
        std::cout << "task id: " << it.task_id << " target: " << it.target << std::endl;
    } */

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
    for(auto i = 1; i < option + 1; i++)
    {
        AGV temp_object(i, STAR_POSITION);
        AGV_vehicles.push_back(std::move(temp_object));
    }
}

void Stage::add_task_to_vehicle(int AGV_id)
{
    if(tasks_to_do.empty())
    {
        std::cerr << "Stage::add_task_to_vehicle: Lack of tasks to assign" << std::endl;
        
    }
    else
    {
        Task temp_task = tasks_to_do.front();
        std::list<int> temp_path=std::move(Warehouse_object.compute_path_Dijkstra(AGV_vehicles[AGV_id-1].return_current_pos(),temp_task.target));
        tasks_to_do.pop_front();
        if(!temp_path.empty())
            AGV_vehicles[AGV_id-1].add_task(temp_task,temp_path);
    }
}

void Stage::make_moves()
{
    for(auto& it: this->AGV_vehicles)
    {
        if(it.return_status())
        {
            it.make_move();
        }
        else
        {
            if(!this->tasks_to_do.empty())
            {
                add_task_to_vehicle(it.return_id());
                it.make_move();
            }
        }
    }
}



std::vector<int> Stage::return_current_positions()
{
    std::vector<int> current_pos;

    for(auto& it: this->AGV_vehicles)
    {
        current_pos.push_back(it.return_current_pos());
    }

    return current_pos;
}


std::vector<std::list<int>> Stage::return_paths()
{
    std::vector<std::list<int>> paths;

        for(auto& it: this->AGV_vehicles)
    {
        paths.push_back(it.return_path());
    }

    return paths;

}