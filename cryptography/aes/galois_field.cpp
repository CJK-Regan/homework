#include <iostream>
#include <string>
using namespace std;

void printGF() {
    cout << 0 << endl;
    for (int i = 1; i < 256; i++) {
        bool first = true;
        for (int j = 0; j < 8; j++)
            if (i & 1 << 7 - j) {
                if (!first) cout << " + ";
                else first = false;
                if (j < 7) cout << "x^" << 7 - j;
                else cout << 1;
            }
        cout << endl;
    }
}

int polynomialDiv(int a, int b) {
    if (a < b) return 0;
    int i = 1;
    int tmp = b;
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

void printSB() {
    unsigned char sb[256];
    for (int i = 0; i < 256; i++) {
        unsigned char inverse = sb[i] = euclidExGF(0x11b, i, 0, 1);
        for (int j = 1; j <=4 ; j++) sb[i] ^= inverse << j | inverse >> 8 - j;
        sb[i] ^= 0x63;
    }
    for (int i = 0; i < 256; i += 16) {
        for (int j = i; j < i + 16; j++) {
            if (sb[j] < 16) cout << "0";
            cout << hex << (unsigned int)(sb[j]) << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "GF_2^8:" << endl;
    printGF();
    cout << endl;
    cout << "AES S box:" << endl;
    printSB();
}
