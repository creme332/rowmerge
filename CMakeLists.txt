set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")


cmake_minimum_required(VERSION 3.10)
project(rowmerge)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB ALGO_SOURCES src/algorithms/*.cpp)

# Main executable
add_executable(rowmerge 
    src/main.cpp 
    src/validator.cpp 
    src/CSVHandler.cpp 
    ${ALGO_SOURCES}
)

enable_testing()
include(CTest)

add_library(test_main OBJECT tests/test_main.cpp)

add_executable(test1 tests/test1.cpp src/validator.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME Validator_Test COMMAND test1)