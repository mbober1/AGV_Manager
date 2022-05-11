#include <iostream>
#include <memory>
#include "Stage.hpp"
int main(){

    const char * file_name = "/home/mbober/Documents/PWR_Algorytmy_optymalizacji/AGV_Manager/resources/data/warehouse.data";

    Stage stage(file_name);
    stage.print_info();
    


    return 0;
}
