[bits 16]

    extern test
    global _start

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call test
    jmp $

    %include "sysCalls.asm"
    %include "char.asm"
