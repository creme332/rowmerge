cmake_minimum_required(VERSION 3.10)
project(rowmerge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(rowmerge src/main.cpp src/validator.cpp)