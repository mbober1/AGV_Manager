#include "AGV.hpp"

AGV::AGV(const int id, const int current_pos) : id{id}, current_pos{current_pos}
{
    in_use = false;
}

void AGV::print_info()
{
    std::cout << "Current pos: " << this->current_pos << std::endl;
    std::cout << "AGVs ID: " << this->id << std::endl;
    std::cout << "Target: " << this->target << std::endl;
    std::cout << "Task perform percent: " << this->task_percent << std::endl;
    for(const auto & it: this->path_to_target)
    {
        std::cout << it << " "; 
    }
    std::cout << std::endl;

}

void AGV::add_task(const Task task_to_assign , const std::list<int> path_to_target)
{
    if(this->in_use == false)
    {
        this->target=task_to_assign.target;
        this->in_use = true;
        this->path_to_target.clear();
        this->path_to_target = std::move(path_to_target);
        this->road_length = path_to_target.size();
        this->task_percent = 0.0;
    }
    
}

void AGV::make_move()
{
    if(this->in_use == true)
    {
        this->current_pos = this->path_to_target.front();
        this->path_to_target.pop_front();
        this->task_percent = (1 - (float(this->path_to_target.size())/this->road_length))*100;
        if(current_pos == target)
        {
            in_use = false;
        }
    }
}


