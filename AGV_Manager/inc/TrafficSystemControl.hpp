#pragma once

#include "Warehouse.hpp"
#include "inc/AGV.hpp"
#include <map>
#include <utility>


enum class Point_State
{
    Free,
    Reserved
};

using status_points = std::list<std::pair< Point_State, int>>;
using shared_points = std::vector<std::list<int>>;
using AGVs =  std::vector<AGV>;
/*
 * Class to handle collision protection. Created according to:
 * "Dynamic Resource Reservation Based Collision and Deadlock Prevention for Multi-AGVs"
 * source: https://ieeexplore.ieee.org/document/9081905
 *
 */
class TrafficSystemControl{

status_points points_with_status;
AGVs AGVs_vector;
shared_points shared_points_vector;



public:


    TrafficSystemControl(Warehouse  &warehouse, AGVs &AGVs_vector);


    bool go_ahead() {return true;}
    void print();


};



