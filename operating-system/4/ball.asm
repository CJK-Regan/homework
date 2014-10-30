    mov ax, cs
    mov ds, ax
    mov ax, 0b800h
    mov gs, ax

    mov ax, 0
    mov es, ax
    push word [es:24h]
    pop word [tmp1]
    push word [es:26h]
    pop word [tmp2]
    mov word [es:24h], keypress
    mov ax, cs
    mov word [es:26h], ax

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

    call Show 

    ; 改变坐标
    mov al, byte [chr]
    add byte [row], al
    mov al, byte [chc]
    add byte [col], al

    call CheckBorder ; 调用检查边界例程
    cmp byte [row], 24
    jnz Loop
    cmp byte [col], 0
    jnz Loop

    mov ax, 0
    mov es, ax
    push word [tmp1]
    pop word [es:24h]
    push word [tmp2]
    pop word [es:26h]
    retf

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
    push bp
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
    mov byte [gs:bp], 'O'
    pop bp
    ret

Data:
    row db 0 ; 当前行
    col db 0 ; 当前列
    chr db 1 ; 行移动方向
    chc db 1 ; 列移动方向

    count dw 0
    ccount dw 0
    gap equ 5000
    ggap equ 5000

    tmp1 dw 0
    tmp2 dw 0

keypress:
    in al, 60h
    cmp al, 2
    jnz _next1
    mov ax, 0b800h
    mov gs, ax
    mov byte [gs:40h], 'O'
    mov byte [gs:42h], 'U'
    mov byte [gs:44h], 'C'
    mov byte [gs:46h], 'H'
    mov byte [gs:48h], '!'
    mov byte [gs:4ah], 'O'
    mov byte [gs:4ch], 'U'
    mov byte [gs:4eh], 'C'
    mov byte [gs:50h], 'H'
    mov byte [gs:52h], '!'
    jmp _end
_next1:
    cmp al, 3
    jnz _next2
    int 33h
    jmp _end
_next2:
    cmp al, 4
    jnz _next3
    int 34h
    jmp _end
_next3:
    cmp al, 5
    jnz _next4
    int 35h
    jmp _end
_next4:
    cmp al, 6
    jnz _end
    int 36h
_end:
    mov al, 20h
    out 20h, al
    out 0a0h, al
    iret
