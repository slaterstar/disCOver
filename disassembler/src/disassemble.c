#include "../include/disassemble.h"



void create_instruction(DecodedInstr* out, uint8_t header, uint32_t op_a, uint32_t op_b){

    out->opcode = header & 0x7F;
    out->op_a = op_a;
    out->is_binary = header & (1 << 7);

    out->op_b = (out->is_binary) ? op_b : 0;
}
