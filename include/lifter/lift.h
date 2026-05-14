#ifndef LIFT_H
#define LIFT_H

#include "../disassembler/structs.h"
#include "../../include/lifter/ir.h"
#include "../../include/lifter/ir_builder.h"
#include <stdint.h>

#include "../../include/lifter/ir.h"
#include "../../include/datastructures/ast.h"
#include <stdint.h>

extern IRContext* ctx;
extern DynamicArray* labels;

/* =========================================
 * MOV INSTRUCTIONS
 * ========================================= */

// [#op_a] = #op_b
void lift_mov10(DecodedInstr instr);
// [#op_a] = [#op_b]
void lift_mov11(DecodedInstr instr);
// [#op_a] = [[#op_b]]
void lift_mov12(DecodedInstr instr);
// [[#op_a]] = #op_b
void lift_mov20(DecodedInstr instr);

// [[#op_a]] = [#op_b]
void lift_mov21(DecodedInstr instr);

// [[#op_a]] = [[#op_b]]
void lift_mov22(DecodedInstr instr);

/* =========================================
 * BITWISE INSTRUCTIONS
 * ========================================= */

// [#op_a] = AND([#op_a], #op_b)
void lift_and10(DecodedInstr instr);
// [#op_a] = AND([#op_a], [#op_b])
void lift_and11(DecodedInstr instr);
// [#op_a] = OR([#op_a], #op_b)
void lift_or10(DecodedInstr instr);
// [#op_a] = OR([#op_a], [#op_b])
void lift_or11(DecodedInstr instr);
// [#op_a] = NOT([#op_a])
void lift_not(DecodedInstr instr);

/* =========================================
 * ARITHMETIC INSTRUCTIONS
 * ========================================= */

// [#op_a] = ADD([#op_a], #op_b)
void lift_add10(DecodedInstr instr);

// [#op_a] = ADD([#op_a], [#op_b])
void lift_add11(DecodedInstr instr);
// [#op_a] = SUB([#op_a], #op_b)
void lift_sub10(DecodedInstr instr);
// [#op_a] = SUB([#op_a], [#op_b])
void lift_sub11(DecodedInstr instr);
// [#op_a] = MUL([#op_a], #op_b)
void lift_mul10(DecodedInstr instr);
// [#op_a] = MUL([#op_a], [#op_b])
void lift_mul11(DecodedInstr instr);

/* =========================================
 * CONTROL FLOW INSTRUCTIONS (Terminators)
 * ========================================= */

// Branch if [#op_a] == 0 to #op_b
void lift_jumpz10(DecodedInstr instr);
// Branch if [#op_a] == 0 to [#op_b]
void lift_jumpz11(DecodedInstr instr);

// Branch if [#op_a] != 0 to #op_b
void lift_jumpnz10(DecodedInstr instr);

// Branch if [#op_a] != 0 to [#op_b]
void lift_jumpnz11(DecodedInstr instr);

/* =========================================
 * MISCELLANEOUS INSTRUCTIONS
 * ========================================= */

void lift_syscall(DecodedInstr instr);

void lift_end(DecodedInstr instr);
#endif