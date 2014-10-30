    org 7c00h

    mov ax, cs
    mov ds, ax
    mov ax, 0
    mov es, ax

    mov ah, 2    ; 功能号
    mov al, 20   ; 读入扇区数
    mov bx, 500h ; ES:BX为读入数据到内存中的存储地址
    mov ch, 0    ; 柱面号
    mov cl, 2    ; 扇区号
    mov dh, 0    ; 磁头号
    mov dl, 0    ; 驱动器号
    int 13h

    jmp 50h:0

    times 510-($-$$) db 0
    dw 0aa55h
