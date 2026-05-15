#include "../../include/lifter/lift.h"
#include "../../include/lifter/ir.h"
#include "../../include/datastructures/ast.h"
#include <stdint.h>

extern DynamicArray* labels;

/* =========================================
 * MOV INSTRUCTIONS
 * ========================================= */

// [#op_a] = #op_b
void lift_mov10(DecodedInstr instr) {
    ast_node_t* rhs = build_imm(instr.op_b);
    set_current_state(ctx, instr.op_a, rhs);
}

// [#op_a] = [#op_b]
void lift_mov11(DecodedInstr instr) {
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);
    set_current_state(ctx, instr.op_a, rhs);
}

// [#op_a] = [[#op_b]]
void lift_mov12(DecodedInstr instr) {
    ast_node_t* ptr_addr = get_current_state(ctx, instr.op_b);
    ast_node_t* rhs = build_load(ptr_addr);
    set_current_state(ctx, instr.op_a, rhs);
}

// [[#op_a]] = #op_b
void lift_mov20(DecodedInstr instr) {
    ast_node_t* ptr_addr = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = build_imm(instr.op_b);

    // Dynamic memory writes are Side Effects, not static state changes
    ast_node_t* store_node = build_store(ptr_addr, rhs);
    push_back(ctx->side_effects, &store_node);
}

// [[#op_a]] = [#op_b]
void lift_mov21(DecodedInstr instr) {
    ast_node_t* ptr_addr = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);

    ast_node_t* store_node = build_store(ptr_addr, rhs);
    push_back(ctx->side_effects, &store_node);
}

// [[#op_a]] = [[#op_b]]
void lift_mov22(DecodedInstr instr) {
    ast_node_t* dest_ptr = get_current_state(ctx, instr.op_a);
    ast_node_t* src_ptr = get_current_state(ctx, instr.op_b);

    ast_node_t* rhs = build_load(src_ptr);
    ast_node_t* store_node = build_store(dest_ptr, rhs);
    push_back(ctx->side_effects, &store_node);
}

/* =========================================
 * BITWISE INSTRUCTIONS
 * ========================================= */

// [#op_a] = AND([#op_a], #op_b)
void lift_and10(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = build_imm(instr.op_b);
    ast_node_t* result = build_and(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = AND([#op_a], [#op_b])
void lift_and11(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);
    ast_node_t* result = build_and(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = OR([#op_a], #op_b)
void lift_or10(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = build_imm(instr.op_b);
    ast_node_t* result = build_or(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = OR([#op_a], [#op_b])
void lift_or11(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);
    ast_node_t* result = build_or(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = NOT([#op_a])
void lift_not(DecodedInstr instr) {
    ast_node_t* src = get_current_state(ctx, instr.op_a);
    ast_node_t* result = build_not(src);
    set_current_state(ctx, instr.op_a, result);
}

/* =========================================
 * ARITHMETIC INSTRUCTIONS
 * ========================================= */

// [#op_a] = ADD([#op_a], #op_b)
void lift_add10(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = build_imm(instr.op_b);
    ast_node_t* result = build_add(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = ADD([#op_a], [#op_b])
void lift_add11(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);
    ast_node_t* result = build_add(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = SUB([#op_a], #op_b)
void lift_sub10(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = build_imm(instr.op_b);
    ast_node_t* result = build_sub(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = SUB([#op_a], [#op_b])
void lift_sub11(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);
    ast_node_t* result = build_sub(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = MUL([#op_a], #op_b)
void lift_mul10(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = build_imm(instr.op_b);
    ast_node_t* result = build_mul(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

// [#op_a] = MUL([#op_a], [#op_b])
void lift_mul11(DecodedInstr instr) {
    ast_node_t* lhs = get_current_state(ctx, instr.op_a);
    ast_node_t* rhs = get_current_state(ctx, instr.op_b);
    ast_node_t* result = build_mul(lhs, rhs);
    set_current_state(ctx, instr.op_a, result);
}

/* =========================================
 * CONTROL FLOW INSTRUCTIONS (Terminators)
 * ========================================= */

// Branch if [#op_a] == 0 to #op_b
void lift_jumpz10(DecodedInstr instr) {
    ast_node_t* cond = get_current_state(ctx, instr.op_a);
    ast_node_t* true_target = build_imm(instr.op_b);
    ast_node_t* false_target = build_imm(instr.mem_addr + 1); // Instruction after this

    ast_node_t* branch_node = build_branch(cond, true_target, false_target);
    ctx->terminator = branch_node; // This explicitly ends the Basic Block
}

// Branch if [#op_a] == 0 to [#op_b]
void lift_jumpz11(DecodedInstr instr) {
    ast_node_t* cond = get_current_state(ctx, instr.op_a);
    ast_node_t* true_target = get_current_state(ctx, instr.op_b);
    ast_node_t* false_target = build_imm(instr.mem_addr + 1);

    ast_node_t* branch_node = build_branch(cond, true_target, false_target);
    ctx->terminator = branch_node;
}

// Branch if [#op_a] != 0 to #op_b
void lift_jumpnz10(DecodedInstr instr) {
    ast_node_t* cond = get_current_state(ctx, instr.op_a);
    ast_node_t* true_target = build_imm(instr.mem_addr + 1);
    ast_node_t* false_target = build_imm(instr.op_b);

    ast_node_t* branch_node = build_branch(cond, true_target, false_target);
    ctx->terminator = branch_node;
}

// Branch if [#op_a] != 0 to [#op_b]
void lift_jumpnz11(DecodedInstr instr) {
    ast_node_t* cond = get_current_state(ctx, instr.op_a);
    ast_node_t* true_target = build_imm(instr.mem_addr + 1);
    ast_node_t* false_target = get_current_state(ctx, instr.op_b);

    ast_node_t* branch_node = build_branch(cond, true_target, false_target);
    ctx->terminator = branch_node;
}

/* =========================================
 * MISCELLANEOUS INSTRUCTIONS
 * ========================================= */

void lift_syscall(DecodedInstr instr) {
    // Syscalls have unknown external effects, so they belong in side effects.
    // ast_node_t* syscall_node = build_syscall(instr.op_a);
    // push_back(ctx->side_effects, &syscall_node);
}

void lift_end(DecodedInstr instr) {
    ast_node_t* halt_node = build_halt();
    ctx->terminator = halt_node;
}