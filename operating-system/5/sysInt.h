#ifndef SYSINT
#define SYSINT

#include "string.h"

void setSysInt();

void intHandler1and2(int es, int dx, int op) {
    char *addr = (char *)(es * 16 + dx);
    while (*addr) {
        if (op == 1) {
            if (*addr >= 'a' && *addr <= 'z')
                *addr = 'A' + *addr - 'a';
        }
        else if (op == 2) {
            if (*addr >= 'A' && *addr <= 'Z')
                *addr = 'a' + *addr - 'A';
        }
        addr++;
    }
}

int intHandler3(int es, int dx) {
    int result = 0;
    char *addr = (char *)(es * 16 + dx);
    while (*addr)
        result = result * 10 + (*addr++) - '0';
    return result;
}

void intHandler4(int bx, int es, int dx) {
    char *addr = (char *)(es * 16 + dx);
    char *num = toString(bx);
    while (*num)
        *addr++ = *num++;
    *addr = '\0';
}

void intHandler5(int cx, int es, int dx) {
    char *addr = (char *)(es * 16 + dx);
    int gs = ((cx >> 8) * 80 + (cx & 0xff)) * 2;
    while (*addr) {
        absPutChar(gs, *addr++);
        gs += 2;
    }
}

#endif
