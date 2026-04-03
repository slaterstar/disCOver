#include "../include/dynamicarray.h"
#include <stdint.h>

enum IROpcode {
    OPCODE_ADD,
    OPCODE_SUB,
    OPCODE_MUL,
    OPCODE_DIV,
    OPCODE_LOAD,
    OPCODE_STORE,
    OPCODE_ASSIGN,
    OPCODE_HALT,
};

typedef struct {
    enum IROpcode opcode;
    union {
        struct {
            int dest_reg;
            int src;
        } load;
        struct {
            int dest_addr;
            int src_reg;
        } store;
        struct {
            int dest_reg;
            int src1_reg;
            int src2_reg;
        } alu;
        struct {
            int dest_reg;
            int const_val;
        } assign;
    };
} IRInstruction;

typedef struct {
    DynamicArray* instructions;
    int reg_count;
} IRContext;

void create_ir_context(IRContext* ctx);
void add_instruction(IRContext* ctx, IRInstruction instr);
void print_ir(IRContext* ctx);
IRInstruction get_instruction(IRContext* ctx, int index);
void free_ir_context(IRContext* ctx);

int new_reg(IRContext* ctx);