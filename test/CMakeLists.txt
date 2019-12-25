cmake_minimum_required(VERSION 2.6)

include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

add_executable(tuple_tests tuple_tests.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp)
target_link_libraries(tuple_tests gtest gtest_main pthread)
add_test(NAME tuple_tests COMMAND tuple_tests)

add_executable(canvas_tests canvas_tests.cpp ${PROJECT_SOURCE_DIR}/src/canvas.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp)
target_link_libraries(canvas_tests gtest gtest_main pthread)
add_test(NAME canvas_tests COMMAND canvas_tests)

add_executable(matrix_tests matrix_tests.cpp ${PROJECT_SOURCE_DIR}/src/matrix.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp)
target_link_libraries(matrix_tests gtest gtest_main pthread)
add_test(NAME matrix_tests COMMAND matrix_tests)

add_executable(transformation_tests transformation_tests.cpp ${PROJECT_SOURCE_DIR}/src/matrix.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp)
target_link_libraries(transformation_tests gtest gtest_main pthread)
add_test(NAME transformation_tests COMMAND transformation_tests)

add_executable(ray_tests ray_tests.cpp ${PROJECT_SOURCE_DIR}/src/matrix.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp ${PROJECT_SOURCE_DIR}/src/ray.cpp ${PROJECT_SOURCE_DIR}/src/sphere.cpp)
target_link_libraries(ray_tests gtest gtest_main pthread)
add_test(NAME ray_tests COMMAND ray_tests)

add_executable(plane_tests plane_tests.cpp ${PROJECT_SOURCE_DIR}/src/matrix.cpp ${PROJECT_SOURCE_DIR}/src/tuple.cpp ${PROJECT_SOURCE_DIR}/src/ray.cpp ${PROJECT_SOURCE_DIR}/src/sphere.cpp ${PROJECT_SOURCE_DIR}/src/plane.cpp)
target_link_libraries(plane_tests gtest gtest_main pthread)
add_test(NAME plane_tests COMMAND plane_tests)
