cmake_minimum_required(VERSION 2.6)

include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

add_executable(tuple_tests tuple_tests.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp)
target_link_libraries(tuple_tests gtest gtest_main pthread)
add_test(NAME tuple_tests COMMAND tuple_tests)

add_executable(canvas_tests canvas_tests.cpp ${PROJECT_SOURCE_DIR}/src/canvas.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp)
target_link_libraries(canvas_tests gtest gtest_main pthread)
add_test(NAME canvas_tests COMMAND canvas_tests)
