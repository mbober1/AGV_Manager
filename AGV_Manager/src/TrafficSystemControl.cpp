#include "inc/TrafficSystemControl.hpp"
#include <algorithm>

TrafficSystemControl::TrafficSystemControl(Warehouse  &warehouse, AGVs &AGVs_vector): AGVs_vector{&AGVs_vector}
{
    auto graph_size = warehouse.return_graph_size();
    for(auto i = 0; i < graph_size ; i ++  )
    {
      this->points_with_status.push_back(std::make_pair(Point_State::Free, i));
    }
    
}


void TrafficSystemControl::print()
{
    std::cout << "shared points vector size: " << this->shared_points_vector.size() << std::endl;
    for(auto const & it: this->points_with_status)
    {
        std::cout << static_cast<int>(it.first) << " " << it.second << std::endl;
    }


    for(auto & it: this->AGVs_vector)
    {
        std::cout << it.return_id() << std::endl;
    }

}


void TrafficSystemControl::set_shared_path_points()
{
    std::vector<std::list<int>> temp_vect;
    std::list<int> temp;

    for(auto & it: AGVs_vector)
    {
        temp_vect.push_back(it.return_path());
        std::cout << it.return_current_pos() << std::endl;
    }

    auto vect_size = temp_vect.size();
   
    for(auto i = 0; i < vect_size-1; i++)
    {
        std::list<int> temp_1 =  temp_vect[i];
        for(auto j = i+1; j < vect_size; j++)
        {
            std::list<int> temp_2 = temp_vect[j];
            std::vector<int> v(temp_1.size()+temp_2.size());
            auto end = std::set_intersection(temp_1.begin(),
                                            temp_1.end(),
                                            temp_2.begin(),
                                            temp_2.end(),
                                            v.begin());
            if(i == 0)
            {
                temp.insert(temp.begin(), 
                            std::make_move_iterator(v.begin()), 
                            std::make_move_iterator(end));
            }

            else
            {
                temp.insert(temp.begin(), 
                            std::make_move_iterator(v.begin()), 
                            std::make_move_iterator(end));
            }

            this->shared_points_vector.push_back(temp);
            temp.clear();
        }
    }

    for(auto & it: this->shared_points_vector)
    {
        for(auto & it_2: it)
        {
            std::cout << it_2 << std::endl;
        }
        std::cout << std::endl; 
    } 

}