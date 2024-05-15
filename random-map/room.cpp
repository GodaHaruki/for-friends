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

  return current; // unreachable
}

std::vector<direction> get_paths(pos const current, const std::vector<std::vector<bool>>& map){
  std::vector<direction> directions;
  
  if(current.first -1 > 0 && !map.at(current.first -1).at(current.second)){
    directions.push_back(direction::down);
  }
  if(current.first +1 < map.size() && !map.at(current.first +1).at(current.second)){
    directions.push_back(direction::up);
  }
  if(current.second -1 > 0 && !map.at(current.first).at(current.second -1)){
    directions.push_back(direction::left);
  }
  if(current.second +1 < map.at(0).size() && !map.at(current.first).at(current.second +1)){
    directions.push_back(direction::right);
  }

  return directions;
}

int distance(pos const pos1, pos const pos2){
  return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

int dig_inner(pos const current, int const can_dig, std::vector<pos>& history, std::vector<std::vector<bool>>& map, std::vector<int>& min_distances, const std::vector<pos>& connected){
  if(can_dig - std::accumulate(min_distances.begin(), min_distances.end(), 0) <= 0){
    return can_dig;
  }

  map.at(current.first).at(current.second) = true; // atに変えたらここで落ちてるのがわかった
  
  for(auto& h : history){
    if(h.first == -1 && h.second == -1){
      h = current;
      break;
    }
  }

  auto c = connected.at(0);
  for(int i = 0; i < connected.size(); i++){
    if(min_distances.at(i) < distance(c, connected.at(i)) || min_distances.at(i) == -1){
      min_distances.at(i) = distance(c, connected.at(i));
    }
  }

  std::random_device rd;
  std::mt19937 mt(rd());

  pos new_pos = {-1, -1};
  auto paths = get_paths(current, map);
  
  if(paths.size() != 0){
    auto d = paths.at(mt() % paths.size());
    new_pos = get_pos(current, d);
  } else {
    for(int i = history.size() -1; i >= 0; i--){
      if(history.at(i).first == -1 || history.at(i).second == -1){
        continue;
      }
      
      paths = get_paths(history.at(i), map);
      if(paths.size() != 0){
        auto d = paths.at(mt() % paths.size());
        new_pos = get_pos(history.at(i), d);
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
  std::vector<int> min_distances(connected.size(), -1);
  std::vector<pos> history(can_dig, {-1, -1});

  can_dig = dig_inner(current, can_dig, history, map, min_distances, connected);

  for(int i = 0; i < min_distances.size(); i++){
    if(min_distances.at(i) != 0){
      // 通路と通路を最短経路で繋ぐ

      pos nearest_pos = {-1, -1};
      for(int h = 0; h < map.size(); h++){
        for(int w = 0; w < map.at(0).size(); w++){
          if(distance({h, w}, connected.at(i)) == min_distances.at(i)){
            nearest_pos = {h, w};
            break;
          }
        };

        if(nearest_pos.first != -1 && nearest_pos.second != -1){
          break;
        }
      };

      current = nearest_pos;
      while(current.first != connected.at(i).first || current.second != connected.at(i).second){
        if(current.first > connected.at(i).first){
          current.first--;
          map.at(current.first).at(current.second) = true;
          can_dig--;
        } else if(current.first < connected.at(i).first) {
          current.first++;
          map.at(current.first).at(current.second) = true;
          can_dig--;
        }

        if(current.second > connected.at(i).second){
          current.second--;
          map.at(current.first).at(current.second) = true;
          can_dig--;
        } else if(current.second < connected.at(i).second) {
          current.second++;
          map.at(current.first).at(current.second) = true;
          can_dig--;
        }
      }
    }
  }
}


room::room(const int width, const int height, const int block, const std::vector<pos>& connected)
: _width(width), _height(height), _block(block)
{
  _map = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));
  int can_dig = width * height - block;

  dig(connected.at(0), can_dig, _map, connected);
}

void room::show() const{
  for(int h = 0; h < _height; h++){
    for(int w = 0; w < _width; w++){
      if(_map.at(h).at(w)){
        std::cout << '.';
      } else {
        std::cout << '@';
      }
    }
    std::cout << std::endl;
  }
}
