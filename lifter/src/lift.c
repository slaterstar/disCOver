#include "../include/lift.h"
#include "../include/ir.h"
#include <stdint.h>


extern IRContext* ctx;

/*
 * t0 = ASSIGN(0xAA)
 * STORE(0x100, t0)
 */

void mov10(DecodedInstr instr){
    uint8_t opcode = instr.opcode;
    uint32_t op_a = instr.op_a;
    uint32_t op_b = instr.op_b;

    int vreg = new_reg(ctx);

    IRInstruction ir_instr;
    ir_instr.opcode = OPCODE_ASSIGN;
    ir_instr.assign.dest_reg = op_a;
    ir_instr.assign.const_val = op_b;

    add_instruction(ctx, ir_instr);

    ir_instr.opcode = OPCODE_STORE;
    ir_instr.store.dest_addr = op_a;
    ir_instr.store.src_reg = op_b;
    add_instruction(ctx, ir_instr);
}
/*
 * t0 = LOAD(0x100)
 * STORE(0xAA, t0)
 */
void mov11(DecodedInstr instr){

}

/*
 * t0 = LOAD(0x100)
 * t1 =
 * STORE(0xAA, t0)
 */
void mov12(DecodedInstr instr){

}
void mov20(DecodedInstr instr){

}
void mov21(DecodedInstr instr){

}
void mov22(DecodedInstr instr){

}

void lift_and10(DecodedInstr instr){

}
void lift_and11(DecodedInstr instr){

}
void lift_or10(DecodedInstr instr){

}
void lift_or11(DecodedInstr instr){

}
// void lift_xor(DecodedInstr instr);
// void lift_not(DecodedInstr instr);

void lift_add10(DecodedInstr instr){

}
void lift_add11(DecodedInstr instr){

}
void lift_sub10(DecodedInstr instr){

}
void lift_sub11(DecodedInstr instr){

}
void lift_mul10(DecodedInstr instr){

}
void lift_mul11(DecodedInstr instr){

}
// void lift_div(DecodedInstr instr);



// void lift_jump(DecodedInstr instr);
void lift_jumpz10(DecodedInstr instr){

}
void lift_jumpz11(DecodedInstr instr){

}
void lift_jumpnz10(DecodedInstr instr){

}
void lift_jumpnz11(DecodedInstr instr){

}