#pragma once

#include "Warehouse.hpp"
#include "AGV.hpp"
#include "Stage.hpp"
#include <map>
#include <utility>


enum class Point_State
{
    Free,
    Reserved
};


using status_path = std::list<std::pair< Point_State, int>>;


/*
 * Class to handle collision protection. Created according to:
 * "Dynamic Resource Reservation Based Collision and Deadlock Prevention for Multi-AGVs"
 * source: https://ieeexplore.ieee.org/document/9081905
 *
 */
class TraficSystemControl{

status_path points_with_status;
public:


    TraficSystemControl(Warehouse & warehouse);


    bool go_ahead() {return true;}
    void print();


};
