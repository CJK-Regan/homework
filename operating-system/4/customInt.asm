setTimer:
    mov ax, 0
    mov es, ax
    mov word [es:20h], timer
    mov ax, cs
    mov word [es:22h], ax
    ret

setCustomInt:
    mov ax, 0
    mov es, ax
    mov ax, cs
    mov word [es:0cch], int33
    mov word [es:0ceh], ax
    mov word [es:0d0h], int34
    mov word [es:0d2h], ax
    mov word [es:0d4h], int35
    mov word [es:0d6h], ax
    mov word [es:0d8h], int36
    mov word [es:0dah], ax
    ret

int33:
    mov ax, 0b800h
    mov gs, ax
    mov byte [gs:220h], 'i'
    mov byte [gs:222h], 'n'
    mov byte [gs:224h], 't'
    mov byte [gs:226h], '3'
    mov byte [gs:228h], '3'
    mov al, 20h
    out 20h, al
    out 0a0h, al
    iret

int34:
    mov ax, 0b800h
    mov gs, ax
    mov byte [gs:360h], 'i'
    mov byte [gs:362h], 'n'
    mov byte [gs:364h], 't'
    mov byte [gs:366h], '3'
    mov byte [gs:368h], '4'
    mov al, 20h
    out 20h, al
    out 0a0h, al
    iret

int35:
    mov ax, 0b800h
    mov gs, ax
    mov byte [gs:4a0h], 'i'
    mov byte [gs:4a2h], 'n'
    mov byte [gs:4a4h], 't'
    mov byte [gs:4a6h], '3'
    mov byte [gs:4a8h], '5'
    mov al, 20h
    out 20h, al
    out 0a0h, al
    iret

int36:
    mov ax, 0b800h
    mov gs, ax
    mov byte [gs:5e0h], 'i'
    mov byte [gs:5e2h], 'n'
    mov byte [gs:5e4h], 't'
    mov byte [gs:5e6h], '3'
    mov byte [gs:5e8h], '6'
    mov al, 20h
    out 20h, al
    out 0a0h, al
    iret

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
