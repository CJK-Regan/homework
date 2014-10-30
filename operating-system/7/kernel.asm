[bits 16]

    extern cmain
    global _start

_start:
    mov ax, cs
    mov ds, ax
    mov ss, ax
    mov ax, 0xffff
    mov sp, ax

    push word 0x0
    call cmain
    jmp $

    %include "char.asm"
    %include "clear.asm"
    %include "multiprocess.asm"
