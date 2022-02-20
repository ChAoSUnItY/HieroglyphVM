#ifndef HVM_VM_H
#define HVM_VM_H

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;
  u8* ip;
  int line;
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

typedef enum { INTERPRET_OK, INTERPRET_ERROR } InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value peek(int distance);
Value pop();
InterpretResult run();

#endif
