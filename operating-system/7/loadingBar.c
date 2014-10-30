asm(".code16gcc");

#define GAP 1000000

void absPutChar(short bp, char c);

void bar() {
    int gap = GAP, i = 0;
    char c = '*';
    while (gap--)
        if (!gap) {
            gap = GAP;
            absPutChar(2 * (80 * 24 + i++), c);
            if (i == 80) {
                c = c == '*' ? ' ' : '*';
                i = 0;
            }
        }
}
