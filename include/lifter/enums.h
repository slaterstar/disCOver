#ifndef ENUMS_H
#define ENUMS_H

typedef enum  {
    OPCODE_ADD,
    OPCODE_SUB,
    OPCODE_MUL,
    OPCODE_DIV,
    OPCODE_LT,
    OPCODE_LTE,
    OPCODE_GT,
    OPCODE_GTE,
    OPCODE_EQ,
    OPCODE_NOT,
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_XOR,
    OPCODE_ASR,
    OPCODE_LSL,
    OPCODE_LSR,
    OPCODE_LOAD,
    OPCODE_STORE,
    OPCODE_ASSIGN,
    OPCODE_LABEL,
    OPCODE_JUMP,
    OPCODE_BRANCH,
    OPCODE_HALT,
    OPCODE_PHI,
    // AST Leaf Opcodes
    OPCODE_IMMEDIATE,
    OPCODE_REGISTER,
    OPCODE_MEMORY_ADDRESS,
} IROpcode;


typedef struct {
    IROpcode opcode;
    const char *name;
} OpcodePrint;

const static OpcodePrint opcode_print[] = {
    {OPCODE_ADD, "ADD"},
    {OPCODE_SUB, "SUB"},
    {OPCODE_MUL, "MUL"},
    {OPCODE_DIV, "DIV"},
    {OPCODE_LT, "LT"},
    {OPCODE_LTE, "LTE"},
    {OPCODE_GT, "GT"},
    {OPCODE_GTE, "GTE"},
    {OPCODE_EQ, "EQ"},
    {OPCODE_NOT, "NOT"},
    {OPCODE_AND, "AND"},
    {OPCODE_OR, "OR"},
    {OPCODE_XOR, "XOR"},
    {OPCODE_ASR, "ASR"},
    {OPCODE_LSL, "LSL"},
    {OPCODE_LSR, "LSR"},
    {OPCODE_LOAD, "LOAD"},
    {OPCODE_STORE, "STORE"},
    {OPCODE_ASSIGN, "ASSIGN"},
    {OPCODE_LABEL, "LABEL"},
    {OPCODE_JUMP, "JUMP"},
    {OPCODE_BRANCH, "BRANCH"},
    {OPCODE_HALT, "HALT"},
    {OPCODE_PHI, "PHI"},
    {OPCODE_IMMEDIATE, "IMMEDIATE"},
    {OPCODE_REGISTER, "REGISTER"},
    {OPCODE_MEMORY_ADDRESS, "MEMORY_ADDRESS"},
};

#endif // ENUMS_H
