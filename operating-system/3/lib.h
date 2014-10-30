#define BUFFER_LEN 1000

void load(int head, int cylinder, int sector);
void putChar(char c);
char getChar();
int getCentury();
int getYear();
int getMonth();
int getDay();
int getHour();
int getMinute();
int getSecond();
void clear();

int strcmp(char *a, char *b) {
    while (*a == *b) {
        if (*a == 0 && *b == 0)
            return 0;
        a++;
        b++;
    }
    return *a - *b;
}

void loadSector(int n) {
    int sector = (n - 1) % 18 + 1;
    n = (n - 1) / 18;
    int cylinder = n % 80;
    int head = n / 80;
    load(head, cylinder, sector);
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
    while (n && i) {
        buffer[--i] = '0' + n % 10;
        n /= 10;
    }
    return buffer + i;
}

int BCDdecode(int n) {
    return n / 16 * 10 + n % 16;
}

char *getDate() {
    static char date[11];
    int tmp;
    tmp = BCDdecode(getCentury());
    date[0] = '0' + tmp / 10;
    date[1] = '0' + tmp % 10;
    tmp = BCDdecode(getYear());
    date[2] = '0' + tmp / 10;
    date[3] = '0' + tmp % 10;
    date[4] = '-';
    tmp = BCDdecode(getMonth());
    date[5] = '0' + tmp / 10;
    date[6] = '0' + tmp % 10;
    date[7] = '-';
    tmp = BCDdecode(getDay());
    date[8] = '0' + tmp / 10;
    date[9] = '0' + tmp % 10;
    return date;
}

char *getTime() {
    static char time[9];
    int tmp;
    tmp = BCDdecode(getHour());
    time[0] = '0' + tmp / 10;
    time[1] = '0' + tmp % 10;
    time[2] = ':';
    tmp = BCDdecode(getMinute());
    time[3] = '0' + tmp / 10;
    time[4] = '0' + tmp % 10;
    time[5] = ':';
    tmp = BCDdecode(getSecond());
    time[6] = '0' + tmp / 10;
    time[7] = '0' + tmp % 10;
    return time;
}
