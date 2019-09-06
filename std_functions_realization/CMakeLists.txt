cmake_minimum_required(VERSION 3.15)
project(std_functions_realization)

set(CMAKE_CXX_STANDARD 17)

add_executable(std_functions_realization main.cpp service_funcs.cpp service_funcs.h custom_funcs.cpp custom_funcs.h)