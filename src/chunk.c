#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(u8, chunk->code, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk0(Chunk* chunk, u8 byte) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCap = chunk->capacity;
        chunk->capacity = GROW_CAP(oldCap);
        chunk->code = GROW_ARRAY(u8, chunk->code, oldCap, chunk->capacity);
    }

    chunk->code[chunk->count++] = byte;
}

inline void writeChunk1(Chunk* chunk, u8 byte0, u8 byte1) {
    writeChunk0(chunk, byte0);
    writeChunk0(chunk, byte1);
}


int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

