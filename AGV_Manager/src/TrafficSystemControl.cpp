#include "inc/TrafficSystemControl.hpp"
#include <algorithm>
#include "inc/Stage.hpp"
TrafficSystemControl::TrafficSystemControl(Warehouse  &warehouse, AGVs AGVs_vector): AGVs_vector{AGVs_vector}
{
    auto graph_size = warehouse.return_graph_size();
    for(auto i = 0; i < graph_size ; i ++  )
    {
      this->points_with_status.push_back(std::make_pair(Point_State::Free, i));
    }

    this->shared_points_vector.resize(AGVs_vector.get()->size());

    for(auto & it: shared_points_vector)
    {
        it.resize(AGVs_vector.get()->size());
    }


    paths.resize(AGVs_vector.get()->size());
    
}

void TrafficSystemControl::add_path(int agv_id)
{
    this->paths[agv_id] = (*AGVs_vector.get())[agv_id].return_path();
}

void TrafficSystemControl::print()
{
    
    for(auto const & it: this->points_with_status)
    {
        std::cout << static_cast<int>(it.first) << " " << it.second << std::endl;
    }


    for(auto & it: *AGVs_vector.get())
    {
        std::cout << it.return_id() << std::endl;
    }

}
void TrafficSystemControl::clear_shared_points()
{
    for(auto & it: shared_points_vector)
    {
        it.clear();
    }

}

void TrafficSystemControl::set_shared_path_points()
{
    /* std::vector<std::list<int>> temp_vect; */
    std::list<int>::iterator end; 


    clear_shared_points();

   
/*     for(auto &it: temp_vect)
    {
        std::cout << std::endl;
        for(auto &it2: it)
            std::cout << it2 << " ";
    } */

    std::cout << std::endl;



    auto vect_size = paths.size();
   
    for(auto i = 0; i < vect_size; i++)
    {
        std::list<int> temp_1 =  paths[i];
        for(auto j = 0; j < vect_size; j++)
        {
            if(j != i)
            {
                std::list<int> temp_2=paths[j];
                std::list<int> v(temp_1.size() + temp_2.size());
                temp_1.sort();
                temp_2.sort();
                end = std::set_intersection(temp_1.begin(),
                                                temp_1.end(),
                                                temp_2.begin(),
                                                temp_2.end(),
                                                v.begin());
                
                (this->shared_points_vector[i])[j].clear();
                (this->shared_points_vector[i])[j].insert(((this->shared_points_vector[i])[j]).begin(), 
                                                        std::make_move_iterator(v.begin()), 
                                                        std::make_move_iterator(end));
            }
        }
    }

/*     for(auto &it: shared_points_vector[0][1])
    {
      
  
        std::cout << it << " ";
    }
        std::cout << std::endl; */

}

bool TrafficSystemControl::find_element(int key, std::list<int> container)
{
    if(std::count(container.begin(), container.end(), key))
        return true;
    
    return false;
}

bool TrafficSystemControl::point_in_shared_set(int point, int agv_id)
{

    for(auto i=0u; i < shared_points_vector.size(); i++)
    {
        for(auto &it: shared_points_vector[agv_id][i])
        {
            std::cout << it << " ";
        }
        std::cout << std::endl;

        if(find_element(point, shared_points_vector[agv_id][i]))
        {
            return true;
        }
    }

    return false;
} 

bool TrafficSystemControl::point_in_shared_set2(int point, int agv_id, int current_point)
{

    for(auto i=0u; i < shared_points_vector.size(); i++)
    {
        if(find_element(point, shared_points_vector[agv_id][i]))
        {
            if(reserved_point_in_shared_set(shared_points_vector[agv_id][i], current_point))
                return true;
        }
    }

    return false;
} 

bool TrafficSystemControl::reserved_point_in_shared_set(std::list<int> container, int current)
{
    for(auto &it: container)
    {
        if(points_with_status[it].first == Point_State::Reserved && current!=points_with_status[it].second)
            return true;
    }

    return false;
}



bool TrafficSystemControl::go_ahead(AGV agv)
{
    this->set_shared_path_points();
    auto remained_path_to_do = agv.return_path();
    auto next_point  = remained_path_to_do.front();
    auto id = agv.return_id();
    auto current_point = agv.return_current_pos();

  

    if((!point_in_shared_set(next_point, id) ) && (points_with_status[next_point].first == Point_State::Free))
    {
        //std::cout << "tu" << std::endl;
        points_with_status[next_point].first = Point_State::Reserved;
        points_with_status[current_point].first = Point_State::Free;
        return true;
    }
    
    if(!point_in_shared_set2(next_point, id, current_point))
    {
        //std::cout << "tu" << std::endl;
        points_with_status[next_point].first = Point_State::Reserved;
        points_with_status[current_point].first = Point_State::Free; 
        return true;
    }
    

    

    return false;
    
}


