cmake_minimum_required(VERSION 3.10)
project(rowmerge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB ALGO_SOURCES src/algorithms/*.cpp)

# Main executable
add_executable(rowmerge 
    src/main.cpp
    src/timer.cpp
    src/validator.cpp 
    src/CSVHandler.cpp 
    ${ALGO_SOURCES}
)

# Executable for validation program
add_executable(validator 
    src/validator_main.cpp
    src/validator.cpp 
    src/CSVHandler.cpp 
)

# Enable testing and include CTest module
enable_testing()
include(CTest)

# Create the test executable
add_library(test_main OBJECT tests/test_runner.cpp)

# Add the test for the Validator class
add_executable(validator_test tests/validator_test.cpp src/validator.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME Validator_Test COMMAND validator_test)

# Add the test for the CSVHandler class
add_executable(csv_handler_test tests/csv_handler_test.cpp src/CSVHandler.cpp src/validator.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME CSVHandler_Test COMMAND csv_handler_test)

# Add the test for the TrivialAlgorithm class
add_executable(trivial_algo_test tests/algorithms/trivial_algo_test.cpp src/CSVHandler.cpp src/validator.cpp src/algorithms/trivial_algo.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME Trivial_Algorithm_Test COMMAND trivial_algo_test)