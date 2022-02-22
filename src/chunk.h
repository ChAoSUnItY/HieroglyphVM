#ifndef HVM_CHUNK_H
#define HVM_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
  V1_0,
} Version;

typedef enum {
  OP_CONST,
  OP_CONST_0,
  OP_CONST_1,
  OP_DUMP,
  OP_NEG,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_REM,
  OP_L_NOT,
  OP_L_OR,
  OP_L_AND,
  OP_RETURN,
} OpCode;

typedef enum {
  ATTR_LINE = 0x80,
} Attribute;

typedef struct {
  long count;
  int capacity;
  u8* code;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk0(Chunk* chunk, u8 byte);
void writeChunk1(Chunk* chunk, u8 byte0, u8 byte1);

int addConstant(Chunk* chunk, Value value);

#endif
