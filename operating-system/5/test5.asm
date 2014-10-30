[bits 16]

    extern test
    global _start

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call test
    retf

    %include "char.asm"
    %include "sysCalls.asm"
