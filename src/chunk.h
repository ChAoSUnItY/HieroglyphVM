#ifndef HVM_CHUNK_H
#define HVM_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONST,
  OP_DUMP,
  OP_NEG,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_REM,
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  u8* code;
  int* lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk0(Chunk* chunk, u8 byte, int line);
void writeChunk1(Chunk* chunk, u8 byte0, u8 byte1, int line);

int addConstant(Chunk* chunk, Value value);

#endif
