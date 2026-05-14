General rule of thumb for this basic IR:
Arithmetic will use a mix of registers and immediates as operands. See [ARITHMETIC](#arithmetic) for more information.

Control Flow will use a mix of registers and Labels. Labels can be alpha-numeric.

# MEMORY
Memory operations can only take registers.
| Operations | Description | Example |
| ---------- | ----------- | ------- |
| LOAD | Returns the value stored in the memory address contained in the provided register. | t1 = LOAD(t0)
| STORE | Writes the second register into the first register's memory address | STORE(t1, t0)

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

# CONTROL FLOW
| Operations | Description | Example |
| ---------- | ----------- | ------- |
| LT | Returns 1 if the first operand is lesser than the second | t2 = LT(t1, t0)
| LTE | Returns 1 if the first operand is lesser than or equal to the second operand | t2 = LTE(t1, t0)
| EQ | Returns 1 if both operands have equivalent value else 0 | t2 = EQ(t1, t0)
| GT | Returns 1 if the first operand is greater than the second operand else 0| t2 = GT(t1, t0)
| GTE | Returns 1 if the first operand is greater than or equal to the second operand | t2 = GTE(t1, t0)
| JUMP | Continue execution starting from the specified label or register address. | JUMP(LABEL)
| BRANCH | If the first operand (register) is 1, jump to the 3rd operand's label else jump to the 2nd operand. | BRANCH(t0, TRUE_LABEL, FALSE_LABEL)
| HALT | Returns no value, halts execution of program. | HALT |

# MISC
| Operations | Description | Example |
| ---------- | ----------- | ------- |
| ASSIGN | Returns the immediate value. | t0 = ASSIGN(0x100)

