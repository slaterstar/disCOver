#include "../include/main.h"
// To make logic easier, will use format strings for each operation.
OutputPair unary[] = { {0, "not [#%Xx]"}, {1, "sys [#%Xx]"} };
OutputPair binary[] = {
    {0, "mov [#%Xx] #%Xx"}, {1, "mov [#%Xx] #%Xx"}, {2, "mov [#%Xx] [[#%Xx]]"},
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


    uint8_t header_byte;
    int read_cnt = 0;
    while(fread(&header_byte, 1, 1, in_file)){



        // Parse each instruction, getting a Decoded result.
        OverInstr* header = (OverInstr*) &header_byte;
        DecodedInstr instruction;
        if(header->size == 0){
            // printf("Unary");
            uint32_t op_a;
            read_cnt = fread(&op_a, sizeof(uint32_t), 1, in_file);
            if(read_cnt != 1){
                break;
            }

            create_instruction(&instruction, header_byte, op_a, 0);
        }
        else{
            printf("Binary");
            uint32_t op_a;
            uint32_t op_b;

            read_cnt = fread(&op_a, sizeof(uint32_t), 1, in_file);
            if(read_cnt != 1){
                break;
            }
            read_cnt = fread(&op_b, sizeof(uint32_t), 1, in_file);
            if(read_cnt != 1){
                break;
            }

            create_instruction(&instruction, header_byte, op_a, op_b);
        }

        // Create a mapped output of instruction to human readable.
        if(instruction.is_binary == 1){
            printf(binary[instruction.opcode].format, instruction.op_a, instruction.op_b);
        }
        else{
            printf(unary[instruction.opcode].format, instruction.op_a);
        }

    }
    return 0;
}
