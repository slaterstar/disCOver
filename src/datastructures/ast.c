#include "../../include/datastructures/ast.h"
#include <stdlib.h>
#define TABLE_SIZE 1024
// make sure its zero initialized
ast_node_t* ast_table[TABLE_SIZE] = {0};


uint32_t hash_node(IROpcode op, ast_node_t* lhs, ast_node_t* rhs, int imm){
    struct {
        uint32_t op;
        uintptr_t l;
        uintptr_t r;
        uint64_t val;
    } data;

    data.op = (uint32_t)op;
    data.l  = (uintptr_t)lhs;
    data.r  = (uintptr_t)rhs;
    data.val = imm;

    uint32_t hash_out;
    uint32_t seed = 0xADCDBADE; // Constant seed

    MurmurHash3_x86_32(&data, sizeof(data), seed, &hash_out);

    return hash_out;
}

// Constructor for ast_node
ast_node_t* make_binop(IROpcode op, ast_node_t* lhs, ast_node_t* rhs){
    // hash pointers of children
    uint32_t hash = hash_node(op, lhs, rhs, 0);
    int bucket = hash % TABLE_SIZE;

    // Lookup specific operation with specific children
    ast_node_t* node = ast_table[bucket];
    while(node){
        // check for exact match
        if (node->data.bin.left_child == lhs && node->data.bin.right_child == rhs && node->opcode == op) {
            return node;
        }
        // Traverse the bucket for collisions
        node = node->next;
    }
    // node is NULL here
    // no match found, create our ast node and link it to the bucket
    node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->opcode = op;
    node->hash = hash;
    node->data.bin.left_child = lhs;
    node->data.bin.right_child = rhs;
    // Insert at head of bucket
    node->next = ast_table[bucket];
    ast_table[bucket] = node;

    return node;
}