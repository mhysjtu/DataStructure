cmake_minimum_required(VERSION 2.8)
project(dataStructure)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

#include_directories(${PROJECT_SOURCE_DIR}/include) #默认在.cpp的文件夹中找头文件

add_executable(testBST src/BST/test.cpp)