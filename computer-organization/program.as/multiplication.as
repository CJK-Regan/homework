    lw 0 2 mcand
    lw 0 3 mplier
    lw 0 4 one
    lw 0 6 times
    lw 0 7 neg
loop nand 3 4 5
    beq 5 7 next
    add 1 2 1
next add 2 2 2
    add 4 4 4
    add 6 7 6
    beq 0 6 done
    beq 0 0 loop
done halt
mcand .fill 32766
mplier .fill 10383
one .fill 1
times .fill 32
neg .fill -1
