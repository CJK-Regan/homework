asm(".code16gcc");

#include "clib.h"

int status = 1;

void parseCommand(char *command) {
    if (strcmp(command, "help") == 0) {
        putString("command list:\n");
        putString("help  -- display available command\n");
        putString("clear -- clear the screen\n");
        putString("exit  -- halt the machine\n");
        putString("date  -- get date\n");
        putString("time  -- get time\n");
        putString("ball  -- load the custom ball program\n");
        putString("asc   -- load the custom asc program\n");
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
    else if (strcmp(command, "ball") == 0) {
        clear();
        loadSector(14);
        clear();
    }
    else if (strcmp(command, "asc") == 0)
        loadSector(12);
    else if (strcmp(command, "exit") == 0)
        status = 0;
}

void cmain() {
    putString("Hello, world!\n");
    while (status) {
        putString("$ > ");
        parseCommand(getString());
    }
    putString("Bye\n");
}
