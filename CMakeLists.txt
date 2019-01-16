cmake_minimum_required(VERSION 3.13)
project(fast_split)

set(CMAKE_CXX_STANDARD 17)

add_library(fast_split SHARED exploder.cpp exploder.h explode.h explode.cpp)