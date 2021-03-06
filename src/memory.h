#ifndef HVM_MEMORY_H
#define HVM_MEMORY_H

#include "common.h"

#define GROW_CAP(cap) ((cap) < 8 ? 8 : cap * 2)

#define GROW_ARRAY(type, ptr, oldCount, newCount)                              \
  (type*)reallocate(ptr, sizeof(type) * oldCount, sizeof(type) * newCount)

#define FREE_ARRAY(type, ptr, oldCount)                                        \
  reallocate(ptr, sizeof(type) * oldCount, 0)

void* reallocate(void* ptr, size_t oldSize, size_t newSize);

#endif
