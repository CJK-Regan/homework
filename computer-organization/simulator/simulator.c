#include <cstdio>
#include <cstring>
#include <cstdlib>

#define NUMMEMORY 65536
#define NUMREGS 8
#define MAXLINELENGTH 1000

struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} state;

int count;

void printState() {
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", state.pc);
    printf("\tmemory:\n"); 
    for (int i = 0; i < state.numMemory; i++)
        printf("\t\tmem[ %d ] %d\n", i, state.mem[i]);
    printf("\tregisters:\n");
    for (int i = 0; i < NUMREGS; i++)
        printf("\t\treg[ %d ] %d\n", i, state.reg[i]);
    printf("end state\n");
}

int offsetNum(int num) {
    if (num & (1 << 15))
        num -= (1 << 16);
    return num;
}

void execute(int op) {
    printState();
    state.pc++;
    count++;
    switch (op >> 22) {
        case 0:
            state.reg[op % 8] = state.reg[(op >> 16) % 8] + state.reg[(op >> 19) % 8];
            break;
        case 1:
            state.reg[op % 8] = ~(state.reg[(op >> 16) % 8] & state.reg[(op >> 19) % 8]);
            break;
        case 2:
            state.reg[(op >> 16) % 8] = state.mem[state.reg[(op >> 19) % 8] + offsetNum(op % (1 << 16))];
            break;
        case 3:
            state.mem[state.reg[(op >> 19) % 8] + offsetNum(op % (1 << 16))] = state.reg[(op >> 16) % 8];
            break;
        case 4:
            if (state.reg[(op >> 19) % 8] == state.reg[(op >> 16) % 8])
                state.pc = state.pc + offsetNum(op % (1 << 16));
            break;
        case 5:
            state.reg[(op >> 16) % 8] = state.pc;
            state.pc = state.reg[(op >> 19) % 8];
            break;
        case 6:
            printf("machine halted\ntotal of %d instructions executed\nfinal state of machine:\n", count);
            printState();
            exit(0);
    }
}

int main(int argc, char *argv[]) {
    char line[MAXLINELENGTH];
    FILE *filePtr;

    if (argc != 2) {
        printf("Usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL) {
        printf("Error: Can't open file %s", argv[1]);
        exit(1);
    }

    while (fgets(line, MAXLINELENGTH, filePtr) != NULL) {
        if (sscanf(line, "%d", state.mem + state.numMemory) != 1) {
            printf("Error: Fail in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
        state.numMemory++;
    }

    while (true)
        execute(state.mem[state.pc]);

    printState();
}
