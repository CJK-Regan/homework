%ifndef TIMER
%define TIMER

setTimer:
    mov ax, 0
    mov es, ax
    mov word [es:20h], timer
    mov ax, cs
    mov word [es:22h], ax
    ret

timer:
    push ds
    mov ax, cs
    mov ds, ax

    dec byte [gap]
    jnz _end
    mov ax, 0b800h
    mov gs, ax
    cmp byte [curChar], 3
    jnz _next1
    mov byte [gs:9eh], '/'
_next1:
    cmp byte [curChar], 2
    jnz _next2
    mov byte [gs:9eh], '-'
_next2:
    cmp byte [curChar], 1
    jnz _next3
    mov byte [gs:9eh], '\'
_next3:
    cmp byte [curChar], 0
    jnz _next4
    mov byte [gs:9eh], '|'
    mov byte [curChar], 4
_next4:
    dec byte [curChar]
    mov byte [gap], 2
_end:
    mov al, 20h
    out 20h, al
    out 0a0h, al
    pop ds
    iret

    gap db 2
    curChar db 3

%endif
