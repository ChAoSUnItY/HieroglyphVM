#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "memory.h"

Chunk *loadFile(Chunk *chunk, const char *filePath)
{
  FILE *fileptr;
  long filelen;

  fileptr = fopen(filePath, "rb");
  fseek(fileptr, 0L, SEEK_END);
  filelen = ftell(fileptr);
  rewind(fileptr);

  u8 buffer[filelen * sizeof(u8)];
  for (int i = 0; i < filelen; i++)
  {
    fread(buffer + i, 1, 1, fileptr);
  }
  fclose(fileptr);

  initChunk(chunk);

  ValueArray va;

  initValueArray(&va);

  int skipLen = 0;
  for (int i = 0; i < filelen; i++)
  {
    if (i == 0)
    { // Check magic numbers
      if (buffer[0] == 'C' && buffer[1] == 'A' && buffer[2] == 'S' &&
          buffer[3] == 'C')
      {
        i = 3; // Skip 4 bytes
        continue;
      }
      else
      {
        fputs(stderr, "Missing magic number `CASC`");
        exit(1);
      }
    }

    if (i == 4)
    { // read constant length
      int constantLen = _a_2btos(buffer, i);
      i += 2;

      for (int j = 0; j < constantLen; j++)
      {
        if (buffer[i] == 0x00)
        { // INTEGER CONSTANT
          i++;
          int v = _a_4btoi(buffer, i);

          writeValueArray(&va, INT_VAL(v));
          i += 4;
        }
      }

      skipLen = i;
      break;
    }
  }

  chunk->constants = va;

  for(int i = skipLen; i < filelen; i++) {
    writeChunk0(chunk, buffer[i]);
  }

  return chunk;
}
