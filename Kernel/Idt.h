#ifndef IDT_H
#define IDT_H

/* Core structures for the IDT (interrupt descriptor table) */

#include "Kernel.h"

#define KERNEL_CS 0x08

struct __attribute__((packed))  IdtGate {
    U16 HandlerAddressLo;
    U16 KernelSegment;
    U8 ZeroPadding;
    U8 Flags;
    U16 HandlerAddressHi;
};

struct __attribute__((packed)) IdtRegister {
    U16 Limit;
    UIntPtr32 Base;
};

#define IDT_ENTRY_COUNT 256

extern struct IdtGate IDT[IDT_ENTRY_COUNT];
extern struct IdtRegister IdtRegister;

extern void SetIdtGate(U32 _i, void(*_handler)(void));
extern void LoadIdt(void);

#endif
