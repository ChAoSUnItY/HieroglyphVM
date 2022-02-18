#ifndef HVM_DISASSEMBLER_H
#define HVM_DISASSEMBLER_H

#include "chunk.h"
#include "common.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif
