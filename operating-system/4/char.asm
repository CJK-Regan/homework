%ifndef CHAR
%define CHAR

    global putChar
    global getChar

putChar:
    push bp
    mov bp, sp
    mov ah, 0eh
    mov al, byte [bp+0x6]
    mov bx, 0
    mov sp, bp
    int 10h
    pop bp
    jmp returnC

getChar:
    mov ah, 0
    int 16h
    jmp returnC

    %include "returnC.asm"

%endif
