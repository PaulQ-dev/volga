# VOLGA DOCUMENTATION VER.0.0
## ABOUT
Volga is an 8-bit virtual processor architecture. Project's goal is to create working 8-bit vitrual processor and assembles/disassembler for it
## MEMORY
Volga uses 16-bit adresses, allowing it to use 65536 bytes of memory. Also 16 8-bit and 4 16-bit registers are availible
### MEMORY LAYOUT
1. Zero Page (0x0000 - 0x00FF) (rw)
2. Main RAM (0x0100 - 0x80FF) (rw)
3. Stack (0x8100 - 0x80FF) (rw)
5. Halt trigger ([0x8FFF](Memory.md#special-memory-addresses)) (w)
4. Console out port ([0x9000](Memory.md#special-memory-addresses)) (rw)
6. Program ROM (0xA000 - 0xFFFF) (r)
### PROCESSOR FLAGS
`CZN-----H`
+ `C` - Carry
+ `Z` - Zero
+ `N` - Negative
+ `H` - [Halting](Memory.md#special-memory-addresses)
## INSTRUCTIONS
Volga instructions are 8-bit long and can be followed by operands. 
[Instructions manual](Instructions.md)