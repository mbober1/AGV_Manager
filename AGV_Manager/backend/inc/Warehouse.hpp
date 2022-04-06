#pragma once
#include <memory>
#include "Dynamic2DMatrix.hpp"

typedef Dynamic2DMatrix<int> IntMatrix;     // type defining a matrix of int values
typedef std::unique_ptr<IntMatrix> pMatrix; // type defining a unique pointer to IntMatrix


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
 * Parametric constructor creating an object with a pointer that contains instance IntMatrix with (x,y) size and particular data
 * @param[in] x - number of rows
 * @param[in] y - number of columns 
 * @param[in] input_data - vector storing data to write inside matrix
 */
Warehouse(const unsigned int x, const unsigned int y, std::vector<int> input_data);

/*
 * Basic method printing Matrix content 
 */
void print();

/*
 * method reading data to matrix from file
 */
bool read_from_file(const char * filename);

};

