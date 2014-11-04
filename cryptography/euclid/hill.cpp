#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int key[2][2];
int inverse[2][2];
int s, t;

int mod(int a, int b) {
    int c = a % b;
    if (c < 0) c += b;
    return c;
}

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

int inversed(int delta) {
    int r = gcdEx(26, delta);
    if (r != 1) return 0;
    else return mod(t, 26);
}

bool keyIsValid() {
	int delta = mod(key[0][0] * key[1][1] - key[0][1] * key[1][0], 26);
    int inverseDelta = inversed(delta);
    if (inverseDelta == 0) return false;
    inverse[0][0] = mod(key[1][1] * inverseDelta, 26);
    inverse[0][1] = mod(-key[0][1] * inverseDelta, 26);
    inverse[1][0] = mod(-key[1][0] * inverseDelta, 26);
    inverse[1][1] = mod(key[0][0] * inverseDelta, 26);
    return true;
}

string encode(char a, char b){
	int x = a - 'A', y = b - 'A';
	string output = "";
	output += 'A' + mod(x * key[0][0] + y * key[0][1], 26);
	output += 'A' + mod(x * key[1][0] + y * key[1][1], 26);
	return output;
}

string decode(char a, char b){
	int x = a - 'A', y = b - 'A';
	string output = "";
	output += 'A' + mod(x * inverse[0][0] + y * inverse[0][1], 26);
	output += 'A' + mod(x * inverse[1][0] + y * inverse[1][1], 26);
	return output;
}

int main() {
	while (true){
		cout << "Input secret key (2*2): " << endl;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				cin >> key[i][j];
		if (keyIsValid())
			break;
		cout << "Invalid key." << endl;
	}
	string op;
	while (true){
		cout << "encode/decode/exit: ";
		cin >> op;
		if (op == "encode") {
			string input, output = "";
			getchar();
			getline(cin, input);
			int i = 0;
			while (i < input.size()){
				char a, b;
				a = toupper(input[i]);
				do { i++; } while (i < input.size() && !isalpha(input[i]));
				b = toupper(input[i]);
				output += encode(a, b);
				do { i++; } while (i < input.size() && !isalpha(input[i]));
				if (i == input.size()) break;
			}
			for (i = 0; i < input.size(); i++)
				if (input[i] == ' ')
					output.insert(i, 1, ' ');
			cout << output << endl;
		}
		else if (op == "decode"){
			string input, output = "";
			getchar();
			getline(cin, input);
			int i = 0;
			while (i < input.size()){
				char a, b;
				a = toupper(input[i]);
				do { i++; } while (i < input.size() && !isalpha(input[i]));
				b = toupper(input[i]);
				output += decode(a, b);
				do { i++; } while (i < input.size() && !isalpha(input[i]));
				if (i == input.size()) break;
			}
			for (i = 0; i < input.size(); i++)
				if (input[i] == ' ')
					output.insert(i, 1, ' ');
			cout << output << endl;
		}
		else if (op == "exit") break;
	}
}
