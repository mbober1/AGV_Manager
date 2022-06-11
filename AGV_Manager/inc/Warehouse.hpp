#pragma once

#include <fstream>
#include <memory>
#include "Dynamic2DMatrix.hpp"
#include <limits>
#include <set>
#include <list>
#include <utility> // for pair
#include <iterator>
#include <algorithm>
#define IT_IS_PATH 1


using IntMatrix = Dynamic2DMatrix<int> ;     // type defining a matrix of int values
using pMatrix = std::unique_ptr<IntMatrix>; // type defining a unique pointer to IntMatrix
using vertex_t = int;
using weight_t = int;


const int max_weight = std::numeric_limits<int>::max();

/*
 * the structure representing an adjacent vertex
 */
struct neighbor{
    vertex_t target;
    static weight_t  weight;
    neighbor(int target_arg): target(target_arg) {}
};

using adjacency_list_t = std::vector<std::vector<neighbor>>;

/*
 * Definition of Warehouse class that represents warehouse for AGVs. 
 * It's used to map warehouse layout by creating matrix and graph 
 */
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


/*
 * method finding the shortest path from the start vertex to the final vertex
 * @param[in] start_vertex -  start vertex 
 * @param[in] final_vertex - final vertex 
 * @return - list storing sequence of vertices ( required road to achieve final pos.)
 */
std::list<int> compute_path_Dijkstra(const int start_vertex, int final_vertex);

/*
 * method returning the number of rows of the matrix symbolizing a the warehouse
 * @return - The number of matrix rows
 */
int rows_num() {return Matrix_layout_p.get()->rows_number();}

/*
 * method returning the number of columns of the matrix symbolizing a the warehouse
 * @return - The number of matrix columns
 */
int columns_num(){return Matrix_layout_p.get()->columns_number();}


int return_graph_size(){return this->Warehouse_graph.size();} // simple method to return the graph size
};



/*
 * function reading data to a matrix from file
 * @param[in] filename - name of a file that stores data to insert in a warehouse's matrix
 * @return - Warehouse object with data from the file
 */
Warehouse read_from_file(const char * filename);
