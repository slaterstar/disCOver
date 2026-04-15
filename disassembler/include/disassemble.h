
#ifndef DISASSEMBLE_H
#define DISASSEMBLE_H

#include "../include/structs.h"
#include "../include/dynamicarray.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void create_instruction(DecodedInstr* out, uint8_t header, uint32_t op_a, uint32_t op_b);
// Sets the file pointer to the starting address and returns 0 on success, -1 on failure.
int seek_entry(FILE* in_file);
int disassemble(FILE* in_file, DynamicArray* instructions);
#endif // DISASSEMBLE_H
