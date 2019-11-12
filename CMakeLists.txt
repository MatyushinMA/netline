cmake_minimum_required(VERSION 3.15.4 FATAL_ERROR)
project(netline LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

## Build project
add_subdirectory(src)
