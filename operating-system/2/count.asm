    org  7e00h

    mov ax, cs
    mov ds, ax
    mov	es, ax
    mov ax, 0b800h ; 彩色文本显存首地址
    mov gs, ax

    row db 0
    char db '9'
    count dw 0
    ccount dw 0
    gap equ 1000
    ggap equ 1000

Loop:
    ; 计时器
    inc word [count]
    cmp word [count], gap
    jnz Loop
    mov word [count], 0
    inc word [ccount]
    cmp word [ccount], ggap
    jnz Loop
    mov word [ccount], 0
    call Show ; 调用显示例程
    cmp byte [char], '0'
    je Return
    inc byte [row]
    dec byte [char]
    jmp Loop

Show:
    mov ax, 0
    mov al, byte [row]
    mov bx, 160
    mul bx
    mov bp, ax
    mov ah, 0fh
    mov al, byte [char]
    mov word [gs:bp], ax
    ret

Return:
    ; 清屏
    mov ah, 6h
    mov al, 0
    mov bh, 0
    mov cx, 0
    mov dh, 24
    mov dl, 79
    int 10h
    retf
