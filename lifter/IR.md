General rule of thumb for this basic IR:
Arithmetic will use a mix of registers and immediates as operands. See [ARITHMETIC](#arithmetic) for more information.

Memory access instructions will be the only ones to reference memory addresses (and may include registers)

# MEMORY
Memory operations can take Immediates or Registers in any operand.
| Operations | Description | Example |
| ---------- | ----------- | ------- |
| LOAD | Returns the value stored in the provided memory address, or a memory address contained in the provided register. | t0 = LOAD(0x100)
| STORE | Writes the second value (register) into the first operand (a memory address or register containing one) | STORE(0x104, t0)

# ARITHMETIC
Arithmetic operations can take Registers and Immediates. 
HOWEVER, the first operand MUST be a register, and the second operand (if applicable) can either be a register or immediate.


| Operations | Description | Example |
| ---------- | ----------- | ------- |
| ADD | Returns the addition of two values. | t2 = ADD(t1, t0)
| MUL | Returns the multiplication of two values. | t2 = MUL(t1, t0)
| SUB | Returns the subtraction of the second operand from the first. | t2 = SUB(t0, t1)
| AND | Returns the bitwise AND of two values. | t2 = AND(t1, t0)
| NOT | Returns the bitwise NOT of a value. | t1 = NOT(t0)
| XOR | Returns the eXclusive OR of two values. | t2 = XOR(t1, t0)
| ASR | Returns the Arithmetic Shift Right of the first operand by the second operand in number of bits. | t2 = ASR(t1, 3)
| LSL | Returns the Logical Shift Left of the the first operand by the second operand in number of bits. | t2 = LSL(t1, 3)
| LSR | Returns the Logical Shift Right of the first operand by the second operand in number of bits. | t2 = LSR(t1, 3)

# MISC
| Operations | Description | Example |
| ---------- | ----------- | ------- |
| ASSIGN | Returns the immediate value. | t0 = ASSIGN(0x100)

