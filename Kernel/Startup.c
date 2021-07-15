#include "../Drivers/Screen.h"
#include "Isr.h"

void KernelEntry(void) {
    ScreenClear();
    ScreenPrint("Cyrax64 Microkernel (C) Copyright Mario Sieg \"pinsrq\" <mt3000@gmx.de>\n");
    ScreenPrint("64-bit long mode online!\n");
    ScreenPrint("Installing interrupt service routines...\n");
}

void main(void) {
    KernelEntry();
    for(;;);
}