#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void* validateMemory(void* memory) {
    if (memory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return memory;
}
vector createVector(size_t capacity) {
    return (vector) {
            validateMemory(malloc(capacity * sizeof(int))),
            0,
            capacity,
    };
}
void reserve(vector *v, size_t newCapacity){
    if(newCapacity == 0){
        free(v->data);
        v->data = NULL;
    }
    if(newCapacity < v->size){
        v->size = newCapacity;
    }
    v->data = validateMemory(realloc(v->data, newCapacity * sizeof(int)));
    v->capacity = newCapacity;
}
void clear(vector *v){
    v->size = 0;
}
void shrinkToFit(vector *v) {
    v->capacity = v->size;
}
void deleteVector(vector *v){
    free(v->data);
    v->size = 0;
    v->data = NULL;
    v->capacity = 0;
}