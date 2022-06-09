#pragma once

#include "Warehouse.hpp"
#include "AGV.hpp"
#include "Task.hpp"
#define STAR_POSITION_1 272
#define STAR_POSITION_2 268
#define STAR_POSITION_3 264
enum vehicle_num    
{
    option_1 = 1, option_2, option_3
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


/*
 * make_moves - performs moves by every vehicle along AGVs paths. If It does not have a path, make_moves does nothing
 */
void make_moves();

/*
 * returns a vector of current positions of each vehicle
 * @return vector of intiger variabels which mean current pos, vector[0] = current pos AGV (ID=1)
 */
std::vector<int> return_current_positions();
int return_current_position(int AGV_id);


/*
 * returns a vector of remaining points of paths  
 * @return vector of paths 
 */
std::vector<std::list<int>> return_paths();
std::list<int> return_path(int AGV_id);

/*
 * Method to add a task to AGV vehicle
 * @param[in] AGV_id - ID of an AGV vehicle which will have new task
 */
void add_task_to_vehicle(int AGV_id);

/*
 * Method to return vector of free Agvs
 * @return - vector of free AGVs
 */
std::vector<int> free_AGVs();

/*
 * Method to check whether task list is empty
 * @return - true if nothing to assign, else false
 */
bool empty_task_list() {return this->tasks_to_do.empty();};

/*
 * Method to check whether all AGVs finished their tasks
 * @return - true if all agvs finished their tasks, else false
 */
bool AGV_in_use(int AGV_id);


/*
 * Method to return task percent of particular AGV
 * @return - task percent
 */
float return_task_percent(int AGV_id);

/*
 * Method to return task id of particular AGV
 * @return - task percent
 */
int return_task_id(int AGV_id);

void back_to_start_position(int AGV_id);


};
