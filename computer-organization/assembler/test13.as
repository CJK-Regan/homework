    lw 0 1 a
    lw 0 2 b
    lw 0 3 one
    nand 2 2 2
    add 2 3 2
    add 1 2 1
    lw 0 2 tmp
    nand 1 2 1
    nand 1 1 1
    beq 0 1 ga
    lw 0 1
ga lw 0 1 a
    halt
a .fill 7
b .fill 2
one .fill 1
tmp .fill 0x8fff
