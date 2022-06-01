#include <iostream>
#include <memory>
#include "Stage.hpp"
int main(){

    const char * file_name = "warehouse.data";
    const char * file_name_2 = "tasks_1.txt";
    Stage stage(file_name, file_name_2,  option_3);
    std::vector<int> free_agvs_id;

    stage.print_info();
    
    do
    {
        free_agvs_id = stage.free_AGVs();
        if(!free_agvs_id.empty())
        {   
            while(!free_agvs_id.empty())
            {
                if(!stage.empty_task_list())
                {
                    stage.add_task_to_vehicle(free_agvs_id.front());
                }
                 free_agvs_id.erase(free_agvs_id.begin());

            }
        }
        stage.make_moves();
        stage.print_info();
    }while (stage.AGVs_in_use() || !stage.empty_task_list());

   std::cout << stage.return_task_percent(2) << std::endl;
   
    
    


    return 0;
}
