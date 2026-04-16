#include "../../include/lifter/lift.h"
#include "../../include/lifter/ir.h"
#include <stdint.h>


extern IRContext* ctx;
extern DynamicArray* labels;
/*
 * t0 = ASSIGN(0xAA)
 * t1 = ASSIGN(0x100)
 * STORE(t1, t0)
 */

void lift_mov10(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.mem_addr = instr.mem_addr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_a;

    add_instruction(ctx, ir_instr);
    int vreg1 = new_reg(ctx);

    ir_instr.mem_addr = -1;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg1;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);

    ir_instr.mem_addr = -1;
    ir_instr.opcode = OPCODE_STORE;
    Operand dest_addr;
    dest_addr.type = OP_REGISTER;
    dest_addr.value.reg = vreg1;
    ir_instr.store.dest_addr = dest_addr;

    Operand src_reg;
    src_reg.type = OP_REGISTER;
    src_reg.value.reg = vreg0;
    ir_instr.store.src_reg = src_reg;
    add_instruction(ctx, ir_instr);
}
/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * t2 = ASSIGN(0xAA)
 * STORE(t2, t1)
 */
void lift_mov11(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.mem_addr = instr.mem_addr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);

    ir_instr.mem_addr = -1;
    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg1;
    ir_instr.load.src = vreg0;
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg2;
    ir_instr.assign.const_val = op_a;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_MEMORY_ADDR, .value = { .mem = vreg1 } };
    ir_instr.store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg2 } };
    add_instruction(ctx, ir_instr);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * t2 = LOAD(t1)
 * t3 = ASSIGN(0xAA)
 * STORE(t3, t2)
 */
void lift_mov12(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.mem_addr = instr.mem_addr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);
    ir_instr.mem_addr = -1;
    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg1;
    ir_instr.load.src = vreg0;
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg2;
    ir_instr.load.src = vreg1;
    add_instruction(ctx, ir_instr);

    int vreg3 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg3;
    ir_instr.assign.const_val = op_a;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_MEMORY_ADDR, .value = { .mem = vreg3 } };
    ir_instr.store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg2 } };
    add_instruction(ctx, ir_instr);
}
/*
 * t0 = ASSIGN(0xAA)
 * t1 = ASSIGN(0x100)
 * t2 = LOAD(t1)
 * STORE(t2, t0)
 */
void lift_mov20(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.mem_addr = instr.mem_addr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);
    ir_instr.mem_addr = -1;
    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg1;
    ir_instr.assign.const_val = op_a;
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg2;
    ir_instr.load.src = vreg1;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg1 } };
    ir_instr.store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg0 } };
    add_instruction(ctx, ir_instr);
}

/*
 * t0 = ASSIGN(0xAA)
 * t1 = LOAD(t0)
 * t2 = ASSIGN(0x100)
 * t3 = LOAD(t2)
 * STORE(t3, t1)
 */
void lift_mov21(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.mem_addr = instr.mem_addr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);
    ir_instr.mem_addr = -1;

    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg1;
    ir_instr.load.src = vreg0;
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg2;
    ir_instr.assign.const_val = op_a;
    add_instruction(ctx, ir_instr);

    int vreg3 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg3;
    ir_instr.load.src = vreg2;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg2 } };
    ir_instr.store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg1 } };
    add_instruction(ctx, ir_instr);
}

/*
 * t0 = ASSIGN(0xAA)
 * t1 = LOAD(t0)
 * t2 = LOAD(t1)
 * t3 = ASSIGN(0x100)
 * t4 = LOAD(t3)
 * STORE(t4, t2)
 */
void lift_mov22(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);
    IRInstruction ir_instr;
    ir_instr.mem_addr = instr.mem_addr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);
    ir_instr.mem_addr = -1;

    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg1;
    ir_instr.load.src = vreg0;
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg2;
    ir_instr.load.src = vreg1;
    add_instruction(ctx, ir_instr);

    int vreg3 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg3;
    ir_instr.assign.const_val = op_a;
    add_instruction(ctx, ir_instr);

    int vreg4 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg4;
    ir_instr.load.src = vreg3;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg3 } };
    ir_instr.store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg2 } };
    add_instruction(ctx, ir_instr);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = AND(t1, t2)
 * STORE(t0, t3)
 */
void lift_and10(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * t4 = AND(t2, t3)
 * STORE(t0, t4)
 */
void lift_and11(DecodedInstr instr){
    int op_a = instr.op_a;
    int op_b = instr.op_b;

    IRInstruction ir_instr;

    int vreg0 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_a;
    ir_instr.mem_addr = instr.mem_addr;
    add_instruction(ctx, ir_instr);
    ir_instr.mem_addr = -1;

    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg1;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg2;
    ir_instr.load.src = vreg0;
    add_instruction(ctx, ir_instr);

    int vreg3 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg3;
    ir_instr.load.src = vreg1;
    add_instruction(ctx, ir_instr);

    int vreg4 = new_reg(ctx);
    ir_instr.opcode = OPCODE_AND;
    ir_instr.alu.dest_reg = vreg3;
    ir_instr.alu.src1_reg = vreg2;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){.type = OP_REGISTER, .value.reg = vreg0};
    ir_instr.store.src_reg = (Operand){.type = OP_REGISTER, .value.reg = vreg4};
    add_instruction(ctx, ir_instr);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = OR(t1, t2)
 * STORE(t0, t3)
 */
void lift_or10(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * t4 = OR(t2, t3)
 * STORE(t0, t4)
 */
void lift_or11(DecodedInstr instr){

}


/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = ADD(t1, t2)
 * STORE(t0, t3)
 */
void lift_add10(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * t4 = ADD(t2, t3)
 * STORE(t0, t4)
 */
void lift_add11(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = SUB(t2, t1)
 * STORE(t0, t3)
 */
void lift_sub10(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * t4 = SUB(t2, t3)
 * STORE(t0, t4)
 */
void lift_sub11(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = MUL(t1, t2)
 * STORE(t0, t3)
 */
void lift_mul10(DecodedInstr instr){

}

/*
 * t0 = ASSIGN(0x100)
 * t1 = ASSIGN(0x200)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * t4 = MUL(t2, t3)
 * STORE(t0, t4)
 */
void lift_mul11(DecodedInstr instr){

}
// void lift_div(DecodedInstr instr);


// MODIFY LABEL PAIR TO ACCEPT A REGISTER.
// void lift_jump(DecodedInstr instr);
/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * BRANCH(t1, op_b, %0 ) // Create TRUE_Label at op_b, FALSE_Label at the instruction after this
 */
void lift_jumpz10(DecodedInstr instr){
    // Ways to add labels:
    // Create
    LabelPair true_label;
    LabelPair false_label;
    IRInstruction ir_instr;
    int vreg0 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg0,
        .assign.const_val = instr.op_a,
        .mem_addr = instr.mem_addr
    };
    add_instruction(ctx, ir_instr);

    int vreg1 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg1,
        .load.src = vreg0,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    new_label(ctx, instr.op_b, MEM, &true_label);
    new_label(ctx, instr.mem_addr + 1, MEM, &false_label);

    ir_instr = (IRInstruction) {
        .opcode = OPCODE_BRANCH,
        .branch = {
            .cond_reg = vreg1,
            .true_label = true_label.label_index,
            .false_label = false_label.label_index,
        },
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    push_back(labels, &true_label);
    push_back(labels, &false_label);

}
/*
 * t0 = ASSIGN(op_a)
 * t1 = ASSIGN(op_b)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * BRANCH(t2, t3, %0 ) // Create TRUE_Label at t1, FALSE_Label at the instruction after this
 */
void lift_jumpz11(DecodedInstr instr){
    LabelPair true_label;
    LabelPair false_label;
    IRInstruction ir_instr;
    int vreg0 = instr.op_a;
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg0,
        .assign.const_val = instr.op_a,
        .mem_addr = instr.mem_addr
    };
    add_instruction(ctx, ir_instr);

    int vreg1 = instr.op_b;
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg1,
        .assign.const_val = instr.op_b,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg2,
        .load.src = vreg0,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    int vreg3 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg3,
        .load.src = vreg1,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    new_label(ctx, vreg3, REG, &true_label); // Need register to be put here.
    new_label(ctx, instr.mem_addr + 1, MEM, &false_label);

    ir_instr = (IRInstruction) {
        .opcode = OPCODE_BRANCH,
        .branch = {
            .cond_reg = vreg2,
            .true_label = true_label.label_index,
            .false_label = false_label.label_index,
        },
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    push_back(labels, &true_label);
    push_back(labels, &false_label);
}

/*
 * t0 = ASSIGN(op_a)
 * t1 = LOAD(t0)
 * BRANCH(t1, %0, op_b ) // Create TRUE_Label at instruction after, FALSE_Label at op_b
 */
void lift_jumpnz10(DecodedInstr instr){
    LabelPair true_label;
    LabelPair false_label;
    IRInstruction ir_instr;
    int vreg0 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg0,
        .assign.const_val = instr.op_a,
        .mem_addr = instr.mem_addr
    };
    add_instruction(ctx, ir_instr);

    int vreg1 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg1,
        .load.src = vreg0,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    new_label(ctx, instr.mem_addr + 1, MEM, &true_label);
    new_label(ctx, instr.op_b, MEM, &false_label);

    ir_instr = (IRInstruction) {
        .opcode = OPCODE_BRANCH,
        .branch = {
            .cond_reg = vreg1,
            .true_label = true_label.label_index,
            .false_label = false_label.label_index,
        },
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    push_back(labels, &true_label);
    push_back(labels, &false_label);

}
/*
 * t0 = ASSIGN(op_a)
 * t1 = ASSIGN(op_b)
 * t2 = LOAD(t0)
 * t3 = LOAD(t1)
 * BRANCH(t2, %0, t3 ) // Create TRUE_Label at instruction after, FALSE_Label at t3
 */
void lift_jumpnz11(DecodedInstr instr){
    LabelPair true_label;
    LabelPair false_label;
    IRInstruction ir_instr;
    int vreg0 = instr.op_a;
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg0,
        .assign.const_val = instr.op_a,
        .mem_addr = instr.mem_addr
    };
    add_instruction(ctx, ir_instr);

    int vreg1 = instr.op_b;
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg1,
        .assign.const_val = instr.op_b,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg2,
        .load.src = vreg0,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    int vreg3 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg3,
        .load.src = vreg1,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    new_label(ctx, instr.mem_addr + 1, MEM, &true_label);
    new_label(ctx, vreg3, REG, &false_label);

    ir_instr = (IRInstruction) {
        .opcode = OPCODE_BRANCH,
        .branch = {
            .cond_reg = vreg2,
            .true_label = true_label.label_index,
            .false_label = false_label.label_index,
        },
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    push_back(labels, &true_label);
    push_back(labels, &false_label);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * t2 = NOT(t1)
 * STORE(t0, t2)
 */
void lift_not(DecodedInstr instr){
    uint32_t op_a = instr.op_a;

    int vreg0 = new_reg(ctx);
    IRInstruction ir_instr;
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_ASSIGN,
        .assign.dest_reg = vreg0,
        .assign.const_val = op_a,
        .mem_addr = instr.mem_addr
    };
    add_instruction(ctx, ir_instr);

    int vreg1 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_LOAD,
        .load.dest_reg = vreg1,
        .load.src = vreg0,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    int vreg2 = new_reg(ctx);
    ir_instr = (IRInstruction) {
        .opcode = OPCODE_NOT,
        .alu.dest_reg = vreg2,
        .alu.src1_reg = vreg1,
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);

    ir_instr = (IRInstruction) {
        .opcode = OPCODE_STORE,
        .store.dest_addr = (Operand){ .type = OP_MEMORY_ADDR, .value = { .mem = vreg0 } },
        .store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg2 } },
        .mem_addr = -1
    };
    add_instruction(ctx, ir_instr);
}

void lift_syscall(DecodedInstr instr){

}

void lift_end(DecodedInstr instr){
    IRInstruction end_instr = {
        .opcode = OPCODE_HALT,
    };
    end_instr.mem_addr = instr.mem_addr;
    add_instruction(ctx, end_instr);
}
