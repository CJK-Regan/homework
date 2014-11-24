#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define BUFFLEN 256

char plain[BUFFLEN], cipher[BUFFLEN], ctrPlain[BUFFLEN];
int counterSize;
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

int polynomialMul(int a, int b, bool GF=false) {
    int result = 0;
    while (b) {
        if (b & 1) result ^= a;
        a <<= 1;
        if (GF && a & 0x100) a ^= 0x11b;
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
            for (int k = 0; k < 4; k++)
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

void addRoundKey(int n) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state[i][j] ^= key[n][i][j];
}

void substituteBytes(bool inv=false) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (inv) state[i][j] = invsBox[state[i][j]];
            else state[i][j] = sBox[state[i][j]];
}

void shiftRows(bool inv=false) {
    unsigned char tmp[4];
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            if (inv) tmp[j] = state[i][(j - i + 4) % 4];
            else tmp[j] = state[i][(i + j) % 4];
        for (int j = 0; j < 4; j++)
            state[i][j] = tmp[j];
    }
}

void mixColumns(bool inv=false) {
    unsigned char tmp[4];
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            tmp[j] = state[j][i];
        for (int j = 0; j < 4; j++)
            if (inv)
                state[j][i] = polynomialMul(0xe, tmp[j], true) ^
                              polynomialMul(0xb, tmp[(j + 1) % 4], true) ^
                              polynomialMul(0xd, tmp[(j + 2) % 4], true) ^
                              polynomialMul(0x9, tmp[(j + 3) % 4], true);
            else
                state[j][i] = polynomialMul(2, tmp[j], true) ^
                              polynomialMul(3, tmp[(j + 1) % 4], true) ^
                              polynomialMul(1, tmp[(j + 2) % 4], true) ^
                              polynomialMul(1, tmp[(j + 3) % 4], true);
    }
}

void encrypt() {
    for (int i = 0; plain[i]; i += 16) {
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                state[k][j] = plain[i + 4 * j + k];

        addRoundKey(0);
        for (int r = 1; r <= 10; r++) {
            substituteBytes();
            shiftRows();
            if (r != 10) mixColumns();
            addRoundKey(r);
        }

        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                cipher[i + 4 * j + k] = state[k][j];
    }
}

void decrypt() {
    for (int i = 0; cipher[i]; i += 16) {
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                state[k][j] = cipher[i + 4 * j + k];

        addRoundKey(10);
        for (int r = 9; r >= 0; r--) {
            shiftRows(true);
            substituteBytes(true);
            addRoundKey(r);
            if (r) mixColumns(true);
        }

        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                plain[i + 4 * j + k] = state[k][j];
    }
}

void ctr() {
    for (int i = 0; ctrPlain[i]; i += counterSize)
        for (int j = 0; j < counterSize && i + j < strlen(ctrPlain); j++)
            ctrPlain[i + j] ^= cipher[j];
}

int main() {
    gensBox();

    //Print sBox and invsBox.

    //cout << "S Box:" << endl;
    //for (int i = 0; i < 256; i += 16) {
    //    for (int j = i; j < i + 16; j++) {
    //        if (sBox[j] < 16) cout << "0";
    //        cout << hex << int(sBox[j]) << " ";
    //    }
    //    cout << endl;
    //}
    //cout << "Inverse S Box:" << endl;
    //for (int i = 0; i < 256; i += 16) {
    //    for (int j = i; j < i + 16; j++) {
    //        if (invsBox[j] < 16) cout << "0";
    //        cout << hex << int(invsBox[j]) << " ";
    //    }
    //    cout << endl;
    //}

    cout << "Please input key (16 bytes):" << endl;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> key[0][j][i];
    
    expandKey();

    //Print round keys.
    
    //cout << "Round keys:" << endl;
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

    encrypt();

    //Print cipher text.

    cout << "Cipher text (in hex):" << endl;
    for (int i = 0; cipher[i]; i += 16) {
        for (int j = i; j < i + 16; j++) {
            if ((unsigned char)cipher[j] < 16) cout << "0";
            cout << hex << int((unsigned char)cipher[j]) << " ";
        }
        cout << endl;
    }
    
    memset(plain, 0, sizeof(plain));
    decrypt();

    //Print plain text.

    cout << "Plain text after decryption:" << endl;
    cout << plain << endl;

    //CTR mode

    memset(plain, 0, sizeof(plain));
    memset(cipher, 0, sizeof(cipher));

    cout << "Please input plain text of CTR mode:" << endl;
    cin.getline(ctrPlain, BUFFLEN);
    cout << "Please input counter size of CTR mode:" << endl;
    cin >> counterSize;
    cout << "Please input counter of CTR mode (" << counterSize << " bytes):"
         << endl;
    getchar();
    cin.getline(plain, BUFFLEN);

    encrypt();

    ctr();

    cout << "Cipher text of CTR mode (in hex):" << endl;
    for (int i = 0; ctrPlain[i]; i += counterSize) {
        for (int j = i; j < i + counterSize && ctrPlain[j]; j++) {
            if ((unsigned char)ctrPlain[j] < 16) cout << "0";
            cout << hex << int((unsigned char)ctrPlain[j]) << " ";
        }
        cout << endl;
    }

    ctr();

    cout << "Plain text after decryption of CTR mode:" << endl;
    cout << ctrPlain << endl;
}
