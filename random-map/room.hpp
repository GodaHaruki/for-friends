#pragma once
#include <vector>

class room {
  private:
    vector<vector<bool>> _room; // trueが通路、falseが壁
    const int _width, _height;
  public:
    room(const int width, const int height, const int block);
}
