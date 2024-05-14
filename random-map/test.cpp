#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void test(){
  std::cout << "test2" << std::endl;
}

void test2(std::vector<int> v){
  for_each(v.begin(), v.end(), [](int x){
    std::cout << x << std::endl;
  });
}

int main(){
  std::cout << "test" << std::endl;
  test();
  vector<int> a(2, 1);
  test2(a);
}