#include "room.hpp"
#include <vector>
#include <random>
#include <utility>

using pos = std::pair<int, int>;

int dig_inner(pos current, int can_dig, vector<vector<bool>>& map, vector<int>& min_distances, const vector<pos>& connected){
  if(can_dig - accumulate(min_distances.begin(), min_distances.end(), 0) <= 0){
    return can_dig;
  }

  // todo

  return dig_inner(current, can_dig, map, min_distance, connected);
}

void dig(pos current, int can_dig, vector<vector<bool>>& map, vector<int>& min_distances, const vector<pos>& connected){
  can_dig = dig_inner(current, can_dig, map, min_distances, connected);

  
  if(can_dig > 0){
  }
}

room::room(const int width, const int height, const int block, const& vector<pos> connected)
: _width(width), _height(height), _block(block),
{
  _m = vector<vector<bool>>(height, vector<bool>(width, false));
  int connection_count = connected.size();
  
  std::random_device rd;
  std::mt19937 mt(rd());

  pos current = {0, 0};
  vector<int> min_distances(0, 0);
  int digged = 0;
  if(connected.size() > 0){
    current = connected[0];
    min_distances.resize(connection_count);
  }

  auto sum_distances = [&](){
    int res = 0;
    for(auto d : min_distances){
      res += d;
    }

    return res;
  };

  auto distance = [](pos pos1, pos pos2){
    return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
  };
  
  while(block - sum_distances() > digged){
    _map[current.first][current.second] = true;
    for(int i = 0; i < connection_count; i++){
      pos c = connected[i];
      if(min_distances[i] > distance(c, current)){
        min_distance[i] = distance(c, current);
      }
    }
  }
}
