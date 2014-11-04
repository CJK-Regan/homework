#include <iostream>
using namespace std;

int s, t;

int gcdEx(int a, int b) {
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    }
    int r = gcdEx(b, a % b);
    int tmp = s;
    s = t;
    t = tmp - a / b * t;
    return r;
}

int main() {
    int a = 26, b;
    cout << "b = ";
    cin >> b;
    int r = gcdEx(a, b);
    if (r != 1)
        cout << "No inverse" << endl;
    else {
        int x = t % 26;
        if (x < 0) x += 26;
        cout << "Inverse of " << b << " mod 26 is " << x << endl;
    }
}
