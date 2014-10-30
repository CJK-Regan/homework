    lw 0 2 one
    lw 0 3 index
    lw 0 4 ten
loop add 1 2 1
    add 2 3 3
    sw 3 1 0
    beq 1 4 break
    beq 0 0 loop
break halt
one .fill 1
ten .fill 10
index .fill index
    .fill 0
    .fill 0
    .fill 0
    .fill 0
    .fill 0
    .fill 0
    .fill 0
    .fill 0
    .fill 0
    .fill 0
