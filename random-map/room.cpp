#include "room.hpp"
#include <vector>
#include <random>
#include <utility>
#include <algorithm>
#include <iostream>

// 通路のサイズを大きくするとセグメンテーションフォルトが起きやすい　あとで原因探す

using pos = std::pair<int, int>;

enum direction {
  up,
  down,
  left,
  right,
};

pos get_pos(pos current, direction d){
  switch(d){
      case direction::up:
        return {current.first + 1, current.second};
      case direction::down:
        return {current.first -1, current.second};
      case direction::left:
        return {current.first, current.second -1};
      case direction::right:
        return {current.first, current.second +1};
    }
}

std::vector<direction> get_paths(pos const current, const std::vector<std::vector<bool>>& map){
  std::vector<direction> directions;

  if(current.first -1 > 0 && !map[current.first -1][current.second]){
    directions.push_back(direction::down);
  }
  if(current.first +1 < map.size() && !map[current.first +1][current.second]){
    directions.push_back(direction::up);
  }
  if(current.second -1 > 0 && !map[current.first][current.second -1]){
    directions.push_back(direction::left);
  }
  if(current.second +1 < map.size() && !map[current.first][current.second +1]){
    directions.push_back(direction::right);
  }

  return directions;
}

int distance(pos const pos1, pos const pos2){
  return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

int dig_inner(pos const current, int const can_dig, std::vector<pos>& history, std::vector<std::vector<bool>>& map, std::vector<std::pair<int, pos>>& min_distances, const std::vector<pos>& connected){
  std::cout << "dig_inner" << std::endl;
  if(can_dig - std::accumulate(min_distances.begin(), min_distances.end(), 0) <= 0){
    return can_dig;
  }

  map.at(current.first).at(current.second) = true; // atに変えたらここで落ちてるのがわかった
  
  history.push_back(current);

  auto c = connected[0];
  for(int i = 0; i < connected.size(); i++){
    min_distances[i] = {distance(c, connected[i]), c};
  }

  std::random_device rd;
  std::mt19937 mt(rd());

  pos new_pos = {-1, -1};

  // path選択のところに実装ミスがあると思う
  auto paths = get_paths(current, map);
  if(paths.size() != 0){
    std::cout << "found path" << std::endl;
    auto d = paths[mt() % paths.size()];
    
    std::cout << "selected path" << std::endl;
    new_pos = get_pos(current, d);
  } else {
    // not foundの方に実装ミスある説が濃厚
    std::cout << "path not found" << std::endl;
    for(int i = history.size() -1; i >= 0; i--){
      std::cout << "history_backed" << std::endl;
      if(history[i].first == -1 || history[i].second == -i){
        continue;
      }
      
      paths = get_paths(history[i], map);
      if(paths.size() != 0){
        auto d = paths[mt() % paths.size()];
        new_pos = get_pos(current, d);
        break;
      }
    }
  }

  if(new_pos.first == -1 || new_pos.second == -1){ // pathがどこにも無かったら(全てのマスを掘り切ったら)
    std::cout << (can_dig == 0 ? "ok" : "error") << std::endl;

    return can_dig -1;
  }

  return dig_inner(new_pos, can_dig -1, history, map, min_distances, connected);
}

void dig(pos current, int can_dig, std::vector<std::vector<bool>>& map, const std::vector<pos>& connected){
  std::vector<int> min_distances(connected.size(), INT32_MAX);
  std::vector<pos> history(can_dig, {-1, -1});

  int left_dig = dig_inner(current, can_dig, history, map, min_distances, connected);

  for(int i = 0; i < min_distances.size(); i++){
    if(min_distances[i] != 0){
      // 通路と通路を最短経路で繋ぐ
    }
  }
}


room::room(const int width, const int height, const int block, const std::vector<pos>& connected)
: _width(width), _height(height), _block(block)
{
  _map = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));
  int can_dig = width * height - block;

  dig(connected[0], can_dig, _map, connected);
}

void room::show() const{
  for(int h = 0; h < _height; h++){
    for(int w = 0; w < _width; w++){
      if(_map[h][w]){
        std::cout << '.';
      } else {
        std::cout << '@';
      }
    }
    std::cout << std::endl;
  }
}
