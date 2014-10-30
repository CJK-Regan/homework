%ifndef RETURN_C
%define RETURN_C

returnC:
    pop bx
    pop cx
    push bx
    ret

%endif
