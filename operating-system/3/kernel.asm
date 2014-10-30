[bits 16]

    extern cmain

[section .text]
    global _start
    global load
    global putChar
    global getChar
    global getCentury
    global getYear
    global getMonth
    global getDay
    global getHour
    global getMinute
    global getSecond
    global clear

_start:
    mov ax, cs
    mov ds, ax

    push word 0x0
    call cmain
    jmp $

load:
    push bp
    mov bp, sp

    mov ax, 0
    mov es, ax
    mov ah, 2             ; 功能号
    mov al, 2             ; 读入扇区数
    mov bx, 7e00h         ; ES:BX为读入数据到内存中的存储地址
    mov ch, byte [bp+0xa] ; 柱面号
    mov cl, byte [bp+0xe] ; 扇区号
    mov dh, byte [bp+0x6] ; 磁头号
    mov dl, 0             ; 驱动器号
    int 13h

    call 7e0h:0

    mov ax, cs
    mov ds, ax

    mov sp, bp
    pop bp
    jmp returnC

putChar:
    push bp
    mov bp, sp
    mov ah, 0eh
    mov al, byte [bp+0x6]
    mov bx, 0
    mov sp, bp
    int 10h
    pop bp
    jmp returnC

getChar:
    mov ah, 0
    int 16h
    jmp returnC

getDate:
    mov ah, 4h
    int 1ah
    mov ah, 0
    ret
getCentury:
    call getDate
    mov al, ch
    jmp returnC
getYear:
    call getDate
    mov al, cl
    jmp returnC
getMonth:
    call getDate
    mov al, dh
    jmp returnC
getDay:
    call getDate
    mov al, dl
    jmp returnC

getTime:
    mov ah, 2h
    int 1ah
    mov ah, 0
    ret
getHour:
    call getTime
    mov al, ch
    jmp returnC
getMinute:
    call getTime
    mov al, cl
    jmp returnC
getSecond:
    call getTime
    mov al, dh
    jmp returnC

clear:
    mov ah, 0
    mov al, 3
    int 10h
    jmp returnC

returnC:
    pop bx
    pop cx
    push bx
    ret
