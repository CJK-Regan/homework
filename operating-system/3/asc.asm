[bits 16]

    extern asc

[section .text]
    global _start
    global getChar
    global putChar

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call asc
    retf

getChar:
    mov ah, 0
    int 16h
    jmp returnC

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

returnC:
    pop bx
    pop cx
    push bx
    ret
