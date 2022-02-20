#include <math.h>
#include <stdio.h>

#include "common.h"
#include "vm.h"

VM vm;

static void resetStack() { vm.stackTop = vm.stack; }

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

Value pop()
{
  vm.stackTop--;
  return *vm.stackTop;
}

InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  int line = 0;

  // for (;;)
  // {
  //   u8 instruction;
  //   switch (instruction = READ_BYTE())
  //   {
  //   case OP_CONST:
  //   {
  //     Value constant = READ_CONSTANT();
  //     push(constant);
  //     break;
  //   }
  //   case OP_DUMP:
  //     printf("%g\n", pop());
  //     break;
  //   case OP_NEG:
  //     push(-pop());
  //     break;
  //   case OP_ADD:
  //   {
  //     Value v1 = pop();
  //     Value v2 = pop();
  //     push(v1 + v2);
  //     break;
  //   }
  //   case OP_SUB:
  //   {
  //     Value v1 = pop();
  //     Value v2 = pop();
  //     push(v2 - v1);
  //     break;
  //   }
  //   case OP_MUL:
  //   {
  //     Value v1 = pop();
  //     Value v2 = pop();
  //     push(v2 * v1);
  //     break;
  //   }
  //   case OP_DIV:
  //   {
  //     Value v1 = pop();
  //     Value v2 = pop();
  //     push(v2 / v1);
  //     break;
  //   }
  //   case OP_REM:
  //   {
  //     Value v1 = pop();
  //     Value v2 = pop();
  //     push(fmod(v2, v1));
  //     break;
  //   }
  //   case OP_RETURN:
  //   {
  //     return INTERPRET_OK;
  //   }
  //   case ATTR_LINE:
  //   {
  //     line = _4btoi(vm.ip);
  //   }
  //   }
  // }

#undef READ_BYTE
#undef READ_CONSTANT
}
