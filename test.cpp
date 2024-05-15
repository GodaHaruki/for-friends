#include <iostream>
#include "random-map/room.hpp"
#include <vector>

int main(){
  std::vector<std::pair<int, int>> connected;
  
  connected.push_back({5, 0});
  connected.push_back({0, 5});

  room r1(30, 30, 450, connected);

  r1.show();

  room r2(23, 37, 63, connected);

  r2.show();

  connected.push_back({20, 20});
  connected.push_back({18, 13});
  connected.push_back({27, 27});
  room r3(34, 28, 43, connected);

  r3.show();

  room r4(200, 200, 20000, connected);

  r4.show();
}
