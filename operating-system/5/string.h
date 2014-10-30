#ifndef BUFFER_LEN
#define BUFFER_LEN 1000
#endif

#ifndef STRING
#define STRING

void putChar(char c);
void absPutChar(int gs, char c);
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

char *getString() {
    static char buffer[BUFFER_LEN];
    int i = 0;
    while (i < BUFFER_LEN) {
        char c = getChar();
        if (c == 0xd) {
            buffer[i] = 0;
            putChar(0xd);
            putChar(0xa);
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

char *toString(short n) {
    static char buffer[BUFFER_LEN];
    int i = BUFFER_LEN - 1;
    if (!n)
        buffer[--i] = '0';
    while (n && i) {
        buffer[--i] = '0' + n % 10;
        n /= 10;
    }
    return buffer + i;
}

#endif
