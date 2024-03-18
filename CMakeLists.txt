cmake_minimum_required(VERSION 3.26.4)
project(OP C)

set(CMAKE_C_STANDARD 11)

add_library(OP library.c
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        libs/algorithms/array/array.h
        main.c
        libs/data_structures/vector/vector.c)
target_link_libraries(OP data_structures)
target_link_libraries(OP algorithms)