#include "inc/warehouse.hpp"



weight_t neighbor::weight=1;

Warehouse::Warehouse(const unsigned int x, const unsigned int y): Matrix_layout_p{std::make_unique<IntMatrix>(x,y)}
{

}


void Warehouse::print()
{
    Matrix_layout_p->print();

    for( auto i = 0u; i < this->Warehouse_graph.size(); i ++ )
    {
        std::cout << i << ": ";
        for( auto j = 0u; j < Warehouse_graph[i].size(); j++ )
        {
            std::cout << Warehouse_graph[i][j].target << " ";
        }
        std::cout << std::endl;
    }
}


void Warehouse::insert_data_matrix( std::vector<int> input_data)
{
    if(!Matrix_layout_p->insert_data(input_data))
    {
        std::cerr << "Warehouse: Problem with writing data to matrix \n";
        exit(-1);
    } 
    create_graph();
    
}


bool Warehouse::add_sizes(const unsigned int x, const unsigned int y)
{
    if(this->Matrix_layout_p != nullptr)
        return false;
    
    this->Matrix_layout_p = std::make_unique<IntMatrix>(x,y);
    return true;
}


void Warehouse::create_graph()
{
    if(Matrix_layout_p == nullptr)
    {
        std::cerr << "Warehouse::create_graph: Matrix == nullptr \n";
        exit(-1);
    }
    auto columns_num = this->Matrix_layout_p->columns_number();
    auto row_num = this->Matrix_layout_p->rows_number();
    auto vertices_num = columns_num * row_num;

    adjacency_list_t vector(vertices_num);
    IntMatrix * pTemp = this->Matrix_layout_p.get();

    for(auto i = 0u; i < vector.size(); i++)
    {   
        if( i < columns_num )
        {  
            if( i != columns_num -1 )
                if( (*pTemp)[i] == 1 && (*pTemp)[i+1] == 1 )
                {
                        vector[i].push_back(neighbor(i+1));
                }
            if( (*pTemp)[i] == 1 && (*pTemp)[i+columns_num] == 1 )
            {
                vector[i].push_back(neighbor(i+columns_num));
            }
            if(i != 0)
                if( (*pTemp)[i] == 1 && (*pTemp)[i-1] == 1 )
                {
                    vector[i].push_back(neighbor(i-1));
                }
        }
    
        else if(i > (row_num*columns_num - columns_num -1))
        {
            if( i != row_num*columns_num -1 )
                if( (*pTemp)[i] == 1 && (*pTemp)[i+1] == 1 ) 
                {
                        vector[i].push_back(neighbor(i+1));
                }
            if( (*pTemp)[i] == 1 && (*pTemp)[i-columns_num] == 1 )
            {
                vector[i].push_back(neighbor(i-columns_num));
            }
            if(i != row_num*(columns_num-1))
                if( (*pTemp)[i] == 1 && (*pTemp)[i-1] == 1 ) 
                {
                    vector[i].push_back(neighbor(i-1));
                }
        }

        else
        {
            if( !(i % (columns_num-1) == 0) )
                if( (*pTemp)[i] == 1 && (*pTemp)[i+1] == 1 )
                {
                        vector[i].push_back(neighbor(i+1));
                }
            if( (*pTemp)[i] == 1 && (*pTemp)[i-columns_num] == 1 )
            {
                vector[i].push_back(neighbor(i-columns_num));
            }
            if( (*pTemp)[i] == 1 && (*pTemp)[i+columns_num] == 1 )
            {
                vector[i].push_back(neighbor(i+columns_num));
            }
            if( !(i % columns_num == 0) )
                if( (*pTemp)[i] == 1 && (*pTemp)[i-1] == 1 )
                {
                    vector[i].push_back(neighbor(i-1));
                }
        }
        
    }

    this->Warehouse_graph = vector;

}


Warehouse read_from_file(const char * filename)
{
    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "read_from_file: Problem with file opening \n";
        exit(-1);
    }
    
    std::vector<int> data_buff;
    data_buff.clear();
    unsigned int x_size, y_size, temp_var;

    ReadFile >> x_size >> y_size;
    Warehouse WarehouseObj(x_size, y_size);

    while(ReadFile >> temp_var)
    {
        data_buff.push_back(temp_var);
    }
    
    ReadFile.close();

    if(data_buff.size() != x_size*y_size)
    {
        std::cerr << "read_from_file: Problem with declared size and amount of data \n" <<  data_buff.size() ;
        exit(-1);
    }

    WarehouseObj.insert_data_matrix(data_buff);
    return WarehouseObj;
}


std::list<int> Warehouse::compute_path_Dijkstra(const int start_vertex, const int final_vertex)
{

    std::list<vertex_t> path;  // vector storing road 

    auto graph_size = this->Warehouse_graph.size(); 

    std::vector<weight_t> minimal_distance;  
    std::vector<vertex_t> previous;  

    minimal_distance.clear();
    minimal_distance.resize(graph_size, max_weight);
    minimal_distance[start_vertex] = 0;

    previous.clear();
    previous.resize(graph_size, -1);

    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(minimal_distance[start_vertex], start_vertex));


    while (!vertex_queue.empty()) 
    {
        auto dist = vertex_queue.begin()->first;
        auto u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        
	    const auto& neighbors = this->Warehouse_graph[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            auto v = neighbor_iter->target;
            auto weight = neighbor_iter->weight;
            
            auto distance_through_u = dist + weight;
	        if (distance_through_u < minimal_distance[v]) 
            {
                vertex_queue.erase(std::make_pair(minimal_distance[v], v));
                minimal_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(minimal_distance[v], v));
	        }
        }
    }

    auto final = final_vertex;

    for ( ; final != -1; final = previous[final])
        path.push_front(final);

    for(const auto & it: path)
    {
        std::cout << it << " " ;
    }

    
    return path;
}