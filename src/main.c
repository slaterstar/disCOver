#include "../include/main.h"
// To make logic easier, will use format strings for each operation.
OutputPair unary[] = { {0, "not [#%Xx]"}, {1, "sys [#%Xx]"} };
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
        printf(unary[instruction.opcode].format, instruction.op_a);
    }
    return 0;
}
