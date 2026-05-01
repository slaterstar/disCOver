#ifndef LIFTER_MAIN_H
#define LIFTER_MAIN_H

#define HELP_MESSAGE "Usage: lifter <file>\n"
#include <stdint.h>
#include <stdio.h>
#include "ir.h"
#include "lift.h"
#include "../disassembler/structs.h"

void print_ir_instr(IRInstruction *ir_instr, FILE* out_file);

void insert_labels_into_ir(IRContext* ctx, DynamicArray* labels);
int find_instr_index_by_addr(IRContext* ctx, uint32_t addr);
#endif