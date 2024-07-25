# VOLGA DOCUMENTATION VER.0.0
Main documentation [here](Main.md)
## INSTRUCTIONS
### NOTATIONS
+ `#` - Single byte
+ `##` - Two bytes in little-endian
+ `b` - Lower nibble (half-byte)
+ `a` - Address (Similar to `##`, but has different meaning)
+ `r` - Any 8-bit register
+ `rX` - Any 8-bit register (if instruction uses multiple), X goes from 0 to 9
+ `ra` - Any 16-bit register
+ `raX` - Any 16-bit register (if instruction uses multiple), X goes from 0 to 9
+ `0x` or `$` - Prefix for hexadecimal number
+ `0b` - Prefix for binary number
### IMPLEMENTED INSTRUCTIONS
+ `ht b` - Stop execution and return exit code `b`. In bytecode: `$0b`, where `b` goes from `$0` to `$F`.
+ `ld #,r` - Load `#` into `r`. In bytecode: `$40`. Operands: `#` - byte to be loaded, `r` - destination register (`$0`-`$F`).
+ `st r,a` - Store `r` at `a`. In bytecode: `$90`. Operands: `r` - source register (`$0`-`$F`), `a` - destination address.
+ `jp a` - Jump execution to `a` (Changes program counter to `a`). In bytecode: `$D0`. Operands: `a` - new execution address.
+ `bri r,#,a` - If value of `r` equals `#`, then jump to `a`. In bytecode: `$B0`. Operands: `r` - register to compare, `#` - value to compare, `a` - new execution address