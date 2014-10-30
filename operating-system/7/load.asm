%ifndef LOAD
%define LOAD

    global load

load:
    push bp
    mov bp, sp

    mov ah, 2
    mov al, 4              ; 读入扇区数
    mov bx, 0
    mov es, word [bp+0x12] ; ES:BX为读入数据到内存中的存储地址
    mov ch, byte [bp+0xa]  ; 柱面号
    mov cl, byte [bp+0xe]  ; 扇区号
    mov dh, byte [bp+0x6]  ; 磁头号
    mov dl, 0
    int 13h

    mov sp, bp
    pop bp
    jmp returnC

    %include "returnC.asm"

%endif
