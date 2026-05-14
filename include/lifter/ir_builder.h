#ifndef IR_BUILDER_H
#define IR_BUILDER_H
#include "ir_construction.h"
#include "enums.h"
#include "ir.h"
#include <stdint.h>

int build_assign(int ctx, uint32_t value, int mem_addr);
int build_load(int ctx, int reg, int mem_addr);
int build_store(int ctx, int reg, int value, int mem_addr);
int build_alu(int ctx, int reg1, Operand op2, int opcode, int mem_addr);

#endif // IR_BUILDER_H
