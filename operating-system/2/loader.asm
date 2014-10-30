    org 7c00h

    mov ax, cs
    mov ds, ax
    mov es, ax

    call Hello
    call Input

Load:
    mov bx, 0
    mov bl, byte [cur]
    add bx, list
    mov cl, byte [bx] ; 扇区号
    inc byte [cur]

    mov ax, 0
    mov es, ax
    mov ah, 2     ; 功能号
    mov al, 1     ; 读入扇区数
    mov bx, 7e00h ; ES:BX为读入数据到内存中的存储地址
    mov ch, 0     ; 柱面号
    mov dh, 0     ; 磁头号
    mov dl, 0     ; 驱动器号
    int 13h

    ; 清屏
    mov ah, 6h
    mov al, 0
    mov bh, 0
    mov cx, 0
    mov dh, 24
    mov dl, 79
    int 10h

    call 7e00h

    mov al, byte [cur]
    cmp al, byte [num]
    je 7c00h
    jmp Load

Hello:
    mov ah, 13h    ; 功能号
    mov al, 1      ; 输出后更新光标
    mov bh, 0      ; 页号
    mov bl, 7h     ; 闪烁(7)底色(6-4)字色(3-0)
    mov cx, MsgLen ; 串长
    mov dx, 0      ; 起始位置: DH(row), DL(column)
    mov bp, Msg    ; ES:BP = 串地址
    int 10h
    ret
Msg:
    db "OS:"
    db 0ah, 0dh
    db "Hello, human."
    db 0ah, 0dh
    db "Key in the number of sector to load (1-3): "
    db 0ah, 0dh
    MsgLen equ $-Msg

Input:
    ; 读入一个按键
    mov ah, 0
    int 16h
    ; 回显字符
    mov ah, 0eh
    mov bl, 0
    int 10h
    ; 回车结束读入
    cmp al, 0dh
    je return
    ; 将输入转换成扇区号存入list
    sub al, 2fh
    mov bx, 0
    mov bl, byte [num]
    add bx, list
    mov byte [bx], al
    inc byte [num]
    jmp Input
return:
    ret

    cur db 0  ; 当前执行的程序
    num db 0  ; 等待执行的程序数
    list db 0 ; 程序队列

    times 510-($-$$) db 0
    dw 0aa55h
