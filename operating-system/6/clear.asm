%ifndef CLEAR
%define CLEAR

    global clear

clear:
    mov ah, 0
    mov al, 3
    int 10h
    jmp returnC

    %include "returnC.asm"

%endif
