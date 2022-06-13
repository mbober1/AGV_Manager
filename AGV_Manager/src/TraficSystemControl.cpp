#include "inc/TraficSystemControl.hpp"

TraficSystemControl::TrafficSystemControl(Warehouse & warehouse)
{
    auto graph_size = warehouse.return_graph_size();
    for(auto i = 0; i < graph_size ; i ++  )
    {
      this->points_with_status.push_back(std::make_pair(Point_State::Free, i));
    }
    this->print();
}

void TraficSystemControl::print()
{
    for(auto const & it: this->points_with_status)
    {
        std::cout << static_cast<int>(it.first) << " " << it.second << std::endl;
    }
}
