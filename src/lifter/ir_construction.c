#include "../../include/lifter/ir_construction.h"

// Make a function to get a GVN

int construct_phi(IRInstruction *inst, int dest_reg, int *src_regs, int num_srcs){
    inst->opcode = OPCODE_PHI;
    inst->phi.dest_reg = dest_reg;
    inst->phi.num_srcs = num_srcs;
    inst->phi.src_regs = malloc(num_srcs * sizeof(int));
    for (int i = 0; i < num_srcs; i++){
        inst->phi.src_regs[i] = src_regs[i];
    }
    return 0;
}

int construct_alu(IRInstruction *inst, int dest_reg, int src1_reg, Operand src2, IROpcode opcode){
    inst->opcode = opcode;
    inst->alu.dest_reg = dest_reg;
    inst->alu.src1_reg = src1_reg;
    inst->alu.src2 = src2;
    return 0;
}

int construct_compare(IRInstruction *inst, int dest_reg, int src1_reg, Operand src2, IROpcode opcode){
    inst->opcode = opcode;
    inst->comp.dest_reg = dest_reg;
    inst->comp.src1_reg = src1_reg;
    inst->comp.src2 = src2;
    return 0;
}

int construct_branch(IRInstruction *inst, int cond_reg, Operand true_value, Operand false_value){
    inst->opcode = OPCODE_BRANCH;
    inst->branch.cond_reg = cond_reg;
    inst->branch.true_val = true_value;
    inst->branch.false_val = false_value;
    return 0;
}

int construct_jump(IRInstruction *inst, Operand value){
    inst->opcode = OPCODE_JUMP;
    inst->jump.label = value;
    return 0;
}

int construct_store(IRInstruction *inst, int dest_mem, int src_reg){
    inst->opcode = OPCODE_STORE;
    inst->store.addr_reg = dest_mem;
    inst->store.data_reg = src_reg;
    return 0;
}

int construct_load(IRInstruction *inst, int dest_reg, int src_reg){
    inst->opcode = OPCODE_LOAD;
    inst->load.dest_reg = dest_reg;
    inst->load.src_reg = src_reg;
    return 0;
}

int construct_assign(IRInstruction *inst, int dest_reg, int const_val){
    inst->opcode = OPCODE_ASSIGN;
    inst->assign.dest_reg = dest_reg;
    inst->assign.const_val = const_val;
    return 0;
}