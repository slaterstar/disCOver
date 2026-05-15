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

typedef struct BasicBlock {
    size_t start_idx;    // Index in the 'instructions' array
    size_t end_idx;      // Index of the terminator instruction
    uint32_t start_addr; // The actual Overscore memory address of the first instruction

    DynamicArray* predecessors; // Array of BasicBlock*
    DynamicArray* successors;   // Array of BasicBlock*

    // Lemerre's Abstract Stores (Replacing the global ctx->state_map)
    DynamicArray* entry_store;  // Array of StateMapEntry
    DynamicArray* exit_store;   // Array of StateMapEntry

    bool sealed; // Used later to check if all predecessors are known
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
