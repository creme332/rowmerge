# Installation Guide

## Prerequisites

- CMake (optional but recommended)
- Git (only needed for downloading the repository)
- C++17 compiler

## Instructions with CMake

Download the repository:

```bash
git clone git@github.com:creme332/rowmerge.git
```

Build the project:

```bash
cd rowmerge
mkdir build && cd build
cmake ..
make
```

To run the main executable in the `build` folder: 

```bash
cd /path/to/build
./rowmerge
```

To run tests:

```bash
cd /path/to/build
ctest --output-on-failure
```

## Instructions without CMake

Compile the project:

```bash
g++ -std=c++17 -pthread src/main.cpp src/algorithms/*.cpp src/CSVHandler.cpp src/timer.cpp src/validator.cpp -o rowmerge.exe 
```

Run the project:

```bash
./rowmerge.exe
```