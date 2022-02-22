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
  vm.stackTop += vm.stackCount += 1;
}

Value peek(int distance) { return vm.stackTop[-1 - distance]; }

Value pop() {
  if (!vm.stackCount) {
    runtimeError("Invalid operand. No operands on stack.");
    vm.terminate = 1;
  }

  vm.stackTop -= vm.stackCount -= 1;
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
    case OP_CONST_0: push(BOOL_VAL(false)); break;
    case OP_CONST_1: push(BOOL_VAL(true)); break;
    case OP_DUMP: {
      Value v = pop();

      if (vm.terminate) break;

      if (IS_INT(v)) {
        printf("%d\n", AS_INT(v));
      } else if (IS_BOOL(v)) {
        printf("%s\n", AS_BOOL(v) ? "true" : "false");
      }
      break;
    }
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
}
