#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMMEMORY 65536
#define NUMREGS 8
#define MAXLINELENGTH 1000

struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int memoryAddress;
    int memoryData;
    int instrReg;
    int aluOperand;
    int aluResult;
    int numMemory;
} state;

void printState(char *stateName) {
    static int cycle = 0;
    int i;
    printf("\n@@@\nstate %s (cycle %d)\n", stateName, cycle++);
    printf("\tpc %d\n", state.pc);
    printf("\tmemory:\n");
    for (i = 0; i < state.numMemory; i++)
        printf("\t\tmem[ %d ] %d\n", i, state.mem[i]);
    printf("\tregisters:\n");
    for (i = 0; i < NUMREGS; i++)
        printf("\t\treg[ %d ] %d\n", i, state.reg[i]);
    printf("\tinternal registers:\n");
    printf("\t\tmemoryAddress %d\n", state.memoryAddress);
    printf("\t\tmemoryData %d\n", state.memoryData);
    printf("\t\tinstrReg %d\n", state.instrReg);
    printf("\t\taluOperand %d\n", state.aluOperand);
    printf("\t\taluResult %d\n", state.aluResult);
}

int memoryAccess(int readFlag) {
    static int lastAddress = -1;
    static int lastReadFlag = 0;
    static int lastData = 0;
    static int delay = 0;

    if (state.memoryAddress < 0 ||
            state.memoryAddress >= NUMMEMORY) {
        printf("memory address out of range\n");
        exit(1);
    }

    if ((state.memoryAddress != lastAddress) ||
            (readFlag != lastReadFlag) ||
            (readFlag == 0 && lastData != state.memoryData)) {
        delay = state.memoryAddress % 3;
        lastAddress = state.memoryAddress;
        lastReadFlag = readFlag;
        lastData = state.memoryData;
    }

    if (delay == 0) {
        if (readFlag)
            state.memoryData = state.mem[state.memoryAddress];
        else
            state.mem[state.memoryAddress] = state.memoryData;
        return(1);
    }
    else {
        delay--;
        return(0);
    }
}

int convertNum(int num) { 
    if (num & (1 << 15))
        num -= (1 << 16);
    return(num);
}

void run() {
    int bus;
fetch:
    printState("fetch");
    bus = state.pc;
    state.memoryAddress = bus;
    state.pc++;
fetch1:
    printState("fetch1");
    if (!memoryAccess(1))
        goto fetch1;
fetch2:
    printState("fetch2");
    bus = state.memoryData;
    state.instrReg = bus;
    if (state.instrReg >> 22 == 0)
        goto add;
    if (state.instrReg >> 22 == 1)
        goto nand;
    if (state.instrReg >> 22 == 2)
        goto lw;
    if (state.instrReg >> 22 == 3)
        goto sw;
    if (state.instrReg >> 22 == 4)
        goto beq;
    if (state.instrReg >> 22 == 5)
        goto jalr;
    if (state.instrReg >> 22 == 6)
        goto halt;
    if (state.instrReg >> 22 == 7)
        goto fetch;
add:
    printState("add");
    bus = state.reg[(state.instrReg >> 19) % 8];
    state.aluOperand = bus;
add1:
    printState("add1");
    bus = state.reg[(state.instrReg >> 16) % 8];
    state.aluResult = state.aluOperand + bus;
add2:
    printState("add2");
    bus = state.aluResult;
    state.reg[state.instrReg % 8] = bus;
    goto fetch;
nand:
    printState("nand");
    bus = state.reg[(state.instrReg >> 19) % 8];
    state.aluOperand = bus;
nand1:
    printState("nand1");
    bus = state.reg[(state.instrReg >> 16) % 8];
    state.aluResult = ~(state.aluOperand & bus);
nand2:
    printState("nand2");
    bus = state.aluResult;
    state.reg[state.instrReg % 8] = bus;
    goto fetch;
lw:
    printState("lw");
    bus = state.reg[(state.instrReg >> 19) % 8];
    state.aluOperand = bus;
lw1:
    printState("lw1");
    bus = convertNum(state.instrReg % (1 << 16));
    state.aluResult = state.aluOperand + bus;
lw2:
    printState("lw2");
    bus = state.aluResult;
    state.memoryAddress = bus;
lw3:
    printState("lw3");
    if (!memoryAccess(1))
        goto lw3;
lw4:
    printState("lw4");
    bus = state.memoryData;
    state.reg[(state.instrReg >> 16) % 8] = bus;
    goto fetch;
sw:
    printState("sw");
    bus = state.reg[(state.instrReg >> 19) % 8];
    state.aluOperand = bus;
sw1:
    printState("sw1");
    bus = convertNum(state.instrReg % (1 << 16));
    state.aluResult = state.aluOperand + bus;
sw2:
    printState("sw2");
    bus = state.aluResult;
    state.memoryAddress = bus;
sw3:
    printState("sw3");
    bus = state.reg[(state.instrReg >> 16) % 8];
    state.memoryData = bus;
sw4:
    printState("sw4");
    if (!memoryAccess(0))
        goto sw4;
    goto fetch;
beq:
    printState("beq");
    bus = state.reg[(state.instrReg >> 19) % 8];
    state.aluOperand = bus;
beq1:
    printState("beq1");
    bus = state.reg[(state.instrReg >> 16) % 8];
    state.aluResult = state.aluOperand - bus;
beq2:
    printState("beq2");
    if (state.aluResult == 0) {
        bus = convertNum(state.instrReg % (1 << 16));
        state.aluOperand = bus;
    }
    else
        goto fetch;
beq3:
    printState("beq3");
    bus = state.pc;
    state.aluResult = state.aluOperand + bus;
beq4:
    printState("beq4");
    bus = state.aluResult;
    state.pc = bus;
    goto fetch;
jalr:
    printState("jalr");
    bus = state.pc;
    state.reg[(state.instrReg >> 16) % 8] = bus;
jalr1:
    printState("jalr1");
    bus = state.reg[(state.instrReg >> 19) % 8];
    state.pc = bus;
    goto fetch;
halt:
    printState("halt");
    return;
}

int main(int argc, char *argv[]) {
    char line[MAXLINELENGTH];
    FILE *filePtr;

    if (argc != 2) {
        printf("error: usage: %s <machine-code file>n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL) {
        printf("error: can't open file %s\n", argv[1]);
        perror("fopen");
        exit(1);
    }

    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL;
            state.numMemory++) {
        if (sscanf(line, "%d", state.mem + state.numMemory) != 1) {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    printf("\n");

    run();
}
