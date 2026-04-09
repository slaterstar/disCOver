#define HELP_MESSAGE "Usage: lifter <file>\n"
#include <stdint.h>
#include "../../disassembler/include/structs.h"

typedef struct {
    uint8_t op_code;
    void(*funcptr)(DecodedInstr);
} LifterOutput;