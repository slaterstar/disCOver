#ifndef IR_H
#define IR_H

#include "../datastructures/dynamicarray.h"
#include <stdint.h>
#include "enums.h"
#include "../disassembler/structs.h"
#include "../datastructures/ast.h"



typedef struct {
    uint32_t address;  // The actual memory address (Key)
    ast_node_t* node;  // The AST node (Value)
} StateMapEntry;

typedef struct {
    // Data Flow
    DynamicArray* state_map;  // Tracks static addresses like [#100]
    // Dynamic array of StateMapEntrys

    // Side Effects
    DynamicArray* side_effects; // A list to push STORE or SYSCALL nodes into, flags anything that can't be statically resolved

    // Control Flow
    ast_node_t* terminator;   // Replaces 'root'. Holds the final BRANCH/JUMP/HALT
} IRContext;

typedef struct {
    size_t start; // Index of first instruction in basic block.
    size_t end; // Index of last instruction in basic block.
} BasicBlock;


typedef struct {
    uint8_t op_code;
    void(*funcptr)(DecodedInstr);
} LifterOutput;

typedef enum LabelType{
    MEM,
    REG,
} LabelType;

typedef struct {
    int label_index;
    LabelType type;
    union{
        size_t memory_addr;
        size_t reg_index;
    } value;
} LabelPair;

int label_cmp(const void* a, const void* b);

int block_cmp(const void* a, const void* b);

void create_ir_context(IRContext* ctx);



void free_ir_context(IRContext* ctx);

ast_node_t* get_current_state(IRContext* ctx, uint32_t memory_addr);
void set_current_state(IRContext* ctx, uint32_t memory_addr, ast_node_t* node);

#endif // IR_H
