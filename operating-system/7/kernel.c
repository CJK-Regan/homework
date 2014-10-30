asm(".code16gcc");

#include "string.h"
#include "multiprocess.h"

void clear();

void parseCommand(char *command) {
    if (strcmp(command, "exit") == 0) {
        putString("Bye!");
        killProcess(0);
    }
    else if (strcmp(command, "clear") == 0) {
        clear();
        putString("$ > ");
    }
    else if (strcmp(command, "help") == 0) {
        absPutString("help  -- display available commands", 2, 0);
        absPutString("clear -- clear the screen", 3, 0);
        absPutString("exit  -- halt the kernel process", 4, 0);
        absPutString("test  -- test fork, wait and exit", 5, 0);
        absPutString("bar   -- create a process for user program 'bar'", 6, 0);
    }
    else if (strcmp(command, "test") == 0)
        createProcess(1);
    else if (strcmp(command, "bar") == 0)
        createProcess(2);
}

void cmain() {
    PCB_list[0].id = 0;
    PCB_list[0].status = STATUS_READY;
    PCB_list[0].nextPCB = &PCB_list[0];
    curProcess = 0;
    setTimer();
    setSysInt();
    putString("$ > ");
    while (1)
        parseCommand(getString());
}
