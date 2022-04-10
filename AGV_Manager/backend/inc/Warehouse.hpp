#pragma once

#include <fstream>
#include <memory>
#include "Dynamic2DMatrix.hpp"

using IntMatrix = Dynamic2DMatrix<int> ;     // type defining a matrix of int values
using pMatrix = std::unique_ptr<IntMatrix>; // type defining a unique pointer to IntMatrix


/*
 * Definition of Warehouse class that represents warehouse for AGVs. 
 * It's used to map warehouse layout by creating matrix and graph 
 */
class Warehouse{

pMatrix Matrix_layout_p;  // Unique  pointer to IntMatrix

public:

Warehouse()
{
    Matrix_layout_p = nullptr;
}

/*
 * Parametric constructor creating an object with a pointer that contains instance IntMatrix with (x,y) size
 * @param[in] x - number of rows
 * @param[in] y - number of columns 
 */
Warehouse(const unsigned int x, const unsigned int y);


/*
 * Basic method printing Matrix content 
 */
void print();

/*
 * method adding sizes of matrix, only if the Matrix_layout_p ==  nullptr
 * @param[in] x - number of rows 
 * @param[in] y - number of columns 
 */
bool add_sizes(const unsigned int x, const unsigned int y);

/*
 * method inserting data to matrix from vector<int>
 * @param[in] x - number of rows 
 * @param[in] y - number of columns 
 */
void insert_data_matrix(std::vector<int> input_data);

};



/*
 * function reading data to a matrix from file
 * @param[in] filename - name of a file
 * @return - true if reading will be executed with success, false in another case
 */
Warehouse read_from_file(const char * filename);