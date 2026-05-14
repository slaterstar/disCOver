#ifndef IR_H
#define IR_H

#include "../datastructures/dynamicarray.h"
#include <stdint.h>
#include "enums.h"
#include "../disassembler/structs.h"



typedef struct {
    OperandType type;
    union {
        int reg;
        int imm;
        int mem;
    } value;
} Operand;

typedef struct {
    IROpcode opcode;
    union {
        struct {
            int dest_reg;
            int src_reg; // Register only
        } load;
        struct {
            int addr_reg;
            int data_reg;
        } store;
        struct {
            int dest_reg;
            int src1_reg;
            Operand src2;
        } alu;
        struct{
            int dest_reg;
            int src1_reg;
            Operand src2;
        } comp;
        struct {
            int dest_reg;
            int const_val;
        } assign;
        struct {
            Operand label; // intlabel or a register for address
        } jump;
        struct {
            int cond_reg;
            Operand true_val; // intlabel or a register for address
            Operand false_val; // intlabel or a register for address
        } branch;
        struct {
            int label;
        } label;
        struct {
            int dest_reg;
            int *src_regs;
            int num_srcs;
        } phi;
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
void add_instruction(IRContext* ctx, IRInstruction instr);
void print_ir(IRContext* ctx);
IRInstruction get_instruction(IRContext* ctx, int index);
void* insert_ir_instruction(IRContext* ctx, int index, IRInstruction instr);
void free_ir_context(IRContext* ctx);

int new_reg(IRContext* ctx);
int new_label(IRContext* ctx, uint32_t value, LabelType type, LabelPair* out_label);

#endif // IR_H
