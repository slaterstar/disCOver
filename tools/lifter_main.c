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
    for(int i = 0; i < ctx->state_map->size; i++) {
        print_node(((StateMapEntry*)ctx->state_map->data)[i].node, 0);
    }

    // Begin on Lemerre's SSA,


    free_ir_context(ctx);
    free_dynamic_array(labels);
    return 0;
}

