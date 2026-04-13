#include "../include/dynamicarray.h"

void init_dynamic_array(DynamicArray* arr, size_t capacity, size_t data_size){
    arr->data = malloc(capacity * data_size);
    arr->size = 0;
    arr->capacity = capacity;
    arr->data_size = data_size;
}
void resize_dynamic_array(DynamicArray* arr){
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity * arr->data_size);
}
void push_back(DynamicArray* arr, void* data){
    if (arr->size == arr->capacity) {
        resize_dynamic_array(arr);
    }
    void* target = (char*)arr->data + (arr->size * arr->data_size);
    memcpy(target, data, arr->data_size);
    arr->size++;
}
void free_dynamic_array(DynamicArray* arr){
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void* get(DynamicArray* arr, size_t index){
    if (index >= arr->size) {
        return NULL;
    }
    return (void*) (arr->data + index * arr->data_size);
}
void* insert(DynamicArray* arr, size_t index, void* data) {
    if (index > arr->size) return NULL;
    if (arr->size == arr->capacity) resize_dynamic_array(arr);

    char* base = (char*)arr->data;
    void* pos = base + (index * arr->data_size);

    // Use memmove for overlapping regions when shifting elements right
    if (index < arr->size) {
        memmove(base + (index + 1) * arr->data_size,
                pos,
                (arr->size - index) * arr->data_size);
    }

    memcpy(pos, data, arr->data_size);
    arr->size++;
    return pos;
}