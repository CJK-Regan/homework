#include <iostream>
using namespace std;

int s, t;

void gcdEx(int a, int b) {
    if (b == 0) {
        s = 1;
        t = 0;
        return;
    }
    gcdEx(b, a % b);
    int tmp = s;
    s = t;
    t = tmp - a / b * t;
}

int main() {
    int a, b;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    gcdEx(a, b);
    cout << "s = " << s << ", t = " << t << endl;
}
