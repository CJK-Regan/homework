#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

unsigned int test;

unsigned int expMod(unsigned long a, unsigned int e, unsigned int m) {
    unsigned long result = 1;
    while (e) {
        if (e & 1) result = result * a % m;
        if (e >>= 1) a = a * a % m;
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

int main() {
    srand(time(NULL));
    // How many prime numbers to find and how many turns of test:
    int n = 2, t = 10;
    while (n) {
        // Previously make sure test number is not a multiple of 2 or 5.
        do test = 0x80000001 | rand(); while (test % 5 == 0);
        cout << test << " ";
        if (millerRabin(t)) {
            cout << "prime!" << endl;
            n--;
        }
        else cout << "composite" << endl;
    }
}
