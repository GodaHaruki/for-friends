#include <iostream>
#include "random-map/room.hpp"
#include <vector>

int main(){
  std::vector<std::pair<int, int>> connected;
  
  connected.push_back({5, 0});
  connected.push_back({0, 5});
  
  room r(20, 20, 10, connected);

  r.show();
}