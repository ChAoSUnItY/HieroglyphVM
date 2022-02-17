#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "disassembler.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    writeChunk1(&chunk, OP_CONSTANT, addConstant(&chunk, 1.2));
    writeChunk0(&chunk, OP_RETURN);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
} 

