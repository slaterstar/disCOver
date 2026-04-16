#ifndef IR_H
#define IR_H

#include "../datastructures/dynamicarray.h"
#include <stdint.h>
#include "../disassembler/structs.h"

enum IROpcode {
    OPCODE_ADD,
    OPCODE_SUB,
    OPCODE_MUL,
    OPCODE_DIV,
    OPCODE_NOT,
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_ASR,
    OPCODE_LSL,
    OPCODE_LSR,
    OPCODE_LOAD,
    OPCODE_STORE,
    OPCODE_ASSIGN,
    OPCODE_LABEL,
    OPCODE_JUMP,
    OPCODE_BRANCH,
    OPCODE_HALT,
};

typedef enum {
    OP_REGISTER,
    OP_IMMEDIATE,
    OP_MEMORY_ADDR
} OperandType;

typedef struct {
    OperandType type;
    union {
        int reg;
        int imm;
        int mem;
    } value;
} Operand;

typedef struct {
    enum IROpcode opcode;
    union {
        struct {
            int dest_reg;
            int src; // Register only
        } load;
        struct {
            Operand dest_addr;
            Operand src_reg;
        } store;
        struct {
            int dest_reg;
            int src1_reg;
            Operand src2_reg;
        } alu;
        struct {
            int dest_reg;
            int const_val;
        } assign;
        struct {
            Operand label;
        } jump;
        struct {
            int cond_reg;
            int true_label;
            int false_label;
        } branch;
        struct {
            int label;
        } label;
    };
    uint32_t mem_addr; // Address of the memory region being lifted; Only the start of a block will have a positive address.
} IRInstruction;

typedef struct {
    DynamicArray* instructions;
    // DynamicArray* basic_blocks;
    int reg_count;
    int label_count;
} IRContext;

typedef struct {
    size_t start; // Index of first instruction in basic block.
    size_t end; // Index of last instruction in basic block.
} BasicBlock;


typedef struct {
    uint8_t op_code;
    void(*funcptr)(DecodedInstr);
} LifterOutput;

typedef struct {
    int label_index;
    size_t memory_addr;
} LabelPair;

int label_cmp(const void* a, const void* b);

int block_cmp(const void* a, const void* b);

void create_ir_context(IRContext* ctx);
void add_instruction(IRContext* ctx, IRInstruction instr);
void print_ir(IRContext* ctx);
IRInstruction get_instruction(IRContext* ctx, int index);
void* insert_ir_instruction(IRContext* ctx, int index, IRInstruction instr);
void free_ir_context(IRContext* ctx);

int new_reg(IRContext* ctx);
int new_label(IRContext* ctx, uint32_t mem_addr, LabelPair* out_label);

#endif // IR_H
