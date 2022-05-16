#include "AGV.hpp"

AGV::AGV(const int id, const int current_pos) : id{id}, current_pos{current_pos}
{
    in_use = false;
}

void AGV::print_info()
{
    std::cout << "Current pos: " << this->current_pos << std::endl;
    std::cout << "AGVs ID: " << this->id << std::endl;
    
    for(const auto & it: this->path_to_target)
    {
        std::cout << it << " "; 
    }

}

void AGV::add_task(const Task task_to_assign , const std::list<int> path_to_target)
{
    if(this->in_use == false)
    {
        this->target=task_to_assign.target;
        this->in_use = true;
        this->path_to_target.clear();
        this->path_to_target = std::move(path_to_target);
    }
    
}

void AGV::make_move()
{
    if(this->in_use == true)
    {
        current_pos = path_to_target.front();
        path_to_target.pop_front();
                        std::cout << "tu" << std::endl;

        if(current_pos == target)
        {
            in_use = false;
        }
    }
}


