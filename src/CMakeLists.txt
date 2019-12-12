cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(tracer
${PROJECT_SOURCE_DIR}/src/tracer.cpp 
${PROJECT_SOURCE_DIR}/src/tuple.cpp 
${PROJECT_SOURCE_DIR}/src/canvas.cpp 
${PROJECT_SOURCE_DIR}/src/matrix.cpp
${PROJECT_SOURCE_DIR}/src/ray.cpp
${PROJECT_SOURCE_DIR}/src/sphere.cpp )
