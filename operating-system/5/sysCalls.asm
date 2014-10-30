%ifndef SYSCALLS
%define SYSCALLS

    global ouch
    global upperCase
    global lowerCase
    global parseString
    global dumpNumber
    global absPutString

ouch:
    mov ah, 0
    int 21h
    jmp returnC

upperCase:
    push bp
    mov bp, sp
    mov ah, 1
    mov dx, word [bp+0xa]
    mov es, word [bp+0x6]
    int 21h
    mov sp, bp
    pop bp
    jmp returnC

lowerCase:
    push bp
    mov bp, sp
    mov ah, 2
    mov dx, word [bp+0xa]
    mov es, word [bp+0x6]
    int 21h
    mov sp, bp
    pop bp
    jmp returnC

parseString:
    push bp
    mov bp, sp
    mov ah, 3
    mov dx, word [bp+0xa]
    mov es, word [bp+0x6]
    int 21h
    mov ax, bx
    mov sp, bp
    pop bp
    jmp returnC

dumpNumber:
    push bp
    mov bp, sp
    mov ah, 4
    mov dx, word [bp+0xe]
    mov es, word [bp+0xa]
    mov bx, word [bp+0x6]
    int 21h
    mov sp, bp
    pop bp
    jmp returnC

absPutString:
    push bp
    mov bp, sp
    mov ah, 5
    mov ch, byte [bp+0x6]
    mov cl, byte [bp+0xa]
    mov es, word [bp+0xe]
    mov dx, word [bp+0x12]
    int 21h
    mov sp, bp
    pop bp
    jmp returnC

    %include "returnC.asm"

%endif
