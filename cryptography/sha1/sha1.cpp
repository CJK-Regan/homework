#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

unsigned W[80], K[4] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};
unsigned A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476,
         E = 0xc3d2e1f0, T;

unsigned leftRotate(unsigned input, int bits) {
    return (input << bits) | (input >> (32 - bits));
}

unsigned f(int t) {
    switch (t / 20) {
        case 0: return (B & C) | ((~B) & D);
        case 1: return B ^ C ^ D;
        case 2: return (B & C) | (B & D) | (C & D);
        case 3: return B ^ C ^ D;
    }
}

void sha1(string input) {
    string buffer = input;
    // Padding
    buffer += (unsigned char)0x80;
    while (buffer.size() % 64 != 56) buffer += char(0);
    // Append length
    for (int i = 56; i >= 0; i -= 8)
        buffer += (unsigned char)((input.size() << 3) >> i);
    // Deal with block of 512 bits each turn
    for (int i = 0; i < buffer.size(); i += 64) {
        // Initialize W
        for (int j = 0; j < 16; j++) {
            W[j] = unsigned(buffer[i + 4 * j] & 0xff) << 24 |
                   unsigned(buffer[i + 4 * j + 1] & 0xff) << 16 |
                   unsigned(buffer[i + 4 * j + 2] & 0xff) << 8 |
                   unsigned(buffer[i + 4 * j + 3] & 0xff);
            cout << setw(8) << setfill('0') << hex << W[j] << " ";
            if (j == 7 || j == 15) cout << endl;
        }
        // Extend W
        for (int j = 16; j < 80; j++)
            W[j] = leftRotate(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
        // Main loop
        for (int j = 0; j < 80; j++) {
            T = leftRotate(A, 5) + f(j) + E + W[j] + K[j / 20];
            E = D;
            D = C;
            C = leftRotate(B, 30);
            B = A;
            A = T;
        }
        A += 0x67452301;
        B += 0xefcdab89;
        C += 0x98badcfe;
        D += 0x10325476;
        E += 0xc3d2e1f0;
    }
}

int main() {
    string input;
    cout << "Please input message: ";
    getline(cin, input);
    cout << endl;
    sha1(input);
    cout << endl;
    cout << "Hex digest: " << setw(8) << setfill('0') << hex
         << A << " " << B << " " << C << " " << D << " " << E << endl;
}
