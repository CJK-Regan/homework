    org 7c00h

    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ax, 0b800h ; 彩色文本显存首地址
    mov gs, ax

Data:
    row db 0 ; 当前行
    col db 0 ; 当前列
    chr db 1 ; 行移动方向
    chc db 1 ; 列移动方向

    count dw 0
    ccount dw 0
    gap equ 500
    ggap equ 500

Loop:
    ; 计数器
    inc word [count]
    cmp word [count], gap
    jnz Loop
    mov word [count], 0
    inc word [ccount]
    cmp word [ccount], ggap
    jnz Loop
    mov word [ccount], 0

    call Show ; 调用显示例程

    ; 改变坐标
    mov al, byte [chr]
    add byte [row], al
    mov al, byte [chc]
    add byte [col], al

    call CheckBorder ; 调用检查边界例程

    jmp Loop

CheckBorder:
    cmp byte [row], 0
    jnz next1
    mov byte [chr], 1
next1:
    cmp byte [row], 24
    jnz next2
    mov byte [chr], -1
next2:
    cmp byte [col], 0
    jnz next3
    mov byte [chc], 1
next3:
    cmp byte [col], 79
    jnz next4
    mov byte [chc], -1
next4:
    ret

Show:
    mov ax, 0
    mov al, byte [row]
    mov bx, 80
    mul bx
    mov bx, 0
    mov bl, byte [col]
    add ax, bx
    mov bx, 2
    mul bx
    mov bp, ax
    mov ah, 0fh
    mov al, byte [Char]
    mov word [gs:bp], ax
    ret

Char: db "O"

    times 510-($-$$) db 0
    dw 0aa55h
