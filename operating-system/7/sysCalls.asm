%ifndef SYSCALLS
%define SYSCALLS

    global Pfork
    global Pwait
    global Pexit

Pfork:
    cli
    mov ah, 0
    int 21h
    sti
    jmp returnC

Pwait:
    cli
    mov ah, 1
    int 21h
    sti
    jmp returnC

Pexit:
    cli
    mov ah, 2
    int 21h
    sti
    jmp returnC

    %include "returnC.asm"

%endif
