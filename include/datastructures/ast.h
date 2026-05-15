#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stdbool.h>
#include "../lifter/enums.h"
#include "hash.h"
// Hash-Consed AST Node
// For our hash we use a bucket-based approach, hence why we have a `next` pointer
// Making it a ternary is necessary for a branch operator
typedef struct ast_node {
    IROpcode opcode;
    uint32_t hash;

    // The Universal Fields
    struct ast_node* c1; // Used for: Left Child OR Condition
    struct ast_node* c2; // Used for: Right Child OR True Target
    struct ast_node* c3; // Used for: False Target
    uint64_t value;      // Used for: Immediates/Registers

    struct ast_node* next; // Hash table bucket chain
} ast_node_t;

ast_node_t* make_node(IROpcode op, ast_node_t* c1, ast_node_t* c2, ast_node_t* c3, int imm);
void print_node(ast_node_t* node, int depth);
#endif // AST_H
