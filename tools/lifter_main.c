#include "../include/lifter/lifter_main.h"
#include "../include/disassembler/disassemble.h"

IRContext* ctx;
DynamicArray* labels;

const LifterOutput output_unary[] = {
    {0, &lift_not}, {1, &lift_syscall}
};

const LifterOutput output_binary[] = {
    {0, &lift_mov10}, {1, &lift_mov11}, {2, &lift_mov12},
    {3, &lift_mov20}, {4, &lift_mov21}, {5, &lift_mov22},
    {6, &lift_and10}, {7, &lift_and11},
    {8, &lift_or10}, {9, &lift_or11},
    {10, &lift_add10}, {11, &lift_add11},
    {12, &lift_sub10}, {13, &lift_sub11},
    {14, &lift_mul10}, {15, &lift_mul11},
    {16, &lift_jumpz10}, {17, &lift_jumpz11},
    {18, &lift_jumpnz10}, {19, &lift_jumpnz11},
};

void print_ir_instr(IRInstruction *ir_instr, FILE *out_file){
    if(ir_instr->mem_addr != -1){
        fprintf(out_file, "0x%08X: ", ir_instr->mem_addr);
    }
    else{
        fprintf(out_file, "            ");
    }
    switch (ir_instr->opcode) {
        case OPCODE_ADD:
            fprintf(out_file, "add r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_SUB:
            fprintf(out_file, "sub r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_MUL:
            fprintf(out_file, "mul r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_DIV:
            fprintf(out_file, "div r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_NOT:
            fprintf(out_file, "not r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg);
            break;
        case OPCODE_AND:
            fprintf(out_file, "and r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_OR:
            fprintf(out_file, "or r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_ASR:
            fprintf(out_file, "asr r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_LSL:
            fprintf(out_file, "lsl r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_LSR:
            fprintf(out_file, "lsr r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg.value.reg);
            break;
        case OPCODE_LOAD:
            fprintf(out_file, "load r%d, [r%d]\n", ir_instr->load.dest_reg, ir_instr->load.src);
            break;
        case OPCODE_STORE:
            fprintf(out_file, "store [r%d], r%d\n", ir_instr->store.dest_addr.value.reg, ir_instr->store.src_reg.value.reg);
            break;
        case OPCODE_ASSIGN:
            fprintf(out_file, "assign r%d, %d\n", ir_instr->assign.dest_reg, ir_instr->assign.const_val);
            break;
        case OPCODE_LABEL:
            fprintf(out_file, "label l%d\n", ir_instr->label.label);
            break;
        case OPCODE_JUMP:
            fprintf(out_file, "jump l%d\n", ir_instr->jump.label);
            break;
        case OPCODE_BRANCH:
            fprintf(out_file, "branch r%d, l%d, l%d\n", ir_instr->branch.cond_reg, ir_instr->branch.true_label, ir_instr->branch.false_label);
            break;
        case OPCODE_HALT:
            fprintf(out_file, "halt\n");
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]){
    char* infile_name = NULL;

    switch(argc){
        case 2:
            infile_name = argv[1];
            break;
        default:
            printf(HELP_MESSAGE);
            return 0;
    }

    FILE* out_file = stdout;

    FILE* in_file = fopen(infile_name, "rb");
    if(in_file == NULL) {
        printf("Failed to open file: %s\n", infile_name);
        return 1;
    }

    ctx = malloc(sizeof(IRContext));
    create_ir_context(ctx);

    // Initialize labels array to allow for second pass
    labels = malloc(sizeof(DynamicArray));
    init_dynamic_array(labels, 40, sizeof(LabelPair));

    DynamicArray* instructions = malloc(sizeof(DynamicArray));
    init_dynamic_array(instructions, 40, sizeof(DecodedInstr));

    disassemble(in_file, instructions);

    // Lift all instructions
    for(int i = 0; i < instructions->size; i++) {
        DecodedInstr instr = ((DecodedInstr*)instructions->data)[i];
        if(instr.opcode == END) {
            lift_end(instr);
        }
        else if(instr.is_binary == 1) {
            output_binary[instr.opcode].funcptr(instr);
        }
        else {
            output_unary[instr.opcode].funcptr(instr);
        }
    }
    // Print IR instructions
    for(int i = 0; i < ctx->instructions->size; i++) {
        IRInstruction instr = ((IRInstruction*)ctx->instructions->data)[i];
        print_ir_instr(&instr, out_file);
    }

    // Second pass, populate labels and basic blocks.
    //
    // Sort labels by address in descending order.
    // qsort(labels->data, labels->size, sizeof(LabelPair), label_cmp);

    // // Insert labels
    // for(int i = 0; i < labels->size; i++) {
    //     // Parse label and insert into IR
    //     LabelPair label = ((LabelPair*)labels->data)[i];
    //     IRInstruction instr = { .opcode = OPCODE_LABEL, .label = {.label =label.label_index } };
    //     // Find the basic block that this label belongs to and insert the label before it.
    //     // Need fix to find the correct index, doesn't actually find the correct element.
    //     int index = (int) ((char*)bsearch(ctx->basic_blocks->data, ctx->basic_blocks->data, ctx->basic_blocks->size, sizeof(IRInstruction), block_cmp) - (char*)ctx->basic_blocks->data);
    //     insert_ir_instruction(ctx, index, instr);
    // }

    free_ir_context(ctx);
    return 0;
}
