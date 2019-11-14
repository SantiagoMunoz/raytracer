cmake_minimum_required(VERSION 2.6)

project(kTracer)

add_subdirectory(src)

enable_testing()
include(CTest)
add_subdirectory(test)
