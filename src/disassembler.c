#include <stdio.h>

#include "disassembler.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("=== %s ===\n", name);
  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static int instruction0(const char* name, int offset) {
  printf("%s\n", name);
  return ++offset;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  u8 constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset) {
  u8 instruction = chunk->code[offset];
  switch (instruction) {
  case OP_CONST:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  case OP_NEG:
    return instruction0("OP_NEGATE", offset);
  case OP_RETURN:
    return instruction0("OP_RETURN", offset);
  default:
    printf("Unkown opcode %d\n", instruction);
    return ++offset;
  }
}
