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
        libs/data_structures/vector/vector.c
        vec.c
        libs/data_structures/vector/vectorVOID.h
        libs/data_structures/vector/vectorVOID.c
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
        matrix_test.c)
target_link_libraries(OP data_structures)
target_link_libraries(OP algorithms)