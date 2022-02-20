#include <stdarg.h>
#include <math.h>
#include <stdio.h>

#include "common.h"
#include "vm.h"

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

static void runtimeError(const char *format, ...)
{
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

InterpretResult interpret(Chunk *chunk)
{
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

void push(Value value)
{
  *vm.stackTop = value;
  vm.stackTop++;
}

Value peek(int distance)
{
  return vm.stackTop[-1 - distance];
}

Value pop()
{
  vm.stackTop--;
  return *vm.stackTop;
}

InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;)
  {
    u8 instruction;
    switch (instruction = READ_BYTE())
    {
    case OP_CONST:
    {
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
      if (!IS_INT(peek(0)))
      {
        runtimeError("Operand must be a number.");
        return INTERPRET_ERROR;
      }
      push(INT_VAL(-AS_INT(pop())));
      break;
    // case OP_ADD:
    // {
    //   Value v1 = pop();
    //   Value v2 = pop();
    //   push(v1 + v2);
    //   break;
    // }
    // case OP_SUB:
    // {
    //   Value v1 = pop();
    //   Value v2 = pop();
    //   push(v2 - v1);
    //   break;
    // }
    // case OP_MUL:
    // {
    //   Value v1 = pop();
    //   Value v2 = pop();
    //   push(v2 * v1);
    //   break;
    // }
    // case OP_DIV:
    // {
    //   Value v1 = pop();
    //   Value v2 = pop();
    //   push(v2 / v1);
    //   break;
    // }
    // case OP_REM:
    // {
    //   Value v1 = pop();
    //   Value v2 = pop();
    //   push(fmod(v2, v1));
    //   break;
    // }
    case OP_RETURN:
    {
      return INTERPRET_OK;
    }
    case ATTR_LINE:
    {
      vm.line = _4btoi(vm.ip);
    }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}
