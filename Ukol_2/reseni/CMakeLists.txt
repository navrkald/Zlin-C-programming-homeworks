project(Vector)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_C_FLAGS "-std=c99")
add_executable(${PROJECT_NAME} ${SRC_LIST})

