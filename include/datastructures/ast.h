#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stdbool.h>
#include "../lifter/enums.h"
#include "hash.h"
// Hash-Consed AST Node
// For our hash we use a bucket-based approach, hence why we have a `next` pointer
typedef struct ast_node {
    IROpcode opcode;
    uint64_t hash;
    union {
        uint64_t value;
        struct{
            struct ast_node* left_child;
            struct ast_node* right_child;
        } bin;
    } data;
    struct ast_node* next; // The next node in the bucket
} ast_node_t;

uint32_t hash_node(IROpcode opcode, ast_node_t* l, ast_node_t* r, int val);

#endif // AST_H
