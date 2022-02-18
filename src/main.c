#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "disassembler.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
