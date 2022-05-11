#include <iostream>
#include <memory>
#include "Stage.hpp"
int main(){

    const char * file_name = "warehouse_1.txt";

    Stage stage(file_name);
    stage.print_info();
    


    return 0;
}
