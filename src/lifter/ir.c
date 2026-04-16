#include "../../include/lifter/ir.h"

void create_ir_context(IRContext* ctx) {
    ctx->instructions = malloc(sizeof(DynamicArray));
    init_dynamic_array(ctx->instructions, 80, sizeof(IRInstruction));
    ctx->reg_count = -1;
    ctx->label_count = -1;
    // init_dynamic_array(ctx->basic_blocks, 40, sizeof(BasicBlock));
}

void add_instruction(IRContext* ctx, IRInstruction instr) {
    push_back(ctx->instructions, &instr);
}

IRInstruction get_instruction(IRContext* ctx, int index) {
    return *(IRInstruction*)get(ctx->instructions, index);
}

void free_ir_context(IRContext* ctx) {
    free_dynamic_array(ctx->instructions);
    // free_dynamic_array(ctx->basic_blocks);
}

void* insert_ir_instruction(IRContext* ctx, int index, IRInstruction instr) {
    return insert(ctx->instructions, index, &instr);
}

int new_reg(IRContext* ctx){
    ctx->reg_count++;
    return ctx->reg_count;
}

int new_label(IRContext* ctx, uint32_t value, LabelType type, LabelPair* out_label) {
    ctx->label_count++;
    out_label->label_index = ctx->label_count;
    out_label->type = type;
    if(type == REG) {
        out_label->value.reg_index = value;
    } else {
        out_label->value.memory_addr = value;
    }
    return ctx->label_count;
}

// int label_cmp(const void* a, const void* b){
//     // Descending order
//     const LabelPair* la = (const LabelPair*)a;
//     const LabelPair* lb = (const LabelPair*)b;
//     return lb->memory_addr - la->memory_addr;
// }

int block_cmp(const void* a, const void* b){
    // Ascending order
    const IRInstruction* la = (const IRInstruction*)a;
    const IRInstruction* lb = (const IRInstruction*)b;
    return la->label.label - lb->label.label;
}
