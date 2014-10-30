    mov ax, 1000h
    mov es, ax
    mov ah, 2
    mov al, 10
    mov bx, 0
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0
    int 13h

    jmp 1000h:0

    times 510-($-$$) db 0
    dw 0aa55h
