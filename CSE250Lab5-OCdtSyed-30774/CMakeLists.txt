cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(Lab5)

# Add Network implementations
add_library(Network SHARED Network.cpp)
add_library(Network2 SHARED NetworkClassic.cpp)

# Main application
add_executable(Lab5 main.cpp)
target_link_libraries(Lab5 Network Network2)

# Benchmark application
add_executable(Benchmark benchmark.cpp)
target_link_libraries(Benchmark Network Network2)
