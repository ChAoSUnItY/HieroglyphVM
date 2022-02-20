#include <stdio.h>

#include "common.h"
#include "chunk.h"

Chunk* loadFileFromBytecode(Chunk* chunk, u8 bytecode[], int len);
Chunk* loadFile(Chunk* chunk, const char* filePath);
