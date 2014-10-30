    lw 0 1 des
    lw 0 2 one
    lw 0 3 start
loop lw 3 4 0
    beq 1 4 break
    add 3 2 3
    beq 0 0 loop
break sw 0 3 des
    halt
start .fill a
a .fill 1
b .fill 2
c .fill 3
d .fill 4
e .fill 5
des .fill 3
one .fill 1
