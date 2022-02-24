#ifndef HVM_VALUE_H
#define HVM_VALUE_H

#include "common.h"

#define BYTE_VAL(v) ((Value){T_BYTE, {.byte = v}})
#define NIL_VAL(v) ((Value){T_NIL, {.integer = 0}})
#define INT_VAL(v) ((Value){T_INT, {.integer = v}})

#define AS_BYTE(v) ((v).as.byte)
#define AS_INT(v) ((v).as.integer)

#define IS_BYTE(v) ((v).type == T_BYTE)
#define IS_NIL(v) ((v).type == T_NIL)
#define IS_INT(v) ((v).type == T_INT)

typedef enum { T_NIL, T_BYTE, T_INT, T_LONG } TypeCode;

typedef struct {
  TypeCode type;
  union {
    u8 byte;
    int integer;
  } as;
} Value;

void printValue(Value value);

typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void freeValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);

#endif
