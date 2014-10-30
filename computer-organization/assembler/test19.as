    lw 0 2 x
    lw 0 4 one
loop beq 2 3 break
    add 3 4 3
    add 1 2 1
    beq 0 0 loop
break halt
x .fill 7
one .fill 1
