#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "common.h"
#include "loader.h"
#include "vm.h"

VM vm;

static void resetStack() {
  vm.stackTop = vm.stack; 
  vm.stackCount = 0;
}

static void runtimeError(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);

  size_t instruction = vm.ip - vm.chunk->code - 1;
  fprintf(stderr, "[line %d] in script\n", vm.line);
  resetStack();
}

void initVM() {
  resetStack();
  vm.terminate = 0;
}

void freeVM() {}

InterpretResult loadAndInterpret(u8 bytecode[], int len) {
  initVM();

  Chunk chunk;

  loadFileFromBytecode(&chunk, bytecode, len);

  InterpretResult result = interpret(&chunk);

  freeChunk(&chunk);

  return result;
}

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
  vm.stackCount++;
}

bool assertOperands(size_t count) {
  if (vm.stackCount < count) {
    runtimeError("Invalid operand. Not enough operands on stack, requires %d operands.", count);
    vm.terminate = true;
    return false;
  }

  return true;
}

Value peek(int offset) { return vm.stackTop[-1 - offset]; }

Value pop() {
  if (!vm.stackCount) {
    runtimeError("Invalid operand. No operands on stack to be popped.");
    vm.terminate = true;
  }

  vm.stackTop--;
  vm.stackCount--;
  return *vm.stackTop;
}

InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define ARITHMETIC_BINARY_OP(op, opName) \
  { \
    if(!assertOperands(2)) break; \
    if (IS_INT(peek(0)) && IS_INT(peek(1))) { \
      int b = AS_INT(pop()); \
      int a = AS_INT(pop()); \
      push(INT_VAL(a op b)); \
    } else { \
      runtimeError("Cannot aaply operator `%s` on `%s` and `%s`", #opName, peek(0).type, peek(1).type); \
      return INTERPRET_ERROR; \
    } \
  }
#define IF_CMP(op, opName) \
  { \
    if (!assertOperands(2)) break; \
    if ((IS_INT(peek(0)) || IS_NIL(peek(0))) && (IS_INT(peek(1)) || IS_NIL(peek(1)))) { \
      int b = AS_INT(pop()); \
      int a = AS_INT(pop()); \
      bool result = a op b; \
      int byteOffset = _2btos(vm.ip); \
      if (result) { \
        vm.ip = vm.chunk->code + byteOffset; \
      } \
    } else { \
      runtimeError("Cannot apply operator `%s` on `%s` and `%s`", #opName, peek(0).type, peek(1).type); \
      return INTERPRET_ERROR; \
    } \
  }

  for (;;) {
    u8 instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONST: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_CONST_0: push(BYTE_VAL(false)); break;
    case OP_CONST_1: push(BYTE_VAL(true)); break;
    case OP_CONST_NIL: push(NIL_VAL()); break;
    case OP_DUMP: {
      if (!assertOperands(1)) break;

      if (IS_INT(peek(0))) {
        printf("%d\n", AS_INT(pop()));
      } else if (IS_BYTE(peek(0))) {
        printf("%s\n", AS_BYTE(pop()) ? "true" : "false");
      } else if (IS_NIL(peek(0))) {
        pop();
        printf("nil\n");
      }
      break;
    }
    case OP_NEG:
      if (!assertOperands(1)) break;

      if (!IS_INT(peek(0))) {
        runtimeError("Cannot apply operator `negate` on `%s`", peek(0).type);
        return INTERPRET_ERROR;
      } else push(INT_VAL(-AS_INT(pop())));
      break;
    case OP_ADD: ARITHMETIC_BINARY_OP(+, plus); break;
    case OP_SUB: ARITHMETIC_BINARY_OP(-, minus); break;
    case OP_MUL: ARITHMETIC_BINARY_OP(*, multiply); break;
    case OP_DIV: ARITHMETIC_BINARY_OP(/, slash); break;
    case OP_REM: ARITHMETIC_BINARY_OP(%, remainder); break;
    case OP_GOTO: {
      int byteOffset = _2btos(vm.ip);
      vm.ip = vm.chunk->code + byteOffset;
      break;
    }
    case OP_IFEQ: IF_CMP(==, equal); break;
    case OP_IFNE: IF_CMP(!=, not equal); break;
    case OP_IFGT: IF_CMP(>, greater); break;
    case OP_IFGE: IF_CMP(>=, greater equal); break;
    case OP_IFLT: IF_CMP(<, lesser); break;
    case OP_IFLE: IF_CMP(<=, lesser equal); break;
    case OP_RETURN: {
      return INTERPRET_OK;
    }
    case ATTR_LINE: {
      vm.line = _2btos(vm.ip);
      break;    
    }
    }

    if (vm.terminate)
      return INTERPRET_ERROR;
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef ARITHMETIC_BINARY_OP
#undef LOGICAL_BINARY_OP
#undef CMP_BINARY_OP
}
