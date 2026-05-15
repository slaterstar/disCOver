#include "../../include/datastructures/ast.h"
#include <stdlib.h>
#include <stdio.h>
#define TABLE_SIZE 1024
// make sure its zero initialized
ast_node_t* ast_table[TABLE_SIZE] = {0};

uint32_t hash_node(IROpcode op, ast_node_t* c1, ast_node_t* c2, ast_node_t* c3, int imm){
    struct {
        uint32_t op;
        uintptr_t c1;
        uintptr_t c2;
        uintptr_t c3;
        uint64_t val;
    } data;

    data.op = (uint32_t)op;
    data.c1 = (uintptr_t)c1;
    data.c2 = (uintptr_t)c2;
    data.c3 = (uintptr_t)c3;
    data.val = imm;

    uint32_t hash_out;
    uint32_t seed = 0xADCDBADE; // Constant seed

    MurmurHash3_x86_32(&data, sizeof(data), seed, &hash_out);

    return hash_out;
}

uint32_t hash_phi_node(IROpcode op, uint32_t block_start_address, uint32_t memory_address){
    struct {
        uint32_t op;
        uint32_t block_start_address;
        uint32_t memory_address;
    } data;

    data.op = (uint32_t)op;
    data.block_start_address = block_start_address;
    data.memory_address = memory_address;

    uint32_t hash_out;
    uint32_t seed = 0xADCDBADE; // Constant seed

    MurmurHash3_x86_32(&data, sizeof(data), seed, &hash_out);

    return hash_out;
}

// Constructor for ast_phi_node
ast_node_t* make_phi_node(IROpcode op, DynamicArray* phi_operands, uint32_t block_start_address, uint32_t memory_address){
    uint32_t hash = hash_phi_node(op, block_start_address, memory_address);
    int bucket = hash % TABLE_SIZE;


    ast_node_t* node = ast_table[bucket];
    while(node){
        // check for exact match
        if (node->phi_operands == phi_operands && node->phi_block_addr == block_start_address && node->phi_mem_addr == memory_address && node->opcode == op) {
            return node;
        }
        // Traverse the bucket for collisions
        node = node->next;
    }

    node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->opcode = op;
    node->hash = hash;
    node->c1 = NULL;
    node->c2 = NULL;
    node->c3 = NULL;
    node->value = 0;
    node->phi_operands = phi_operands;
    node->phi_block_addr = block_start_address;
    node->phi_mem_addr = memory_address;
    node->next = NULL;

    return node;
}

// Constructor for ast_node
ast_node_t* make_node(IROpcode op, ast_node_t* c1, ast_node_t* c2, ast_node_t* c3, int imm){
    // hash pointers of children
    uint32_t hash = hash_node(op, c1, c2, c3, imm);
    int bucket = hash % TABLE_SIZE;

    // Lookup specific operation with specific children
    ast_node_t* node = ast_table[bucket];
    while(node){
        // check for exact match
        if (node->c1 == c1 && node->c2 == c2 && node->c3 == c3 && node->opcode == op && node->value == imm) {
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
    node->c1 = c1;
    node->c2 = c2;
    node->c3 = c3;
    node->value = imm;
    // Insert at head of bucket
    node->next = ast_table[bucket];
    ast_table[bucket] = node;

    return node;
}

void print_node(ast_node_t* node, int depth){
    if (node == NULL) return;
    for(int i = 0; i < depth; i++) printf("  ");
    printf("%s", opcode_print[node->opcode].name);
    if(node->opcode == OPCODE_IMMEDIATE || node->opcode == OPCODE_REGISTER || node->opcode == OPCODE_MEMORY_ADDRESS) {
        printf(", %llu", node->value);
    }
    printf("\n");
    if(node->c1) {

        print_node(node->c1, depth + 1);
    }
    if(node->c2) {

        print_node(node->c2, depth + 1);
    }
    if(node->c3) {

        print_node(node->c3, depth + 1);
    }
}