#include "AGV.hpp"

AGV::AGV(const int id, const int current_pos) : id{id}, current_pos{current_pos}
{
    in_use = false;
}

void AGV::print_info()
{
    std::cout << "Current pos: " << this->current_pos << std::endl;
    std::cout << "AGVs ID: " << this->id << std::endl;

}

bool AGV::add_target(const unsigned int target)
{

}


