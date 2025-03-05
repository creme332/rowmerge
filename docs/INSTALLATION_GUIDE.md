# Installation Guide

## Prerequisites

- CMake
- Git
- C++ compiler

## Instructions

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