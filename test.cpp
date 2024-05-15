#include <iostream>
#include "random-map/room.hpp"
#include <vector>

int main(){
  std::vector<std::pair<int, int>> connected;
  
  connected.push_back({5, 0});
  connected.push_back({0, 5});
  connected.push_back({19, 19});
  // connectedを2つ以外にするとセグフォ起きる

  room r(20, 20, 100, connected);

  r.show();

  room r2(23, 37, 63, connected);

  r2.show();

  connected.push_back({20, 20});
  connected.push_back({18, 13});
  room r3(34, 28, 43, connected);

  r3.show();
}
