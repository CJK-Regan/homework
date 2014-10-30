#define BUFFER_LEN 1000

void load(int head, int cylinder, int sector, int num);
int getCentury();
int getYear();
int getMonth();
int getDay();
int getHour();
int getMinute();
int getSecond();
void clear();

void loadSector(int n, int l) {
    int sector = (n - 1) % 18 + 1;
    n = (n - 1) / 18;
    int cylinder = n >> 1;
    int head = n & 1;
    load(head, cylinder, sector, l);
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
