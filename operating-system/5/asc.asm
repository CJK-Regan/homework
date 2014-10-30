[bits 16]

    extern asc
    global _start

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call asc
    retf

    %include "char.asm"
    %include "returnC.asm"
