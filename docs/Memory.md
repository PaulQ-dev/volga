# VOLGA DOCUMENTATION VER.0.0
## SPECIAL MEMORY ADDRESSES
1. (0x8FFF, w) - Halt trigger. Write: stop execution and return written byte as exit code. Read: return last read byte
2. (0x9000, rw) - Console out. Write: treat written byte as ASCII encoded character (0x00 - 0x7F) and write it to stdout. Read: return last printed character as ASCII sequence