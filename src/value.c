#include <stdio.h>

#include "memory.h"
#include "value.h"

void printValue(Value value) {
    printf("%g", value);
}

void initValueArray(ValueArray* array) {
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCap = array->capacity;
        array->capacity = GROW_CAP(oldCap);
        array->values = GROW_ARRAY(Value, array->values, oldCap, array->capacity);
    }

    array->values[array->count++] = value;
}

