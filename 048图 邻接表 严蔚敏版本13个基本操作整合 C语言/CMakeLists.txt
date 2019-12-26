cmake_minimum_required(VERSION 3.13)
project(adjmap C)

set(CMAKE_C_STANDARD 11)

add_executable(adjmap main.c adjmap.h adjmap.c queue.h queue.c)