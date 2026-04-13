#include <stdlib.h>
#include <string.h>
typedef struct DynamicArray {
    void* data;
    size_t size; // Number of elements currently stored
    size_t capacity; // Number of elements currently allocated
    size_t data_size;
} DynamicArray;

void init_dynamic_array(DynamicArray* arr, size_t capacity, size_t data_size);
void resize_dynamic_array(DynamicArray* arr);
void push_back(DynamicArray* arr, void* data);
void free_dynamic_array(DynamicArray* arr);

void* get(DynamicArray* arr, size_t index);
void* insert(DynamicArray* arr, size_t index, void* data);
