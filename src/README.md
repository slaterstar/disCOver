The lifter is entirely optional and is probably unnecessary for Overscore, however for the sake of practice I will be making my own IR to lift into!

Linear:
Similar to assembly, `dest = src1 OP src2`

Virtual registers, `t0` `t1` ... (i know that Overscore uses purely label and memory addresses but maybe a lifter is important for this)

Instructions, OPCODE op1 op2

Unlimited memory and fixed size accesses (32 bit)

Overscore:
```c
mov [#100x] #AAx
mov [#104x] [#100x]
not [#104x]
and [#100x] [#104x]
end
```

IR:
```c
t0 = ASSIGN(0xAA)
STORE(0x100, t0)
t1 = LOAD(0x100)
STORE(0x104, t1)
t2 = LOAD(0x104)
t3 = NOT(t2)
STORE(0x104, t3)
t4 = LOAD(0x100)
t5 = LOAD(0x104)
t6 = AND(t4, t5)
STORE(0x100, t6)
HALT
```