#include "../include/main.h"
#include "../../disassembler/include/disassemble.h"
#include <stdio.h>
#include <stdint.h>
#include "../include/lift.h"
#include "../include/ir.h"

IRContext* ctx;

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

    FILE* in_file = fopen(infile_name, "rb");
    if(in_file == NULL) {
        printf("Failed to open file: %s\n", infile_name);
        return 1;
    }
    // Decoding loop for instructions.
    uint8_t header_byte;
    int read_cnt = 0;
    // Initialize IR context.
    ctx = malloc(sizeof(IRContext));
    create_ir_context(ctx);
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
        // Create lifter functions, which take a populated instruction and returns a human readable string.
        // A pair which has a function pointer
        if(instruction.is_binary == 1){
            output_binary[instruction.opcode].funcptr(instruction);
        }
        else{
            output_unary[instruction.opcode].funcptr(instruction);
        }
    }
    return 0;
}
