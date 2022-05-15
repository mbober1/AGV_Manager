#pragma once

#include "Warehouse.hpp"



/*
 * Definition of AGV class that represents AGV vehicle 
 */
class AGV{

int id;  // ID of vehicle
int current_pos; // current position of vehicle
bool in_use;  // does it have task?
unsigned int target; // Point of the warehouse to achieve

public:
AGV() = delete; // to prevent using a default constructor

/*
 * Parametrical  constructor using to set data to AGV object.
 * @param[in] id - using to set id of AGV object
 * @param[in] current_pos - using to set AGV current_pos
 */
AGV(const int id, const int current_pos);


int return_id() {return this->id;} // using to return AGV id
int return_current_pos() {return this->current_pos;}// using to return AGV current_pos

void print_info(); // using to print info about AGV object

/*
 * method to set target, if AGV does not have a task to do
 */
bool add_target(const unsigned int target);


};