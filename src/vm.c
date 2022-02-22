#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "common.h"
#include "loader.h"
#include "vm.h"

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

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

void initVM() { resetStack(); }

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
}

Value peek(int distance) { return vm.stackTop[-1 - distance]; }

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define ARITHMETIC_BINARY_OP(op) \
  { \
    if (IS_INT(peek(0)) && IS_INT(peek(1))) { \
      int b = AS_INT(pop()); \
      int a = AS_INT(pop()); \
      push(INT_VAL(a op b)); \
    } else { \
      runtimeError("Cannot aaply operator `%s`", #op); \
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
    case OP_DUMP:
      if (IS_INT(peek(0))) {
        printf("%d\n", AS_INT(pop()));
      }
      break;
    case OP_NEG:
      if (!IS_INT(peek(0))) {
        runtimeError("Operand must be a number.");
        return INTERPRET_ERROR;
      }
      push(INT_VAL(-AS_INT(pop())));
      break;
    case OP_ADD: ARITHMETIC_BINARY_OP(+); break;
    case OP_SUB: ARITHMETIC_BINARY_OP(-); break;
    case OP_MUL: ARITHMETIC_BINARY_OP(*); break;
    case OP_DIV: ARITHMETIC_BINARY_OP(/); break;
    case OP_REM:
    {
      runtimeError("Not implemented");
      break;
    }
    case OP_RETURN: {
      return INTERPRET_OK;
    }
    case ATTR_LINE: {
      vm.line = _4btoi(vm.ip);
    }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}
