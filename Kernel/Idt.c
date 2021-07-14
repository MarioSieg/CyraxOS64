#include "Idt.h"

struct IdtGate IDT[IDT_ENTRY_COUNT];
struct IdtRegister IdtRegister;

void SetIdtGate(const U32 _i, void(*const _handler)(void)) {
    const UIntPtr32 ptr = (UIntPtr32)(UIntPtr64)_handler;
    struct IdtGate* const entry = IDT + _i;
    entry->HandlerAddressLo = ptr & 0xFFFF;
    entry->KernelSegment = KERNEL_CS;
    entry->ZeroPadding = 0;
    entry->Flags = 0x8E;
    entry->HandlerAddressHi = (ptr >> 16) & 0xFFFF;
}

void LoadIdt(void) {
    IdtRegister.Base = (UIntPtr32)(UIntPtr64)&IDT;
    IdtRegister.Limit = IDT_ENTRY_COUNT * sizeof(struct IdtGate) - 1;
    asm volatile("lidtq (%0)" :: "r"(&IdtRegister));
}
