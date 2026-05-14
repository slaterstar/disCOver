#include "../../include/lifter/lift.h"
#include "../../include/lifter/ir_builder.h" // Assuming this is where build_* functions live

extern IRContext* ctx;

/* --- MEMORY LIFTERS --- */

/*
 * t0 = ASSIGN(0xAA)
 * t1 = ASSIGN(0x100)
 * STORE(t1, t0)
 */
void lift_mov10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    build_store(ctx, vreg1, vreg0, instr.mem_addr);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * t2 = ASSIGN(0xAA)
 * STORE(t2, t1)
 */
void lift_mov11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg2 = build_assign(ctx, instr.op_a, instr.mem_addr);
    build_store(ctx, vreg1, vreg2, instr.mem_addr);
}

/*
 * t0 = ASSIGN(0x100)
 * t1 = LOAD(t0)
 * t2 = LOAD(t1)
 * t3 = ASSIGN(0xAA)
 * STORE(t3, t2)
 */
void lift_mov12(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg1, instr.mem_addr);
    int vreg3 = build_assign(ctx, instr.op_a, instr.mem_addr);
    build_store(ctx, vreg3, vreg2, instr.mem_addr);
}

/*
 * t0 = ASSIGN(0xAA)
 * t1 = ASSIGN(0x100)
 * t2 = LOAD(t1)
 * STORE(t2, t0)
 */
void lift_mov20(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg1, instr.mem_addr);
    build_store(ctx, vreg1, vreg0, instr.mem_addr);
}

/*
 * t0 = ASSIGN(0xAA)
 * t1 = LOAD(t0)
 * t2 = ASSIGN(0x100)
 * t3 = LOAD(t2)
 * STORE(t3, t1)
 */
void lift_mov21(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg2 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg2, instr.mem_addr);
    build_store(ctx, vreg2, vreg1, instr.mem_addr);
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
    int vreg0 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg1, instr.mem_addr);
    int vreg3 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg4 = build_load(ctx, vreg3, instr.mem_addr);
    build_store(ctx, vreg3, vreg2, instr.mem_addr);
}

/* --- ALU LIFTERS --- */

void lift_and10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);

    int vreg3 = build_alu(ctx, vreg1, (Operand){.type = OP_REGISTER, .value.reg = vreg2}, OPCODE_AND, instr.mem_addr);
    build_store(ctx, vreg0, vreg3, instr.mem_addr);
}

void lift_and11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    int vreg4 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg3}, OPCODE_AND, instr.mem_addr);
    build_store(ctx, vreg0, vreg4, instr.mem_addr);
}

void lift_or10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);

    int vreg3 = build_alu(ctx, vreg1, (Operand){.type = OP_REGISTER, .value.reg = vreg2}, OPCODE_OR, instr.mem_addr);
    build_store(ctx, vreg0, vreg3, instr.mem_addr);
}

void lift_or11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    int vreg4 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg3}, OPCODE_OR, instr.mem_addr);
    build_store(ctx, vreg0, vreg4, instr.mem_addr);
}

void lift_add10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);

    int vreg3 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg1}, OPCODE_ADD, instr.mem_addr);
    build_store(ctx, vreg0, vreg3, instr.mem_addr);
}

void lift_add11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    int vreg4 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg3}, OPCODE_ADD, instr.mem_addr);
    build_store(ctx, vreg0, vreg4, instr.mem_addr);
}

void lift_sub10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);

    int vreg3 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg1}, OPCODE_SUB, instr.mem_addr);
    build_store(ctx, vreg0, vreg3, instr.mem_addr);
}

void lift_sub11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    int vreg4 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg3}, OPCODE_SUB, instr.mem_addr);
    build_store(ctx, vreg0, vreg4, instr.mem_addr);
}

void lift_mul10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);

    int vreg3 = build_alu(ctx, vreg1, (Operand){.type = OP_REGISTER, .value.reg = vreg2}, OPCODE_MUL, instr.mem_addr);
    build_store(ctx, vreg0, vreg3, instr.mem_addr);
}

void lift_mul11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    int vreg4 = build_alu(ctx, vreg2, (Operand){.type = OP_REGISTER, .value.reg = vreg3}, OPCODE_MUL, instr.mem_addr);
    build_store(ctx, vreg0, vreg4, instr.mem_addr);
}

/* --- CONTROL FLOW LIFTERS --- */

void lift_jumpz10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);

    Operand true_op = (Operand){.type = OP_MEMORY_ADDR, .value.mem = instr.op_b};
    Operand false_op = (Operand){.type = OP_MEMORY_ADDR, .value.mem = instr.mem_addr + 1};

    build_branch(ctx, vreg1, true_op, false_op, instr.mem_addr);
}

void lift_jumpz11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr); // Assuming op_a is immediate
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    Operand true_op = (Operand){.type = OP_REGISTER, .value.reg = vreg3};
    Operand false_op = (Operand){.type = OP_MEMORY_ADDR, .value.mem = instr.mem_addr + 1};

    build_branch(ctx, vreg2, true_op, false_op, instr.mem_addr);
}

void lift_jumpnz10(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);

    Operand true_op = (Operand){.type = OP_MEMORY_ADDR, .value.mem = instr.mem_addr + 1};
    Operand false_op = (Operand){.type = OP_MEMORY_ADDR, .value.mem = instr.op_b};

    build_branch(ctx, vreg1, true_op, false_op, instr.mem_addr);
}

void lift_jumpnz11(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_assign(ctx, instr.op_b, instr.mem_addr);
    int vreg2 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg3 = build_load(ctx, vreg1, instr.mem_addr);

    Operand true_op = (Operand){.type = OP_MEMORY_ADDR, .value.mem = instr.mem_addr + 1};
    Operand false_op = (Operand){.type = OP_REGISTER, .value.reg = vreg3};

    build_branch(ctx, vreg2, true_op, false_op, instr.mem_addr);
}

/* --- MISC LIFTERS --- */

void lift_not(DecodedInstr instr){
    int vreg0 = build_assign(ctx, instr.op_a, instr.mem_addr);
    int vreg1 = build_load(ctx, vreg0, instr.mem_addr);
    int vreg2 = build_not(ctx, vreg1, instr.mem_addr);

    build_store(ctx, vreg0, vreg2, instr.mem_addr);
}

void lift_syscall(DecodedInstr instr){
    // To be implemented using a build_syscall wrapper
}

void lift_end(DecodedInstr instr){
    build_halt(ctx, instr.mem_addr);
}