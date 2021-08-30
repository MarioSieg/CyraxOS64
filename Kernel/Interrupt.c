#include "Interrupt.h"
#include "Format.h"

struct IdtGate InterruptDescriptorTable[IDT_ENTRIES];
struct IdtRegisterPtr IdtPointer;

void SetIdtGate(const U64 _idx, void(*const _routine)(void)) {
    struct IdtGate* const gate = &InterruptDescriptorTable[_idx];
    const U64 intptr = (U64)_routine;
    gate->Offset0 = intptr & 0xFFFF;
    gate->Offset1 = (intptr >> 16) & 0xFFFF;
    gate->Offset1 = (intptr >> 32) & 0xFFFFFFFF;
    gate->Selector = KERNEL_CS;
    gate->StackTableOffset = 0;
    gate->TypeAttrib = IdtAttrib_Present | IdtAttrib_Ring0 | IdtAttrib_TypeInterrupt;
    gate->Zero = 0;
}

void LoadIdt(void) {
    IdtPointer.BaseOffset = (U64)&InterruptDescriptorTable;
    IdtPointer.Limit = IDT_ENTRIES * sizeof(struct IdtRegisterPtr) - 1;
    __asm__ volatile("lidtq (%0)" : : "r"(&IdtPointer));
}

void InstallInterrupts(void) {
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

const char* const INTERRUPT_NAMES[IDT_ENTRIES] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "Device not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault Exception",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "Floating Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point Exception",
    "Virtualization Exception",
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
    "Security Exception"
};

void InterruptHandler(const U64 _id, void* const _rsp) {
    (void)_rsp;
    Print(INTERRUPT_NAMES[_id]);
    
}
