cmake_minimum_required(VERSION 3.0)

add_subdirectory(./random-map)

add_executable(test test.cpp)

target_link_libraries(test randomMap)