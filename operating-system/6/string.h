#ifndef STRING
#define STRING

#define BUFFER_LEN 1000

void putChar(char c);
void absPutChar(short bp, char c);
char getChar();

int strcmp(char *a, char *b) {
    while (*a == *b) {
        if (*a == 0 && *b == 0)
            return 0;
        a++;
        b++;
    }
    return *a - *b;
}

void putString(char *message) {
    while (*message)
        if (*message == '\n') {
            putChar(0xd);
            putChar(0xa);
            message++;
        }
        else
            putChar(*message++);
}

void absPutString(char *message, short row, short col) {
    short bp = (80 * row + col) * 2;
    while (*message) {
        absPutChar(bp, *message++);
        bp += 2;
    }
}

char *getString() {
    static char buffer[BUFFER_LEN];
    int i = 0;
    while (i < BUFFER_LEN) {
        char c = getChar();
        if (c == 0xd) {
            buffer[i] = 0;
            int j = i;
            while (j--) {
                putChar(0x8);
                putChar(0x20);
                putChar(0x8);
            }
            break;
        }
        if (c == 0x8) {
            if (i) {
                putChar(0x8);
                putChar(0x20);
                putChar(0x8);
                i--;
            }
        }
        else {
            putChar(c);
            buffer[i++] = c;
        }
    }
    return buffer;
}

char *toString(unsigned int n) {
    static char buffer[BUFFER_LEN];
    unsigned int i = BUFFER_LEN - 1;
    if (!n)
        buffer[--i] = '0';
    while (n && i) {
        buffer[--i] = '0' + n % 10;
        n /= 10;
    }
    return buffer + i;
}

#endif
