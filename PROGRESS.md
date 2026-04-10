# Status
DISASSEMBLER - Barebones
IR - Unstable
LIFTER - IN PROGRESS

# Challenges

## Disassembler


## Lifter
Designing an IR for the lifter was a challenge to reason out. Overall the initial ideas I had was to form a complete set. Which is to say include all the fundamental operations, namely: arithmetic, memory access, and control flow.

Now for the other qualities, I had to decide whether I wanted it to be pure or flexible. A few assumptions:
- The looser the operands are, the harder it is to do dataflow analysis.
- Human-readability isn't the main goal. Reading IR line by line isn't much more useful than understanding the assembly if not worse... Our end goal is to make the processing and end goal clean / seamless.

### Datastructures
All forms of storage are within dynamic arrays. LLVM uses doubly linked lists and will be the next-try if issues arise, particularly when optimization passes will be implemented.
Lookup table is used for lifting, each overscore instruction variant has its own lift function which will generate its IR.


# In-progress
- Create IR for all instructions
- Implement labels
# TODO
- Disassembler needs to be able to be smart, differentiate data from code.
- Refactor Lifter (really needs it...)
    - Either use defines or functions to do each IR instruction

# Resources
https://www.cs.cmu.edu/afs/cs/Web/People/fp/courses/15411-f13/lectures/20-decompilation.pdf
