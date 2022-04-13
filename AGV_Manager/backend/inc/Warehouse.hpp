#pragma once

#include <fstream>
#include <memory>
#include "Dynamic2DMatrix.hpp"

using IntMatrix = Dynamic2DMatrix<int> ;     // type defining a matrix of int values
using pMatrix = std::unique_ptr<IntMatrix>; // type defining a unique pointer to IntMatrix


/*
 * the structure representing an adjacent vertex
 */
struct neighbor{
    int target;
    static int weight;
    neighbor(int target_arg): target(target_arg) {}
};
/*
 * Definition of Warehouse class that represents warehouse for AGVs. 
 * It's used to map warehouse layout by creating matrix and graph 
 */

using adjacency_list_t = std::vector<std::vector<neighbor>>;


class Warehouse{

pMatrix Matrix_layout_p;  // Unique  pointer to IntMatrix
adjacency_list_t Warehouse_graph; // graph representing the warehouse layout

void create_graph();   

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
 * @param[in] filename - name of a file that stores data to insert in a warehouse's matrix
 * @return - Warehouse object with data from the file
 */
Warehouse read_from_file(const char * filename);