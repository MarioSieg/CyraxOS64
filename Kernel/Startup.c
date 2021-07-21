#include "../Drivers/Screen.h"
#include "Kernel.h"

void KernelEntry(void) {
    ScreenClear();
    ScreenPrint("Cyrax64 Microkernel (C) Copyright Mario Sieg \"pinsrq\" <mt3000@gmx.de>\n");
    ScreenPrint("64-bit long mode online!\n");
    ScreenPrint("Installing interrupts...\n");
    InstallInterrupts();
    ScreenPrint("Boot complete!\n");
    __asm__ volatile("int3");
}

void main(void) {
    KernelEntry();
    for(;;);
}