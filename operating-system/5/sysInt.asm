[bits 16]
    
    extern intHandler1and2
    extern intHandler3
    extern intHandler4
    extern intHandler5
    global setSysInt

setSysInt:
    mov ax, 0
    mov es, ax
    mov word [es:84h], sysInt
    mov ax, cs
    mov word [es:86h], ax
    ret

sysInt:
    cmp ah, 0
    jz int0
    cmp ah, 1
    jz int1
    cmp ah, 2
    jz int2
    cmp ah, 3
    jz int3
    cmp ah, 4
    jz int4
    cmp ah, 5
    jz int5
    jmp end
int0:
    mov ax, 0b800h
    mov gs, ax
    mov byte [gs:7cch], 'O'
    mov byte [gs:7ceh], 'U'
    mov byte [gs:7d0h], 'C'
    mov byte [gs:7d2h], 'H'
    jmp end
int1:
int2:
    push word 0x0
    mov al, ah
    mov ah, 0
    push ax
    push word 0x0
    push dx
    push word 0x0
    push es
    push word 0x0
    call intHandler1and2
    add sp, 12
    jmp end
int3:
    push word 0x0
    push dx
    push word 0x0
    push es
    push word 0x0
    call intHandler3
    add sp, 8
    mov bx, ax
    jmp end
int4:
    push word 0x0
    push dx
    push word 0x0
    push es
    push word 0x0
    push bx
    push word 0x0
    call intHandler4
    add sp, 12
    jmp end
int5:
    push word 0x0
    push dx
    push word 0x0
    push es
    push word 0x0
    push cx
    push word 0x0
    call intHandler5
    add sp, 12
    jmp end
end:
    mov al, 20h
    out 20h, al
    out 0a0h, al
    iret
