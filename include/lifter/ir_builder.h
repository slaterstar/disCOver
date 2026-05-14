#ifndef IR_BUILDER_H
#define IR_BUILDER_H
#include "enums.h"
#include "ir.h"
#include "../datastructures/ast.h"
#include <stdint.h>



ast_node_t* build_imm(uint32_t value);
ast_node_t* build_reg(int reg_index);

ast_node_t* build_load(ast_node_t* addr);
ast_node_t* build_store(ast_node_t* addr, ast_node_t* value);

ast_node_t* build_not(ast_node_t* src);
ast_node_t* build_and(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_or(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_xor(ast_node_t* lhs, ast_node_t* rhs);

ast_node_t* build_asr(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_lsl(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_lsr(ast_node_t* lhs, ast_node_t* rhs);


ast_node_t* build_add(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_mul(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_sub(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_div(ast_node_t* lhs, ast_node_t* rhs);

ast_node_t* build_lt(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_lte(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_gt(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_gte(ast_node_t* lhs, ast_node_t* rhs);
ast_node_t* build_eq(ast_node_t* lhs, ast_node_t* rhs);

ast_node_t* build_jump(ast_node_t* target);
ast_node_t* build_branch(ast_node_t* cond, ast_node_t* true_target, ast_node_t* false_target);
ast_node_t* build_halt();


#endif // IR_BUILDER_H
