#pragma once
#include <vector>
#include <utility>

class room {
  private:
    vector<vector<bool>> _room; // trueが通路、falseが壁
    const int _width, _height, _block;
  public:
    room(const int width, const int height, const int block, const& vector<std::pair<int, int>> connected);
}
