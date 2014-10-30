#ifndef MULTIPROCESS
#define MULTIPROCESS

#include "load.h"

#define MAX_PROCESS 65 // 1 kernel process and 64 user processes
#define KERNEL_SECTORS 10
#define CUSTOMER_SECTORS 2

typedef struct {
    short AX, BX, CX, DX, SI, DI, BP, SP, IP, CS, DS, ES, SS, Flags;
} RegisterImage;

typedef struct PCB PCB;
struct PCB {
    short id, status;
    RegisterImage regImg;
    PCB *nextPCB;
};

PCB PCB_list[MAX_PROCESS];
short curProcess;
unsigned short ax_save, bx_save, cx_save, dx_save, si_save, di_save, bp_save,
               sp_save, ip_save, cs_save, ds_save, es_save, ss_save, flags_save,
               ret_save;

void setTimer();
void blockInterrupt();
void enableInterrupt();

void createProcess(short programId) {
    blockInterrupt();
    short newProcessId;
    for (newProcessId = 1; newProcessId < MAX_PROCESS; newProcessId++)
        if (!PCB_list[newProcessId].status) {
            PCB_list[newProcessId].id = newProcessId;
            PCB_list[newProcessId].status = 1;
            PCB_list[newProcessId].regImg.CS = PCB_list[newProcessId].regImg.SS
                = 0x2000 + 0x200 * (newProcessId - 1);
            PCB_list[newProcessId].regImg.IP = 0;
            PCB_list[newProcessId].regImg.SP = 0x1fff;
            PCB_list[newProcessId].regImg.Flags = 0x200;
            break;
        }
    loadSector(KERNEL_SECTORS + programId * CUSTOMER_SECTORS,
            PCB_list[newProcessId].regImg.CS);
    PCB_list[newProcessId].nextPCB = PCB_list[curProcess].nextPCB;
    PCB_list[curProcess].nextPCB = &PCB_list[newProcessId];
    enableInterrupt();
}

void killProcess(short processId) {
    PCB_list[processId].status = 0;
}

void scheduler() {
    PCB_list[curProcess].regImg.AX = ax_save;
    PCB_list[curProcess].regImg.BX = bx_save;
    PCB_list[curProcess].regImg.CX = cx_save;
    PCB_list[curProcess].regImg.DX = dx_save;
    PCB_list[curProcess].regImg.SI = si_save;
    PCB_list[curProcess].regImg.DI = di_save;
    PCB_list[curProcess].regImg.BP = bp_save;
    PCB_list[curProcess].regImg.SP = sp_save;
    PCB_list[curProcess].regImg.IP = ip_save;
    PCB_list[curProcess].regImg.CS = cs_save;
    PCB_list[curProcess].regImg.DS = ds_save;
    PCB_list[curProcess].regImg.ES = es_save;
    PCB_list[curProcess].regImg.SS = ss_save;
    PCB_list[curProcess].regImg.Flags = flags_save;

    PCB *nextProcess = PCB_list[curProcess].nextPCB;
    while (!nextProcess -> status)
        nextProcess = nextProcess -> nextPCB;
    PCB_list[curProcess].nextPCB = nextProcess;
    curProcess = nextProcess -> id;

    ax_save = PCB_list[curProcess].regImg.AX;
    bx_save = PCB_list[curProcess].regImg.BX;
    cx_save = PCB_list[curProcess].regImg.CX;
    dx_save = PCB_list[curProcess].regImg.DX;
    si_save = PCB_list[curProcess].regImg.SI;
    di_save = PCB_list[curProcess].regImg.DI;
    bp_save = PCB_list[curProcess].regImg.BP;
    sp_save = PCB_list[curProcess].regImg.SP;
    ip_save = PCB_list[curProcess].regImg.IP;
    cs_save = PCB_list[curProcess].regImg.CS;
    ds_save = PCB_list[curProcess].regImg.DS;
    es_save = PCB_list[curProcess].regImg.ES;
    ss_save = PCB_list[curProcess].regImg.SS;
    flags_save = PCB_list[curProcess].regImg.Flags;
}

#endif
