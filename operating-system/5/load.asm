%ifndef LOAD
%define LOAD

    global load

load:
    push bp
    mov bp, sp

    mov ax, 0
    mov es, ax
    mov ah, 2              ; 功能号
    mov al, byte [bp+0x12] ; 读入扇区数
    mov bx, 7e00h          ; ES:BX为读入数据到内存中的存储地址
    mov ch, byte [bp+0xa]  ; 柱面号
    mov cl, byte [bp+0xe]  ; 扇区号
    mov dh, byte [bp+0x6]  ; 磁头号
    mov dl, 0              ; 驱动器号
    int 13h

    call 7e0h:0

    mov ax, cs
    mov ds, ax

    mov sp, bp
    pop bp
    jmp returnC

    %include "returnC.asm"

%endif
