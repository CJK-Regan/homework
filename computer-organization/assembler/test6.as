    lw 0 1 ten
    lw 0 2 neg
loop add 1 3 3
    add 1 2 1
    beq 0 1 done
    beq 0 0 loop
done halt
ten .fill 10
neg .fill -1
