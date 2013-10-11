project(avx_decimate)
set(CMAKE_CXX_FLAGS "-Wall -O3 -std=gnu++11 -mavx")
cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)
SET(SRC_LIST main.cpp decimate.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

