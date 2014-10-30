#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <map>

#define MAXLINELENGTH 1000

using namespace std;

FILE *inFile, *outFile;

map<string, int> labels;
vector<string *> lines;
vector<string> outputDec;
vector<string> outputHex;

string *line;
char tmp[MAXLINELENGTH];
char label[10], opcode[10], arg0[5], arg1[5], arg2[5];

void parse() {
    int addressNum = 0;
    while (fgets(tmp, MAXLINELENGTH, inFile)) {
        if (strchr(tmp, '\n') == NULL) {
            cout<<"Error: Line exceeds maxlength."<<endl;
            exit(1);
        }

        line = new string[5];
        char *p = tmp;

        if (sscanf(p, "%[^\t\n ]", label)) {
            p += strlen(label);
            line[0] = label;
            if (labels.find(line[0]) != labels.end()) {
                cout<<"Error: Duplicate labels."<<endl;
                exit(1);
            }
            labels.insert(pair<string, int>(line[0], addressNum));
        }
        else
            line[0] = "";

        int items = sscanf(p, "%s%s%s%s", opcode, arg0, arg1, arg2);
        line[1] = opcode;
        line[2] = items >= 2 ? arg0 : "";
        line[3] = items >= 3 ? arg1 : "";
        line[4] = items >= 4 ? arg2 : "";

        lines.push_back(line);
        addressNum++;
    }
}

bool isLabel(string x) {
    if (!(x[0] >= '0' && x[0] <= '9' || x[0] == '-')) {
        if (labels.find(x) == labels.end()) {
            cout<<"Error: Undefined labels."<<endl;
            exit(1);
        }
        return true;
    }
    return false;
}
string numberToString(int n) {
    if (!n)
        return "0";
    string x = "";
    string sign = n < 0 ? "-" : "";
    if (n < 0)
        n = -n;
    while (n) {
        x.insert(0, 1, '0' + n % 10);
        n /= 10;
    }
    return sign + x;
}
int stringToNumber(string x) {
    int n = 0;
    if (x[0] == '-') {
        for (int i = 1; i < x.size(); i++)
            n = 10 * n + x[i] -'0';
        return -n;
    }
    else {
        for (int i = 0; i < x.size(); i++)
            n = 10 * n + x[i] - '0';
        return n;
    }
}
string toBinary(string x, int width) {
    int n = stringToNumber(x);
    string binary = "";
    if (n >= 0) {
        for (int i = 0; i < width - 1; i++) {
            binary.insert(0, 1, n % 2 ? '1' : '0');
            n /= 2;
        }
        binary = "0" + binary;
    }
    else {
        n = - n -1;
        for (int i = 0; i < width - 1; i++) {
            binary.insert(0, 1, n % 2 ? '0' : '1');
            n /= 2;
        }
        binary = "1" + binary;
    }
    if (n) {
        cout<<"Error: Overflow."<<endl;
        exit(1);
    }
    return binary;
}
string toField(string x) {
    int n = stringToNumber(x);
    string field = "";
    for (int i = 0; i < 3; i++) {
        field.insert(0, 1, n % 2 ? '1' : '0');
        n /= 2;
    }
    return field;
}
string toOpcode(string x) {
    if (x == "add")
        return "000";
    if (x == "nand")
        return "001";
    if (x == "lw")
        return "010";
    if (x == "sw")
        return "011";
    if (x == "beq")
        return "100";
    if (x == "jalr")
        return "101";
    if (x == "halt")
        return "110";
    if (x == "noop")
        return "111";
    cout<<"Error: Unrecognized opcodes."<<endl;
    exit(1);
}
int binaryToNumber(string x, bool sign) {
    if (sign) {
        if (x[0] == '0')
            return binaryToNumber(x, false);
        else {
            for (int i = 0; i < x.size(); i++)
                x[i] = x[i] == '0' ? '1' : '0';
            return - binaryToNumber(x, false) - 1;
        }
    }

    int n = 0;
    for (int i = 0; i < x.size(); i++)
        n = 2 * n + x[i] - '0';
    return n;
}
string toDec(string x) {
    return numberToString(binaryToNumber(x, true));
}
string toHex(string x) {
    string hex = "";
    for(int i = 0; i < 32; i += 4) {
        int n = 0;
        for (int j = i; j < i + 4; j++)
            n = 2 * n + x[j] - '0';
        if (n == 0 && hex == "")
            continue;
        else if (n % 16 >= 10)
            hex += 'a' + n % 16 - 10;
        else
            hex += '0' + n % 16;
    }
    return hex;
}

void transfer() {
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 2; j < 4; j++)
            if (lines[i][j] != "" && isLabel(lines[i][j]))
                lines[i][j] = numberToString(labels[lines[i][j]]);

        if (lines[i][4] != "" && isLabel(lines[i][4])) {
            if (lines[i][1] == "beq")
                lines[i][4] = numberToString(labels[lines[i][4]] - i - 1);
            else
                lines[i][4] = numberToString(labels[lines[i][4]]);
        }

        string binary = "";
        if (lines[i][1] == ".fill")
            binary = toBinary(lines[i][2], 32);
        else {
            binary += "0000000";
            if (lines[i][1] == "noop" || lines[i][1] == "halt")
                binary += toOpcode(lines[i][1]) + "0000000000000000000000";
            else if (lines[i][1] == "jalr")
                binary += toOpcode(lines[i][1]) + toField(lines[i][2]) + toField(lines[i][3]) + "0000000000000000";
            else if (lines[i][1] == "add" || lines[i][1] == "nand")
                binary +=
                    toOpcode(lines[i][1]) + toField(lines[i][2]) + toField(lines[i][3]) + "0000000000000" + toField(lines[i][4]);
            else
                binary += toOpcode(lines[i][1]) + toField(lines[i][2]) + toField(lines[i][3]) + toBinary(lines[i][4], 16);
        }

        outputDec.push_back(toDec(binary));
        outputHex.push_back(toHex(binary));
    }
}

void write() {
    for (int i = 0; i < lines.size(); i++) {
        fputs(outputDec[i].c_str(), outFile);
        fputs("\n", outFile);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
        exit(1);
    }

    inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Error in opening %s.\n", argv[1]);
        exit(1);
    }
    parse();
    fclose(inFile);

    transfer();

    outFile = fopen(argv[2], "w");
    write();
    fclose(outFile);

    printf("Success. Output to %s\n", argv[2]);
    exit(0);
}
