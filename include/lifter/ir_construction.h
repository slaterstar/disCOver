#include "ir.h"
#include "enums.h"

int construct_phi(IRInstruction *inst, int dest_reg, int *src_regs, int num_srcs);

int construct_alu(IRInstruction *inst, int dest_reg, int src1_reg, Operand src2, IROpcode opcode);

int construct_compare(IRInstruction *inst, int dest_reg, int src1_reg, Operand src2, IROpcode opcode);

int construct_branch(IRInstruction *inst, int cond_reg, Operand true_reg, Operand false_reg);

int construct_jump(IRInstruction *inst, Operand label);

int construct_store(IRInstruction *inst, int dest_mem, int src_reg);

int construct_load(IRInstruction *inst, int dest_reg, int src_mem);

int construct_assign(IRInstruction *inst, int dest_reg, int const_val);