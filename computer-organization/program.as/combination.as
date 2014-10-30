    lw 0 1 n
    lw 0 2 r
    lw 0 5 funAdr
    jalr 5 6
    halt
func beq 0 2 return
    beq 1 2 return
    sw 7 6 stack
    lw 0 5 pos1
    add 5 7 7
    lw 0 5 neg1
    add 1 5 1
    lw 0 5 funAdr
    jalr 5 6
    lw 0 5 pos1
    sw 7 3 stack
    add 5 7 7
    lw 0 5 neg1
    add 2 5 2
    lw 0 5 funAdr
    jalr 5 6
    lw 0 5 neg1
    add 5 7 7
    lw 7 4 stack
    add 5 7 7
    lw 7 6 stack
    add 3 4 3
    lw 0 5 pos1
    add 1 5 1
    add 2 5 2
    jalr 6 5
return lw 0 3 pos1
    jalr 6 5
n .fill 7
r .fill 3
pos1 .fill 1
neg1 .fill -1
funAdr .fill func
stack .fill 0
