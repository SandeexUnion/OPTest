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
void* validateMemory(void* memory);
void reserve(vector *v, size_t newCapacity);
void clear(vector *v);
void shrinkToFit(vector *v);
void deleteVector(vector *v);
bool isEmpty(vector *v);
bool isFull(vector *v);
int getVectorValue(vector *v, size_t i);
void pushBack(vector *v, int x);

#endif //OP_VECTOR_H
