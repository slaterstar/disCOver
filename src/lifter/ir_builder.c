#include "../../include/lifter/ir_builder.h"

// In ast.c we use the constructor to make the ast and lookup automatically.

ast_node_t* build_imm(uint32_t value) {
    // Immediate: No children, uses 'value'
    return make_node(OPCODE_IMMEDIATE, NULL, NULL, NULL, value);
}

ast_node_t* build_reg(int reg_index) {
    // Register: No children, uses 'reg_index'
    return make_node(OPCODE_REGISTER, NULL, NULL, NULL, reg_index);
}

ast_node_t* build_load(ast_node_t* addr) {
    // Load: Has a left child, no right child, no immediate value
    return make_node(OPCODE_LOAD, addr, NULL, NULL, 0);
}

ast_node_t* build_store(ast_node_t* addr, ast_node_t* value) {
    // Store: Has both children, no immediate value
    return make_node(OPCODE_STORE, addr, value, NULL, 0);
}


ast_node_t* build_not(ast_node_t* src) {
    // Unary NOT: Has a left child, no right child, no immediate value
    return make_node(OPCODE_NOT, src, NULL, NULL, 0);
}
ast_node_t* build_and(ast_node_t* lhs, ast_node_t* rhs){
    // Binary AND: Has both children, no immediate value
    return make_node(OPCODE_AND, lhs, rhs, NULL, 0);
}
ast_node_t* build_or(ast_node_t* lhs, ast_node_t* rhs){
    // Binary OR: Has both children, no immediate value
    return make_node(OPCODE_OR, lhs, rhs, NULL, 0);
}
ast_node_t* build_xor(ast_node_t* lhs, ast_node_t* rhs){
    // Binary XOR: Has both children, no immediate value
    return make_node(OPCODE_XOR, lhs, rhs, NULL, 0);
}


ast_node_t* build_asr(ast_node_t* lhs, ast_node_t* rhs){
    return make_node(OPCODE_ASR, lhs, rhs, NULL, 0);
}
ast_node_t* build_lsl(ast_node_t* lhs, ast_node_t* rhs){
    return make_node(OPCODE_LSL, lhs, rhs, NULL, 0);
}
ast_node_t* build_lsr(ast_node_t* lhs, ast_node_t* rhs){
    return make_node(OPCODE_LSR, lhs, rhs, NULL, 0);
}


ast_node_t* build_add(ast_node_t* lhs, ast_node_t* rhs) {
    // Binary ADD: Has both children, no immediate value
    return make_node(OPCODE_ADD, lhs, rhs, NULL, 0);
}
ast_node_t* build_mul(ast_node_t* lhs, ast_node_t* rhs){
    // Binary MUL: Has both children, no immediate value
    return make_node(OPCODE_MUL, lhs, rhs, NULL, 0);
}
ast_node_t* build_sub(ast_node_t* lhs, ast_node_t* rhs){
    // Binary SUB: Has both children, no immediate value
    return make_node(OPCODE_SUB, lhs, rhs, NULL, 0);
}
ast_node_t* build_div(ast_node_t* lhs, ast_node_t* rhs){
    // Binary DIV: Has both children, no immediate value
    return make_node(OPCODE_DIV, lhs, rhs, NULL, 0);
}


ast_node_t* build_lt(ast_node_t* lhs, ast_node_t* rhs){
    // Binary LT: Has both children, no immediate value
    return make_node(OPCODE_LT, lhs, rhs, NULL, 0);
}
ast_node_t* build_lte(ast_node_t* lhs, ast_node_t* rhs){
    // Binary LTE: Has both children, no immediate value
    return make_node(OPCODE_LTE, lhs, rhs, NULL, 0);
}
ast_node_t* build_gt(ast_node_t* lhs, ast_node_t* rhs){
    // Binary GT: Has both children, no immediate value
    return make_node(OPCODE_GT, lhs, rhs, NULL, 0);
}
ast_node_t* build_gte(ast_node_t* lhs, ast_node_t* rhs){
    // Binary GTE: Has both children, no immediate value
    return make_node(OPCODE_GTE, lhs, rhs, NULL, 0);
}
ast_node_t* build_eq(ast_node_t* lhs, ast_node_t* rhs){
    // Binary EQ: Has both children, no immediate value
    return make_node(OPCODE_EQ, lhs, rhs, NULL, 0);
}


ast_node_t* build_jump(ast_node_t* target){
    // Jump: Has a single child, no immediate value
    return make_node(OPCODE_JUMP, target, NULL, NULL, 0);
}
ast_node_t* build_branch(ast_node_t* cond, ast_node_t* true_target, ast_node_t* false_target){
    // Branch: Has a condition and two targets, no immediate value
    return make_node(OPCODE_BRANCH, cond, true_target, false_target, 0);
}
ast_node_t* build_halt(){
    return make_node(OPCODE_HALT, NULL, NULL, NULL, 0);
}


