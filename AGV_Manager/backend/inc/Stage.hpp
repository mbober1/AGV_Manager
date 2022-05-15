#pragma once

#include "Warehouse.hpp"
#include "AGV.hpp"
#define STAR_POSITION 3
enum vehicle_num    
{
    option_1 = 1, option_2, option_3, option_4
};

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

Warehouse Warehouse_object; 
AGVs AGV_vehicles;
Tasks tasks_to_do;


/*
 * Method to read data from file to the Tasks list
 * @param[in] filename - name of file storing data to the Tasks list
 * 
 * @return true if it  finished with success, else false
 */
bool read_tasks_from_file(const char * filename);

/*
 * Method to set AGVs Vector 
 * @param[in] option - amount of vehicles addding to list
 */
void add_vehicles(vehicle_num option);


public:


Stage() = delete; // to prevent using a default constructor
/*
 * The parametric constructor - allows for setting data to the Warehouse object and the Tasks list
 * @param[in] filename_warehouse - name of file storing data to the Warehouse object
 * @param[in] filename_tasks - name of file storing data to the Tasks list
 */
Stage(const char * filename_warehouse, const char* filename_tasks, vehicle_num option);



void print_info();  // to print info about Stage's components
int rows_num() {return this->Warehouse_object.rows_num();}   // returns a rows number
int columns_num() {return this->Warehouse_object.columns_num();}    // returns a columns number

void make_move();

};