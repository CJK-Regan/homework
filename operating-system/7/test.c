asm(".code16gcc");

#include "sysCalls.h"
#include "string.h"

void test() {
    putChar('a');
    int pid = Pfork();
    if (pid) {
        putChar('b');
        Pwait();
        putChar('c');
    }
    else
        putChar('d');
    Pexit();
}
