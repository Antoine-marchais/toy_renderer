cmake_minimum_required(VERSION 3.14)
project(ToyRenderer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)