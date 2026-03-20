#include "../include/structs.h"
#include <stdint.h>
#include <stdlib.h>

DecodedInstr* create_instruction(uint8_t header, uint32_t op_a, uint32_t op_b);
