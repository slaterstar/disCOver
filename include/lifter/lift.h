#ifndef LIFT_H
#define LIFT_H

#include "../disassembler/structs.h"
#include "../../include/lifter/ir.h"
#include "../../include/lifter/ir_construction.h"
#include <stdint.h>

void lift_mov10(DecodedInstr instr);
void lift_mov11(DecodedInstr instr);
void lift_mov12(DecodedInstr instr);
void lift_mov20(DecodedInstr instr);
void lift_mov21(DecodedInstr instr);
void lift_mov22(DecodedInstr instr);

void lift_and10(DecodedInstr instr);
void lift_and11(DecodedInstr instr);
void lift_or10(DecodedInstr instr);
void lift_or11(DecodedInstr instr);
// void lift_xor(DecodedInstr instr);
// void lift_not(DecodedInstr instr);

void lift_add10(DecodedInstr instr);
void lift_add11(DecodedInstr instr);
void lift_sub10(DecodedInstr instr);
void lift_sub11(DecodedInstr instr);
void lift_mul10(DecodedInstr instr);
void lift_mul11(DecodedInstr instr);
// void lift_div(DecodedInstr instr);



// void lift_jump(DecodedInstr instr);
void lift_jumpz10(DecodedInstr instr);
void lift_jumpz11(DecodedInstr instr);
void lift_jumpnz10(DecodedInstr instr);
void lift_jumpnz11(DecodedInstr instr);

void lift_not(DecodedInstr instr);
void lift_syscall(DecodedInstr instr);

void lift_end(DecodedInstr instr);
#endif