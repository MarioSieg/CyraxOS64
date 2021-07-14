#include "Isr.h"
#include "Idt.h"
#include "../Drivers/Screen.h"

void IsrInstallation() {
    SetIdtGate(0,  &InterruptRoutine0);
    SetIdtGate(1,  &InterruptRoutine1);
    SetIdtGate(2,  &InterruptRoutine2);
    SetIdtGate(3,  &InterruptRoutine3);
    SetIdtGate(4,  &InterruptRoutine4);
    SetIdtGate(5,  &InterruptRoutine5);
    SetIdtGate(6,  &InterruptRoutine6);
    SetIdtGate(7,  &InterruptRoutine7);
    SetIdtGate(8,  &InterruptRoutine8);
    SetIdtGate(9,  &InterruptRoutine9);
    SetIdtGate(10, &InterruptRoutine10);
    SetIdtGate(11, &InterruptRoutine11);
    SetIdtGate(12, &InterruptRoutine12);
    SetIdtGate(13, &InterruptRoutine13);
    SetIdtGate(14, &InterruptRoutine14);
    SetIdtGate(15, &InterruptRoutine15);
    SetIdtGate(16, &InterruptRoutine16);
    SetIdtGate(17, &InterruptRoutine17);
    SetIdtGate(18, &InterruptRoutine18);
    SetIdtGate(19, &InterruptRoutine19);
    SetIdtGate(20, &InterruptRoutine20);
    SetIdtGate(21, &InterruptRoutine21);
    SetIdtGate(22, &InterruptRoutine22);
    SetIdtGate(23, &InterruptRoutine23);
    SetIdtGate(24, &InterruptRoutine24);
    SetIdtGate(25, &InterruptRoutine25);
    SetIdtGate(26, &InterruptRoutine26);
    SetIdtGate(27, &InterruptRoutine27);
    SetIdtGate(28, &InterruptRoutine28);
    SetIdtGate(29, &InterruptRoutine29);
    SetIdtGate(30, &InterruptRoutine30);
    SetIdtGate(31, &InterruptRoutine31);
    LoadIdt();
}

void IsrHandler(struct IsrRegisterAggregate _regs) {
    char buf[64];
    FmtI64(_regs.InterruptNumber, buf);
    ScreenPrint(buf);
    ScreenPrint(" ");
    ScreenPrint(INTERRUPT_MESSAGES[_regs.InterruptNumber]);
    NewLine();
}

const char* const INTERRUPT_MESSAGES[32] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
