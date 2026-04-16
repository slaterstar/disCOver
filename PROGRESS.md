# Status
DISASSEMBLER - Barebones

IR - Unstable

LIFTER - IN PROGRESS

# Challenges

## Disassembler
After making a basic disassembler (linear scan), I now realize an issue with actual assembled binaries.
Desynchronization is a problem that makes the disassembler basically unusable.

As there is no conventions in Overscore (yet atleast) this means that I need to employ heuristics and some form of 'emulation'
to follow blocks of code. 

A couple strategies being contemplated:
- Follow jumps and branches
- Misalignment check (invalid opcodes)
- Backtracking

As the logic for a disassembler is linked to what instructions the lifter works on, this issue must be solved before lifting can be done.

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
  - ~~Follows entry point for parsing~~
- Refactor Lifter (really needs it...)
  - ~~Refactored to reuse disassembler~~
  - Either use defines or functions to do each IR instruction
- SSA
  - Which method? (Phi nodes, coloring algorithm, other? )

# Resources
https://www.cs.cmu.edu/afs/cs/Web/People/fp/courses/15411-f13/lectures/20-decompilation.pdf
binrec
https://compilers.cs.uni-saarland.de/papers/ssara.pdf
