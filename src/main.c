#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "disassembler.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  u8 constant = addConstant(&chunk, 1.2);
  writeChunk1(&chunk, OP_CONST, constant, 1);
  writeChunk0(&chunk, OP_NEG, 2);
  writeChunk0(&chunk, OP_DUMP, 3);
  writeChunk0(&chunk, OP_RETURN, 4);

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
