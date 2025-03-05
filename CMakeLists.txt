cmake_minimum_required(VERSION 3.10)
project(rowmerge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Main executable
add_executable(rowmerge src/main.cpp src/validator.cpp src/CSVHandler.cpp)

enable_testing()
include(CTest)

add_library(test_main OBJECT tests/test_main.cpp)

add_executable(test1 tests/test1.cpp src/validator.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME test1 COMMAND test1)