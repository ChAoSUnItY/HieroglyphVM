#ifndef HVM_VM_H
#define HVM_VM_H

#include <stdbool.h>

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;
  u8* ip;
  int line;
  int stackCount;
  Value stack[STACK_MAX];
  Value* stackTop;
  bool terminate;
} VM;

typedef enum { INTERPRET_OK, INTERPRET_ERROR } InterpretResult;

void initVM();
void freeVM();
InterpretResult loadAndInterpret(u8 bytecode[], int len);
InterpretResult interpret(Chunk* chunk);
void push(Value value);
bool assertOperands(size_t count);
Value peek(int offset);
Value pop();
InterpretResult run();

#endif
