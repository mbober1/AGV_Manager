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

using status_points = std::vector<std::pair< Point_State, int>>;
using shared_path_points =std::vector<std::vector<std::list<int>>>;
using AGVs = std::shared_ptr<std::vector<AGV>>;
using road = std::vector<std::list<int>>;

/*
 * Class to handle collision protection. Created according to:
 * "Dynamic Resource Reservation Based Collision and Deadlock Prevention for Multi-AGVs"
 * source: https://ieeexplore.ieee.org/document/9081905
 *
 */
class TrafficSystemControl{

status_points points_with_status;
AGVs AGVs_vector;
shared_path_points shared_points_vector;
road paths;

void clear_shared_points();
bool find_element(int key, std::list<int> container);
bool condition_1(int point, int agv_id);
bool condition_2(int point, int agv_id, int current_point);
bool reserved_point_in_shared_set(std::list<int> container,  int current);

public:
    TrafficSystemControl() = delete;
    TrafficSystemControl(Warehouse  &warehouse, AGVs AGVs_vector);


    bool go_ahead(AGV agv);
    void print();
    void add_path(int agv_id);
    void set_shared_path_points();


};



