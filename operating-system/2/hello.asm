    org  7e00h

    mov ax, cs
    mov ds, ax

    mov	ax, 0B800h
    mov	es, ax

    mov byte [es:00], 'H'
    mov byte [es:01], 0F0h
    mov byte [es:02], 'e'
    mov byte [es:03], 0F0h
    mov byte [es:04], 'l'
    mov byte [es:05], 0F0h
    mov byte [es:06], 'l'
    mov byte [es:07], 0F0h
    mov byte [es:08], 'o'
    mov byte [es:09], 0F0h
    mov byte [es:10], '!'
    mov byte [es:11], 0F0h

    mov ax, cs
    mov es, ax

    mov ah, 13h    ; 功能号
    mov al, 1      ; 输出后更新光标
    mov bh, 0      ; 页号
    mov bl, 7h     ; 闪烁(7)底色(6-4)字色(3-0)
    mov cx, MsgLen ; 串长
    mov dx, 200h   ; 起始位置: DH(row), DL(column)
    mov bp, Msg    ; ES:BP = 串地址
    int 10h
    
Input:
    mov ah, 0   ; 功能号
    int 16h
    cmp al, 1bh ; ESC
    je Return
    jmp Input

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

Msg:
    db "This is program 1 in sector 2."
    db 0ah, 0dh
    db "Press ESC to continue."
    MsgLen equ $-Msg
