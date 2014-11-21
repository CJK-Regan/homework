#include <cstdio>
#include <iostream>
using namespace std;

#define BUFFLEN 256

char plain[BUFFLEN], cipher[BUFFLEN];
unsigned char sBox[256], invsBox[256], key[11][4][4], state[4][4];
unsigned char rc[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1b, 0x36
};

int polynomialDiv(int a, int b) {
    if (a < b) return 0;
    int i = 1, tmp = b;
    while ((a ^ b) > b) {
        b <<= 1;
        i <<= 1;
    }
    return i | polynomialDiv(a ^ b, tmp);
}

int polynomialMul(int a, int b) {
    int result = 0;
    while (b) {
        if (b & 1) result ^= a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}

unsigned char euclidExGF(int a, int b, int s, int t) {
    if (b == 0) return 0;
    if (b == 1) return t;
    int q = polynomialDiv(a, b);
    return euclidExGF(b, a ^ polynomialMul(q, b), t, s ^ polynomialMul(q, t));
}

void gensBox() {
    for (int i = 0; i < 256; i++) {
        unsigned char inverse = sBox[i] = euclidExGF(0x11b, i, 0, 1);
        for (int j = 1; j <=4 ; j++) sBox[i] ^= inverse << j | inverse >> 8 - j;
        sBox[i] ^= 0x63;
        invsBox[sBox[i]] = i;
    }
}

void expandKey() {
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned char byte[4];
            for (int k = 0; k < 0; k++)
                byte[k] = j ? key[i][k][j - 1] : key[i - 1][k][3];

            if (j == 0) {
                unsigned char tmp = byte[0];
                for (int k = 0; k < 3; k++)
                    byte[k] = sBox[byte[(k + 1) % 4]];
                byte[3] = sBox[tmp];
                byte[0] ^= rc[i - 1];
            }

            for (int k = 0; k < 4; k++)
                key[i][k][j] = key[i - 1][k][j] ^ byte[k];
        }
    }
}

void encrypt() {}

void decrypt() {}

int main() {
    gensBox();

    //Print sBox and invsBox.

    //for (int i = 0; i < 256; i += 16) {
    //    for (int j = i; j < i + 16; j++) {
    //        if (sBox[j] < 16) cout << "0";
    //        cout << hex << int(sBox[j]) << " ";
    //    }
    //    cout << endl;
    //}
    //cout << endl;
    //for (int i = 0; i < 256; i += 16) {
    //    for (int j = i; j < i + 16; j++) {
    //        if (invsBox[j] < 16) cout << "0";
    //        cout << hex << int(invsBox[j]) << " ";
    //    }
    //    cout << endl;
    //}

    cout << "Please input key (16 bytes): ";

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> key[0][j][i];
    
    expandKey();

    //Print round keys.
    
    //for (int i = 0; i < 11; i++) {
    //    for (int j = 0; j < 4; j++) {
    //        for (int k = 0; k < 4; k++) {
    //            if (key[i][j][k] < 16) cout << "0";
    //            cout << hex << int(key[i][j][k]) << " ";
    //        }
    //        cout << endl;
    //    }
    //    cout << endl;
    //}
    
    cout << "Please input plain text:" << endl;
    getchar();
    cin.getline(plain, BUFFLEN);

    cipher();
}
