cmake_minimum_required(VERSION 3.15)
project(poetry)

set(CMAKE_CXX_STANDARD 17)

add_executable(poetry main.cpp poetry_funcs.h poetry_funcs.cpp)