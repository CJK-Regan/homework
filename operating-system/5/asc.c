asm(".code16gcc");

char getChar();
void putChar(char c);

void asc() {
    char *msg = "Keyin a character to display its ascii (ESC to quit):\n";
    while (*msg)
        putChar(*msg++);
    putChar(0xd);
    char c;
    int i;
    while (1) {
        i = c = getChar();
        putChar('0' + i / 100);
        putChar('0' + i % 100 / 10);
        putChar('0' + i % 10);
        putChar(0xa);
        putChar(0xd);
        if (c == 0x1b)
            break;
    }
}
