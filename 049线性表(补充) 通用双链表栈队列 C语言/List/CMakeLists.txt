# cmake_minimum_required(VERSION <specify CMake version here>)
project(List C)

set(CMAKE_C_STANDARD 11)

add_executable(List main.c list.h list.c)