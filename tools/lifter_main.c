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
    if(ir_instr->opcode == OPCODE_LABEL) {
        fprintf(out_file, "label %d\n", ir_instr->label.label);
        return;
    }
    if(ir_instr->mem_addr != -1){
        fprintf(out_file, "0x%08X: ", ir_instr->mem_addr);
    }
    else{
        fprintf(out_file, "            ");
    }
    switch (ir_instr->opcode) {
        case OPCODE_ADD:
            fprintf(out_file, "add r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_SUB:
            fprintf(out_file, "sub r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_MUL:
            fprintf(out_file, "mul r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_DIV:
            fprintf(out_file, "div r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_NOT:
            fprintf(out_file, "not r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg);
            break;
        case OPCODE_AND:
            fprintf(out_file, "and r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_OR:
            fprintf(out_file, "or r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_ASR:
            fprintf(out_file, "asr r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_LSL:
            fprintf(out_file, "lsl r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
            break;
        case OPCODE_LSR:
            fprintf(out_file, "lsr r%d, r%d, r%d\n", ir_instr->alu.dest_reg, ir_instr->alu.src1_reg, ir_instr->alu.src2_reg);
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
            fprintf(out_file, "unknown_opcode\n");
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

    insert_labels_into_ir(ctx, labels);
    // Print IR instructions
    for(int i = 0; i < ctx->instructions->size; i++) {
        IRInstruction instr = ((IRInstruction*)ctx->instructions->data)[i];
        print_ir_instr(&instr, out_file);
    }


    free_ir_context(ctx);
    free_dynamic_array(labels);
    return 0;
}

void insert_labels_into_ir(IRContext* ctx, DynamicArray* labels) {
    // 1. Sort labels by address DESCENDING (highest address first)
    // This is the "Backtracking" trick: inserting at the end of the array
    // doesn't shift the indices of the instructions at the beginning.
    qsort(labels->data, labels->size, sizeof(LabelPair), label_cmp);

    for(int i = 0; i < labels->size; i++) {
        LabelPair* lp = &((LabelPair*)labels->data)[i];

        if (lp->type == MEM) {
            int raw_index = find_instr_index_by_addr(ctx, lp->value.memory_addr);

            if (raw_index != -1) {
                IRInstruction label_instr = {
                    .opcode = OPCODE_LABEL,
                    .label = { .label = lp->label_index },
                    .mem_addr = lp->value.memory_addr
                };

                // Because we are sorting DESCENDING, we don't need an 'offset' variable.
                // We just insert, and the lower-address indices remain stable.
                insert_ir_instruction(ctx, raw_index, label_instr);
            }
        }
    }
}

int find_instr_index_by_addr(IRContext* ctx, uint32_t addr) {
    int best_index = -1;
    uint32_t best_addr = 0;

    for (int i = 0; i < ctx->instructions->size; i++) {
        IRInstruction* current = (IRInstruction*)get(ctx->instructions, i);

        // Skip internal IR instructions that don't have a real physical address
        if (current->mem_addr == (uint32_t)-1) continue;

        // Exact match found
        if (current->mem_addr == addr) {
            return i;
        }

        // Track the closest instruction that started BEFORE the target address
        if (current->mem_addr < addr && (best_index == -1 || current->mem_addr > best_addr)) {
            best_index = i;
            best_addr = current->mem_addr;
        }
    }

    // This will return the index of the instruction "containing" the label
    return best_index;
}