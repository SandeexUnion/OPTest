cmake_minimum_required(VERSION 3.26)
project(OP C)

set(CMAKE_C_STANDARD 11)

add_library(OP library.c
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h)
target_link_libraries(course data_structures)
target_link_libraries(course algorithms)