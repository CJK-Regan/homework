%ifndef DATETIME
%define DATETIME

    global getCentury
    global getYear
    global getMonth
    global getDay
    global getHour
    global getMinute
    global getSecond

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

    %include "returnC.asm"

%endif
