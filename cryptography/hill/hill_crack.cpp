#include <iostream>
#include <string>
using namespace std;

string plain, cypher;
int matrix[2][4];

int mod(int a, int b) {
    int c = a % b;
    if (c < 0) c += b;
    return c;
}

int reverse(int delta) {
    for (int i = 3; i < 26; i++)
        if (i * delta % 26 == 1)
            return i;
    return 0;
}

void toMatrix(string s, int n) {
    int i = 0;
    for (int j = 0; j < s.size(); j++)
        if (isalpha(s[j])) {
            matrix[n][i++] = toupper(s[j]) - 'A';
            if (i == 4)
                break;
        }
    swap(matrix[n][1], matrix[n][2]);
}

int main() {
    cout << "Please input plain text: ";
    getline(cin, plain);
    toMatrix(plain, 0);

    cout << "Please input cypher text: ";
    getline(cin, cypher);
    toMatrix(cypher, 1);

    int d = mod(matrix[0][0] * matrix[0][3] - matrix[0][1] * matrix[0][2], 26);
    int reverseDelta = reverse(d);
    swap(matrix[0][0], matrix[0][3]);
    matrix[0][0] = mod(matrix[0][0] * reverseDelta, 26);
    matrix[0][1] = mod(-matrix[0][1] * reverseDelta, 26);
    matrix[0][2] = mod(-matrix[0][2] * reverseDelta, 26);
    matrix[0][3] = mod(matrix[0][3] * reverseDelta, 26);

    cout << mod(matrix[1][0] * matrix[0][0] + matrix[1][1] * matrix[0][2], 26) << " " << mod(matrix[1][0] * matrix[0][1] + matrix[1][1] * matrix[0][3], 26) << endl;
    cout << mod(matrix[1][2] * matrix[0][0] + matrix[1][3] * matrix[0][2], 26) << " " << mod(matrix[1][2] * matrix[0][1] + matrix[1][3] * matrix[0][2], 26) << endl;
}
