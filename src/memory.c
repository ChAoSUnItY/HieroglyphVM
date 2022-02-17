#include <stdlib.h>

#include "memory.h"

void* reallocate(void* ptr, size_t oldSize, size_t newSize) {
    if (!newSize) {
        free(ptr);
        return NULL;
    }

    void* result = realloc(ptr, newSize);
    if (!result) exit(1);
    return result;
}

