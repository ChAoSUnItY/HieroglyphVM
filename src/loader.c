#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "memory.h"

Chunk* loadFileFromBytecode(Chunk* chunk, u8 bytecode[], int len) {
  initChunk(chunk);

  ValueArray va;

  initValueArray(&va);

  int skipLen = 0;
  int version = 0;
  for (int i = 0; i < len; i++) {
    if (i == 0) { // Check magic numbers
      if (bytecode[0] == 'C' && bytecode[1] == 'A' && bytecode[2] == 'S' &&
          bytecode[3] == 'C') {
        i = 3; // Skip 4 bytes
        continue;
      } else {
        fputs("Missing magic number `CASC`", stderr);
        exit(1);
      }
    }

    if (i == 4) {
      version = _a_2btos(bytecode, i);
   
      i += 2;
    }

    if (i == 6) { // read constant length
      int constantLen = _a_2btos(bytecode, i);
      i += 2;

      for (int j = 0; j < constantLen; j++) {
        if (bytecode[i] == 0x00) { // INTEGER CONSTANT
          i++;
          int v = _a_4btoi(bytecode, i);

          writeValueArray(&va, INT_VAL(v));
          i += 4;
        }
      }

      skipLen = i;
      break;
    }
  }

  chunk->constants = va;

  for (int i = skipLen; i < len; i++) {
    writeChunk0(chunk, bytecode[i]);
  }

  return chunk;
}

Chunk* loadFile(Chunk* chunk, const char* filePath) {
  FILE* fileptr;
  long filelen;

  fileptr = fopen(filePath, "rb");
  fseek(fileptr, 0L, SEEK_END);
  filelen = ftell(fileptr);
  rewind(fileptr);

  u8 buffer[filelen * sizeof(u8)];
  for (int i = 0; i < filelen; i++) {
    fread(buffer + i, 1, 1, fileptr);
  }
  fclose(fileptr);

  return loadFileFromBytecode(chunk, buffer, filelen);
}
