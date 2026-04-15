#include "../datastructures/dynamicarray.h"
#include <stdint.h>

enum IROpcode {
    OPCODE_ADD,
    OPCODE_SUB,
    OPCODE_MUL,
    OPCODE_DIV,
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
            Operand true_label;
            Operand false_label;
        } branch;
        struct {
            int label;
        } label;
    };
} IRInstruction;

typedef struct {
    DynamicArray* instructions;
    DynamicArray* basic_blocks;
    int reg_count;
    int label_count;
} IRContext;

typedef struct {
    size_t start; // Index of first instruction in basic block.
    size_t end; // Index of last instruction in basic block.
    size_t address; // Address of original instruction.
} BasicBlock;

void create_ir_context(IRContext* ctx);
void add_instruction(IRContext* ctx, IRInstruction instr);
void print_ir(IRContext* ctx);
IRInstruction get_instruction(IRContext* ctx, int index);
void* insert_ir_instruction(IRContext* ctx, int index, IRInstruction instr);
void free_ir_context(IRContext* ctx);

int new_reg(IRContext* ctx);
int new_label(IRContext* ctx);