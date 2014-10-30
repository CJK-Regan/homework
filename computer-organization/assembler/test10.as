    lw 0 1 a
    jalr 1 2
    halt
    sw 0 2 a
    beq 0 0 -3
a .fill 3
