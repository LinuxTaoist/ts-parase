# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 设置编译参数
set(CMAKE_CXX_FLAGS "-std=c++0x")

#include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

#source
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRC)

add_executable(Edit ${DIR_SRC})
