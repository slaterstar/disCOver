#include "../../include/lifter/lift.h"
#include "../../include/lifter/ir.h"
#include <stdint.h>


extern IRContext* ctx;
extern DynamicArray* labels;
/*
 * t0 = ASSIGN(0xAA)
 * STORE(0x100, t0)
 */

void lift_mov10(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg;
    ir_instr.assign.const_val = op_b;

    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    Operand dest_addr;
    dest_addr.type = OP_MEMORY_ADDR;
    dest_addr.value.mem = op_a;
    ir_instr.store.dest_addr = dest_addr;

    Operand src_reg;
    src_reg.type = OP_REGISTER;
    src_reg.value.reg = vreg;
    ir_instr.store.src_reg = src_reg;
    add_instruction(ctx, ir_instr);
}
/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * STORE(0xAA, t1)
 */
void lift_mov11(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);
    int vreg1 = new_reg(ctx);
    ir_instr.opcode = OPCODE_LOAD;
    ir_instr.load.dest_reg = vreg1;
    ir_instr.load.src = vreg0;
    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_MEMORY_ADDR, .value = { .mem = op_a } };
    ir_instr.store.src_reg = (Operand){ .type = OP_REGISTER, .value = { .reg = vreg1 } };
    add_instruction(ctx, ir_instr);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * t2 = LOAD(t1)
 * STORE(0xAA, t2)
 */
void lift_mov12(DecodedInstr instr){
    // uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg0 = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);
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

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = (Operand){ .type = OP_MEMORY_ADDR, .value = { .mem = op_a } };
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
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);

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
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);

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
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = vreg0;
    ir_instr.assign.const_val = op_b;
    add_instruction(ctx, ir_instr);

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
 * t3 = SUB(t1, t2)
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



// void lift_jump(DecodedInstr instr);
/*
 * t0 = ASSIGN(op_a)
 * BRANCH(t0, op_b, %0 ) // Create TRUE_Label at op_b, FALSE_Label at the instruction after this
 */
void lift_jumpz10(DecodedInstr instr){
    // Ways to add labels:
    // Create
    int true_label = new_label(ctx);

    int false_label = new_label(ctx);

}
void lift_jumpz11(DecodedInstr instr){

}
void lift_jumpnz10(DecodedInstr instr){

}
void lift_jumpnz11(DecodedInstr instr){

}

void lift_not(DecodedInstr instr){

}

void lift_syscall(DecodedInstr instr){

}

void lift_end(DecodedInstr instr){
    IRInstruction end_instr = {
        .opcode = OPCODE_HALT,
    };
    add_instruction(ctx, end_instr);
}
