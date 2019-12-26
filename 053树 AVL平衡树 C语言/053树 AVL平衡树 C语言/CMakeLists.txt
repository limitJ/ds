cmake_minimum_required(VERSION 3.15)
project(AVLTree C)

set(CMAKE_C_STANDARD 11)

add_executable(AVLTree main.c avltree.h avltree.c binarytree.h binarytree.c)