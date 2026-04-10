#define HELP_MESSAGE "Usage: lifter <file>\n"
#include <stdint.h>
#include "ir.h"
#include "lift.h"
#include "../../disassembler/include/structs.h"

typedef struct {
    uint8_t op_code;
    void(*funcptr)(DecodedInstr);
} LifterOutput;

typedef struct {
    int label_index;
    size_t memory_addr;
} LabelPair;

int label_cmp(const void* a, const void* b){
    // Descending order
    const LabelPair* la = (const LabelPair*)a;
    const LabelPair* lb = (const LabelPair*)b;
    return lb->memory_addr - la->memory_addr;
}

int block_cmp(const void* a, const void* b){
    // Ascending order
    const BasicBlock* la = (const BasicBlock*)a;
    const BasicBlock* lb = (const BasicBlock*)b;
    return la->address - lb->address;
}