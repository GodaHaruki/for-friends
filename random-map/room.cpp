#include "room.hpp"
#include <vector>
#include <random>
#include <utility>

using pos = std::pair<int, int>;

bool is_surrounded_by_path(pos const current, const std::vector<std::vector<bool>>& map){
  if(current.first -1 < 0 && map[current.first -1][current.second]){
    return false;
  } else if(current.first +1 < map.size() && map[current.first +1][current.second]){
    return false;
  } else if(current.second -1 < 0 && map[current.first][current.second -1]){
    return false;
  } else if(current.second +1 < map.size() && map[current.first][current.second +1]){
    return false;
  }

  return true;
}

int distance(pos const pos1, pos const pos2){
  return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

void dig(pos const current, int const can_dig, const std::vector<std::vector<bool>>& map, const std::vector<pos>& connected){
  if(can_dig == 0){
    return;
  }
  
  std::random_device rd;
  std::mt19937 mt(rd());  

  pos new_pos = {0, 0};
  return dig(new_pos, can_dig -1, map, connected);
}

room::room(const int width, const int height, const int block, const std::vector<pos>& connected)
: _width(width), _height(height), _block(block)
{
}
