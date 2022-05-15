#include <iostream>
#include <memory>
#include "Stage.hpp"
int main(){

    const char * file_name = "warehouse_1.txt";
    const char * file_name_2 = "tasks_1.txt";
    Stage stage(file_name, file_name_2,  option_3);
   
    
    stage.print_info();


    return 0;
}
