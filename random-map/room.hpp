#include <vector>
#include <utility>

class room {
  private:
    std::vector<std::vector<bool>> _map; // trueが通路、falseが壁
    const int _width, _height, _block;
  public:
    room(const int width, const int height, const int block, const std::vector<std::pair<int, int>>& connected);

    void show() const;
};
