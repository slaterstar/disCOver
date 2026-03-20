#include "../include/structs.h"
#include <stdint.h>
#include <stdlib.h>

void create_instruction(DecodedInstr* out, uint8_t header, uint32_t op_a, uint32_t op_b);
