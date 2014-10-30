[bits 16]

    extern counter
    global _start

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call counter
    jmp $

    %include "char.asm"
