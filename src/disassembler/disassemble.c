#include "../../include/disassembler/disassemble.h"

void create_instruction(DecodedInstr* out, uint8_t header, uint32_t op_a, uint32_t op_b){

    out->opcode = header & 0x7F;
    out->op_a = op_a;
    out->is_binary = header & (1 << 7);

    out->op_b = (out->is_binary) ? op_b : 0;
}
int seek_entry(FILE* in_file){
    unsigned int starting_address = -1;
    unsigned int file_size = -1;
    fseek(in_file, 0, SEEK_END);
    file_size = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);
    fread(&starting_address, 4, 1, in_file);
    if(starting_address > file_size) {
        printf("Starting address out of bounds.\n");
        return 1;
    }
    else{
        fseek(in_file, starting_address, SEEK_SET);
    }
    return 0;
}
// Disassembles the instructions in the file and stores them in the instructions array.
// Returns 0 on success, 1 on failure.
int disassemble(FILE* in_file, DynamicArray* instructions) {
    if(seek_entry(in_file) != 0) {
        return 1;
    }

    // Decoding loop for instructions.
    uint8_t header_byte;

    int read_cnt = 1;
    while(fread(&header_byte, 1, 1, in_file)){
        if(read_cnt == 0 && header_byte == END){
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
        if (header_byte == END) {
            // End marker, not necessarily instruction but is important for program.
            instruction = (DecodedInstr){ .opcode = END, .op_a = 0, .op_b = 0, .is_binary = false };
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
    return 0;
}