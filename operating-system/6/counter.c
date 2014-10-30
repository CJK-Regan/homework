asm(".code16gcc");

#define GAP 100000000

void absPutChar(short bp, char c);

void counter() {
    char c = '0';
    int gap = GAP;
    absPutChar(2 * (12 * 80 + 8 * (c - '0')), c);
    while (gap--)
        if (!gap) {
            gap = GAP;
            absPutChar(2 * (12 * 80 + 8 * (c - '0')), ' ');
            if (c == '9')
                c = '0';
            else 
                c++;
            absPutChar(2 * (12 * 80 + 8 * (c - '0')), c);
        }
}
