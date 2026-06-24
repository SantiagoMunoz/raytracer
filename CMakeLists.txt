cmake_minimum_required(VERSION 3.10)

project(kTracer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

enable_testing()
include(CTest)
add_subdirectory(test)
