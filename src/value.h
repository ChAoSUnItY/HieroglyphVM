#ifndef HVM_VALUE_H
#define HVM_VALUE_H

#include "common.h"

#define BOOL_VAL(v) ((Value){T_BOOL, {.boolean = v}})
#define NIL_VAL(v) ((Value){T_NIL, {.integer = 0}})
#define INT_VAL(v) ((Value){T_INT, {.integer = v}})

#define AS_BOOL(v) ((v).as.boolean)
#define AS_INT(v) ((v).as.integer)

#define IS_BOOL(v) ((v).type == T_BOOL)
#define IS_NIL(v) ((v).type == T_NIL)
#define IS_INT(v) ((v).type == T_INT)

typedef enum { T_BOOL, T_NIL, T_BYTE, T_INT, T_LONG } TypeCode;

typedef struct {
  TypeCode type;
  union {
    bool boolean;
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
