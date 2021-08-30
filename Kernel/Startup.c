#include "Kernel.h"
#include "Interrupt.h"
#include "StdOut.h"

void KernelStart(void) {
    Clear();
    Print("Cyrax64 Microkernel (C) Copyright Mario Sieg \"pinsrq\" <mt3000@gmx.de>\n");
    Print("64-bit long mode online!\n");
    Print("Installing interrupts...\n");
    InstallInterrupts();
    Print("Boot complete!\n");
    __asm__ volatile("int3");
}

void KernelSetup(void) {
    struct Stream stdout;
    U8 buf[4096];
    InitStdOut(&stdout, buf, sizeof(buf));
    
    KernelStart();
    FlushStdOut();
}

void main(void) {
    KernelSetup();
    for(;;);
}
