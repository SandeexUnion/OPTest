#ifndef OP_VECTOR_H
#define OP_VECTOR_H
#include <stdio.h>
#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;
vector createVector(size_t n);

#endif //OP_VECTOR_H
