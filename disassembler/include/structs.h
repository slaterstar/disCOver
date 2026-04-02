#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
    uint8_t size    : 1;
    uint8_t opcode  : 7;
    uint32_t op_a;

    // only valid if size == 1
    uint32_t op_b;
} OverInstr;

typedef struct {
    uint8_t opcode;
    uint32_t op_a;
    uint32_t op_b;
    bool is_binary;
} DecodedInstr;

typedef struct {
    uint8_t opcode;
    uint32_t op_a;
    uint32_t op_b;
    bool is_binary;
} MapInstr;

typedef struct{
    int opcode;
    char* format;
} OutputPair;

#endif
