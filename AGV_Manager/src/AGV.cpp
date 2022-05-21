#include "AGV.hpp"

AGV::AGV(const int id, const int current_pos) : id{id}, current_pos{current_pos}
{
    in_use = false;
}

void AGV::print_info()
{
    std::cout << this->current_pos << std::endl;
    std::cout << this->id << std::endl;

}


