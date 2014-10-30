asm(".code16gcc");

#include "string.h"
#include "clib.h"
#include "sysInt.h"

int status = 1;

void parseCommand(char *command) {
    if (strcmp(command, "help") == 0) {
        putString("command list:\n");
        putString("help  -- display available command\n");
        putString("clear -- clear the screen\n");
        putString("exit  -- halt the machine\n");
        putString("date  -- get date\n");
        putString("time  -- get time\n");
        putString("asc   -- load the custom asc program\n");
        putString("test  -- test program of system calls\n");
    }
    else if (strcmp(command, "clear") == 0)
        clear();
    else if (strcmp(command, "date") == 0) {
        putString(getDate());
        putString("\n");
    }
    else if (strcmp(command, "time") == 0) {
        putString(getTime());
        putString("\n");
    }
    else if (strcmp(command, "asc") == 0)
        loadSector(22, 2);
    else if (strcmp(command, "test") == 0)
        loadSector(24, 3);
    else if (strcmp(command, "exit") == 0)
        status = 0;
}

void cmain() {
    setSysInt();
    putString("Hello, world!\n");
    while (status) {
        putString("$ > ");
        parseCommand(getString());
    }
    putString("Bye\n");
}
