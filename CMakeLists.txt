cmake_minimum_required(VERSION 3.7)
project(fast_split)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(fast_split SHARED src/exploder.cpp src/explode.cpp)