#include "../include/main.h"
#include "../include/dynamicarray.h"
#include <stdio.h>

// To make logic easier, will use format strings for each operation.
const OutputPair unary[] = { {0, "not [#%Xx]"}, {1, "sys [#%Xx]"} };
const OutputPair binary[] = {
    {0, "mov [#%Xx] #%Xx"}, {1, "mov [#%Xx] [#%Xx]"}, {2, "mov [#%Xx] [[#%Xx]]"},
    {3, "mov [[#%Xx]] #%Xx"}, {4, "mov [[#%Xx]] [#%Xx]"}, {5, "mov [[#%Xx]] [[#%Xx]]"},
    {6, "and [#%Xx] #%Xx"}, {7, "and [#%Xx] [#%Xx]"},
    {8, "or [#%Xx] #%Xx"}, {9, "or [#%Xx] [#%Xx]"},
    {10, "add [#%Xx] #%Xx"}, {11, "add [#%Xx] [#%Xx]"},
    {12, "sub [#%Xx] #%Xx"}, {13, "sub [#%Xx] [#%Xx]"},
    {14, "mul [#%Xx] #%Xx"}, {15, "mul [#%Xx] [#%Xx]"},
    {16, "jz [#%Xx] #%Xx"}, {17, "jz [#%Xx] [#%Xx]"},
    {18, "jnz [#%Xx] #%Xx"}, {19, "jnz [#%Xx] [#%Xx]"},
};
// LSB format
// 0000010 00000000 00000000 00000000 00000000
int main(int argc, char* argv[]){
    char* infile_name = NULL;

    switch(argc){
        case 2:
        infile_name = argv[1];
        break;

        default:
        printf(HELP_MESSAGE);
        return 0;
    }

    FILE* in_file = fopen(infile_name, "rb");

    FILE* out_file = stdout;

    DynamicArray* instructions = malloc(sizeof(DynamicArray));
    init_dynamic_array(instructions, 1024, sizeof(DecodedInstr));

    if(disassemble(in_file, instructions) != 0) {
        return 1;
    }

    // Print the instructions
    for(int i = 0; i < instructions->size; i++) {
        DecodedInstr* instr = (DecodedInstr*)get(instructions, i);
        if(instr->opcode == 0xFF) {
            printf("end\n");
        }
        else if(instr->is_binary) {
            printf(binary[instr->opcode].format, instr->op_a, instr->op_b);
        } else {
            printf(unary[instr->opcode].format, instr->op_a);
        }
        printf("\n");
    }
    return 0;
}
