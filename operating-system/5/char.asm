%ifndef CHAR
%define CHAR

    global putChar
    global absPutChar
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

absPutChar:
    push bp
    mov bp, sp
    mov ax, 0b800h
    mov gs, ax
    mov ah, byte [bp+0xa]
    mov bx, word [bp+0x6]
    push bp
    mov bp, bx
    mov byte [gs:bp], ah
    pop bp
    mov sp, bp
    pop bp
    jmp returnC

getChar:
    mov ah, 0
    int 16h
    jmp returnC

    %include "returnC.asm"

%endif
