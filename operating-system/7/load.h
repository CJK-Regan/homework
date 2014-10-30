#ifndef LOAD
#define LOAD

void load(int head, int cylinder, int sector, int cs);

void loadSector(int n, int cs) {
    int sector = (n - 1) % 18 + 1;
    n = (n - 1) / 18;
    int cylinder = n >> 1;
    int head = n & 1;
    load(head, cylinder, sector, cs);
}

#endif
