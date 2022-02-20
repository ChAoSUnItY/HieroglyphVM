#include <stdio.h>

#include "loader.h"
#include "common.h"
#include "disassembler.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  loadFile(&chunk, argv[1]);

  interpret(&chunk);
  
  freeVM();
  freeChunk(&chunk);
  return 0;
}
