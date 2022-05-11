#pragma once

#include "inc/warehouse.hpp"



/*
 * Definition of AGV class that represents AGV vehicle 
 */
class AGV{

int id;
int current_pos;
bool in_use;

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


};