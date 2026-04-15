#include "../../include/lifter/ir.h"

void create_ir_context(IRContext* ctx) {
    init_dynamic_array(ctx->instructions, 40, sizeof(IRInstruction));
    ctx->reg_count = -1;
    init_dynamic_array(ctx->basic_blocks, 40, sizeof(BasicBlock));
}

void add_instruction(IRContext* ctx, IRInstruction instr) {
    push_back(ctx->instructions, &instr);
}

IRInstruction get_instruction(IRContext* ctx, int index) {
    return *(IRInstruction*)get(ctx->instructions, index);
}

void free_ir_context(IRContext* ctx) {
    free_dynamic_array(ctx->instructions);
    free_dynamic_array(ctx->basic_blocks);
}

void* insert_ir_instruction(IRContext* ctx, int index, IRInstruction instr) {
    return insert(ctx->instructions, index, &instr);
}

int new_reg(IRContext* ctx){
    ctx->reg_count++;
    return ctx->reg_count;
}

int new_label(IRContext* ctx){
    ctx->label_count++;
    return ctx->label_count;
}