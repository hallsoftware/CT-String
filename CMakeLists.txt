cmake_minimum_required(VERSION 3.14)
project(CtStrLib)

# 1. Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Make your headers available globally to targets in this project
#    (assuming your headers are in an 'include' folder)
include_directories(include)

# 3. Add the test subdirectory
add_subdirectory(test)

# 4. Add the examples subdirectory
add_subdirectory(examples)