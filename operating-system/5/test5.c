asm(".code16gcc");

#include "string.h"
#include "sysCalls.h"

void test() {
    ouch();
    putString("Please input the row number: ");
    char *input = getString();
    int row = parseString(0, (int)input);
    putString("Please input the col number: ");
    getString();
    int col = parseString(0, (int)input);
    putString("Please input a string: ");
    getString();
    upperCase(0, (int)input);
    putString("UpperCase: ");
    putString(input);
    putString("\n");
    lowerCase(0, (int)input);
    putString("lowerCase: ");
    putString(input);
    putString("\n");
    absPutString(row, col, 0, (int)input);
}
