cmake_minimum_required(VERSION 3.13)
project(RCSRTSMatrix C)

set(CMAKE_C_STANDARD 11)

add_executable(RCSRTSMatrix main.c rcsmatrix.h rcsmatrix.c)