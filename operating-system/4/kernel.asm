[bits 16]

    extern cmain
    global _start

_start:
    mov ax, cs
    mov ds, ax

    call setTimer
    call setCustomInt
    push word 0x0
    call cmain
    jmp $

    %include "char.asm"
    %include "load.asm"
    %include "clear.asm"
    %include "datetime.asm"
    %include "customInt.asm"
