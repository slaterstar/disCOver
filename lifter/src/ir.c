#include "../include/ir.h"

void create_ir_context(IRContext* ctx) {
    init_dynamic_array(ctx->instructions, 40, sizeof(IRInstruction));
    ctx->reg_count = -1;
}

void add_instruction(IRContext* ctx, IRInstruction instr) {
    push_back(ctx->instructions, &instr);
}

IRInstruction get_instruction(IRContext* ctx, int index) {
    return *(IRInstruction*)get(ctx->instructions, index);
}

void free_ir_context(IRContext* ctx) {
    free_dynamic_array(ctx->instructions);
}

int new_reg(IRContext* ctx){
    ctx->reg_count++;
    return ctx->reg_count;
}

int new_label(IRContext* ctx){
    ctx->label_count++;
    return ctx->label_count;
}