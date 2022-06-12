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
    auto temp = 0u;
    for(auto i = 0u; i < (*AGVs_vector.get()).size()-1; i++)
    {
        for(auto j = i+1; j <(*AGVs_vector.get()).size(); j++)
        {
            temp++;
        }
    }
    this->shared_points_vector.resize(temp);

    
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
    std::vector<std::list<int>> temp_vect;
    std::list<int>::iterator end; 


    clear_shared_points();

    for(auto & it: *AGVs_vector.get())
    {
        temp_vect.push_back(it.return_path());
    }
 
    auto vect_size = temp_vect.size();
   
    for(auto i = 0; i < vect_size-1; i++)
    {
        std::list<int> temp_1 =  temp_vect[i];
        for(auto j = i+1; j < vect_size; j++)
        {
            std::list<int> temp_2 = temp_vect[j];
            std::list<int> v(temp_1.size() + temp_2.size());
            temp_1.sort();
            temp_2.sort();
            end = std::set_intersection(temp_1.begin(),
                                            temp_1.end(),
                                            temp_2.begin(),
                                            temp_2.end(),
                                            v.begin());
            
            if(i == 0)
            {
                this->shared_points_vector[i+j-1].insert(this->shared_points_vector[i+j-1].begin(), 
                                                         std::make_move_iterator(v.begin()), 
                                                         std::make_move_iterator(end));
            }

            else
            {
                this->shared_points_vector[i+j].insert(this->shared_points_vector[i+j].begin(), 
                                                        std::make_move_iterator(v.begin()), 
                                                        std::make_move_iterator(end));
            }
            v.clear();
        }
    }

/*     for(auto & it: shared_points_vector)
    {
        std::cout << std::endl;
        for(auto & it2: it)
        {
            std::cout << it2 << " ";
        }
    } */

}

bool TrafficSystemControl::find_element(int key, std::list<int> container)
{
    if(std::count(container.begin(), container.end(), key))
        return true;
    
    return false;
}


bool TrafficSystemControl::go_ahead(AGV agv)
{
    this->set_shared_path_points();
    auto remained_path_to_do = agv.return_path();
    auto next_point  = remained_path_to_do.front();

    std::cout << next_point << std::endl;

    if()
    


    return true;
}