#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

#define BUFFLEN 256

struct PublicKey { unsigned long N, e; } publicKey;
struct PrivateKey { unsigned long d, p, q; } privateKey;
unsigned int test;
long s, t; // For euclidEx

// a * b % m
unsigned long mulMod(unsigned long a, unsigned long b, unsigned long m) {
    unsigned long result = 0;
    while (b) {
        if (b & 1) result = (result + a) % m;
        if (b >>= 1) a = 2 * a % m;
    }
    return result;
}

// a ^ e % m
unsigned long expMod(unsigned long a, unsigned long e, unsigned long m) {
    unsigned long result = 1;
    while (e) {
        if (e & 1) result = mulMod(result, a, m);
        if (e >>= 1) a = mulMod(a, a, m);
    }
    return result;
}

bool millerRabin(int t) {
    unsigned int q = test - 1, k = 0;
    while (q & 1 == 0) {
        q >>= 1;
        k++;
    }
    while (t--) {
        unsigned int a = rand() + 2; // 1 < a < test - 1
        unsigned int tmp = expMod(a, q, test);
        if (tmp == 1 || tmp == test - 1) return true;
        for (int i = 1; i < k; i++)
            if (expMod(tmp, 2, test) == test - 1) return true;
    }
    return false;
}

unsigned int genPrime(int t) {
    do test = 0x40000001 | rand();
    while (test % 5 == 0 || (test - 1) % 3 == 0);
    if (millerRabin(t)) return test;
    else return genPrime(t);
}

unsigned long euclidEx(unsigned long a, unsigned long b) {
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    }
    unsigned long r = euclidEx(b, a % b);
    unsigned long tmp = s;
    s = t;
    t = tmp - a / b * t;
    return r;
}

int main() {
    srand(time(NULL));
    privateKey.p = genPrime(20);
    privateKey.q = genPrime(20);
    publicKey.N = privateKey.p * privateKey.q;
    publicKey.e = 3;
    unsigned long fN = (privateKey.p - 1) * (privateKey.q - 1);
    euclidEx(fN, publicKey.e);
    privateKey.d = (t + fN) % fN;

    cout << "Public: (" << publicKey.N << "," << publicKey.e << ")" << endl;
    cout << "Private: (" << privateKey.d << "," << privateKey.p << ","
         << privateKey.q << ")" << endl;

    char plain[BUFFLEN];
    unsigned long cypher[BUFFLEN];
    cout << "Please input plain text: ";
    cin.getline(plain, BUFFLEN);
    int len = strlen(plain);

    cout << "Cypher (after encryption):" << endl;
    for (int i = 0; i < len; i++) {
        cypher[i] = expMod(plain[i], publicKey.e, publicKey.N);
        cout << cypher[i] << " ";
    }
    cout << endl;

    cout << "Plain (after decrpytion):" << endl;
    for (int i = 0; i < len; i++)
        plain[i] = expMod(cypher[i], privateKey.d, publicKey.N);
    cout << plain << endl;
}
