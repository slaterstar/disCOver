#include "../../include/lifter/ir_construction.h"

int construct_phi(IRInstruction *inst, int dest_reg, int *src_regs, int num_srcs){

}

int construct_alu(IRInstruction *inst, int dest_reg, int src1_reg, Operand src2, IROpcode opcode){
    inst->opcode = opcode;
    inst->alu.dest_reg = dest_reg;
    inst->alu.src1_reg = src1_reg;
    inst->alu.src2 = src2;

}

int construct_compare(IRInstruction *inst, int dest_reg, int src1_reg, Operand src2, IROpcode opcode){
    inst->opcode = opcode;
    inst->comp.dest_reg = dest_reg;
    inst->comp.src1_reg = src1_reg;
    inst->comp.src2 = src2;
}

int construct_branch(IRInstruction *inst, int cond_reg, Operand true_value, Operand false_value){
    inst->opcode = OPCODE_BRANCH;
    inst->branch.cond_reg = cond_reg;
    inst->branch.true_val = true_value;
    inst->branch.false_val = false_value;
}

int construct_jump(IRInstruction *inst, Operand value){
    inst->opcode = OPCODE_JUMP;
    inst->jump.label = value;

    return 0;
}