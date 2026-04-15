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
    unsigned int starting_address = -1;
    unsigned int file_size = -1;
    fseek(in_file, 0, SEEK_END);
    file_size = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);

    DynamicArray* instructions = malloc(sizeof(DynamicArray));
    init_dynamic_array(instructions, sizeof(DecodedInstr), 1024);

    // Decoding loop for instructions.
    uint8_t header_byte;
    fread(&starting_address, 4, 1, in_file);
    if(starting_address > file_size) {
        printf("Starting address out of bounds.\n");
        return 1;
    }
    else{
        fseek(in_file, starting_address, SEEK_SET);
    }
    int read_cnt = 1;
    while(fread(&header_byte, 1, 1, in_file)){
        if(read_cnt == 0 && header_byte == 0xFF){
            // Stop execution
            printf("Silent exit. 0xFF");
            break;
        }
        uint8_t opcode = header_byte & 0x7F;
        uint8_t size = header_byte >> 7;
        // printf("Header byte: 0x%02X, Opcode: 0x%02X, Size: %u\n", header_byte, opcode, size);
        // word = 4 bytes
        // bytes = variable
        // end = 1 byte
        // instruction = variable
        // Parse each instruction, getting a Decoded result.
        DecodedInstr instruction;
        if (header_byte == 0xFF) {
            // End marker, not necessarily instruction but is important for program.
            instruction = (DecodedInstr){ .opcode = 0xFF, .op_a = 0, .op_b = 0, .is_binary = false };
        }
        else if(size == 0 && opcode < 2){
            // printf("Unary");
            uint32_t op_a;
            read_cnt = fread(&op_a, sizeof(uint32_t), 1, in_file);
            if(read_cnt != 1){
                break;
            }
            create_instruction(&instruction, header_byte, op_a, 0);
        }
        else if(size == 1 && opcode < 20){
            // printf("Binary");
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
        else{
            // continue to read the next byte.
            continue;
        }
        push_back(instructions, &instruction);
    }


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
