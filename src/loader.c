#include "loader.h"
#include "memory.h"

Chunk* loadFile(Chunk* chunk, const char* filePath) {
  FILE* fileptr;
  u8* buffer;
  long filelen;

  fileptr = fopen(".hvmc", "rb");
  fseek(fileptr, 0, SEEK_END);
  filelen = ftell(fileptr);
  rewind(fileptr);

  buffer = (u8*)malloc(filelen * sizeof(u8));
  fread(buffer, filelen, 1, fileptr);
  fclose(fileptr);

  initChunk(chunk);

  chunk->count = filelen;
  chunk->code = buffer;

  while (chunk->capacity < chunk->count) {
    GROW_CAP(chunk->capacity);
  }

  return chunk;
}
