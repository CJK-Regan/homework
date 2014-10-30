%ifndef MULTIPROCESS
%define MULTIPROCESS

    extern ax_save
    extern bx_save
    extern cx_save
    extern dx_save
    extern si_save
    extern di_save
    extern bp_save
    extern sp_save
    extern ip_save
    extern cs_save
    extern ds_save
    extern es_save
    extern ss_save
    extern flags_save
    extern ret_save
    extern scheduler
    global setTimer
    global blockInterrupt
    global enableInterrupt

setTimer:
    mov al, 34h
    out 43h, al
    mov ax, 1193182/20
    out 40h, al
    mov al, ah
    out 40h, al

    mov ax, 0
    mov es, ax
    mov word [es:20h], timer
    mov ax, cs
    mov word [es:22h], ax
    jmp returnC

timer:
    call save
    push word 0x0
    call scheduler

    mov al, 20h
    out 20h, al
    out 0a0h, al

    call recover
    iret

save:
    push ds
    push cs
    pop ds
    pop word [ds:ds_save]
    pop word [ds:ret_save]
    pop word [ds:ip_save]
    pop word [ds:cs_save]
    pop word [ds:flags_save]
    mov word [ds:ax_save], ax
    mov word [ds:bx_save], bx
    mov word [ds:cx_save], cx
    mov word [ds:dx_save], dx
    mov word [ds:si_save], si
    mov word [ds:di_save], di
    mov word [ds:bp_save], bp
    mov word [ds:sp_save], sp
    mov word [ds:es_save], es
    mov word [ds:ss_save], ss
    push word [ds:ret_save]
    ret

recover:
    pop word [ds:ret_save]
    mov ax, word [ds:ax_save]
    mov bx, word [ds:bx_save]
    mov cx, word [ds:cx_save]
    mov dx, word [ds:dx_save]
    mov si, word [ds:si_save]
    mov di, word [ds:di_save]
    mov bp, word [ds:bp_save]
    mov sp, word [ds:sp_save]
    mov es, word [ds:es_save]
    mov ss, word [ds:ss_save]
    push word [ds:flags_save]
    push word [ds:cs_save]
    push word [ds:ip_save]
    push word [ds:ret_save]
    push word [ds:ds_save]
    pop ds
    ret

blockInterrupt:
    cli
    jmp returnC
enableInterrupt:
    sti
    jmp returnC

    %include "returnC.asm"
    %include "load.asm"

%endif
