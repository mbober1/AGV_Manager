#pragma once

#include "inc/warehouse.hpp"
#include "AGV.hpp"

struct Task{
    int target;
    int task_id;
};

using AGVs = std::vector<AGV>;
using Tasks = std::list<Task>;
/*
 * Definition of Stage class that represents an entire robotic process of performing tasks by AGVs
 */
class Stage{

public:
Warehouse Warehouse_object;
AGVs AGV_vehicles;
Tasks task_to_do;


Stage() = delete;
Stage(const char * filename);

void print_info();
bool read_tasks_from_file(const char * filename);


};