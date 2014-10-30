[bits 16]

    extern bar
    global _start

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call bar
    jmp $

    %include "char.asm"
