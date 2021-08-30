#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "Foundation.h"

enum IdtAttrib {
    IdtAttrib_Ring0 = 0 << 5,
    IdtAttrib_Ring1 = 1 << 5,
    IdtAttrib_Ring2 = 2 << 5,
    IdtAttrib_Ring3 = 3 << 5,
    IdtAttrib_Present = 1 << 7,
    IdtAttrib_TypeInterrupt = 0xE, // 1110
    IdtAttrib_TypeTrap = 0xF // 1111
};

struct __attribute__((packed)) IdtGate {
    U16 Offset0;
    U16 Selector;
    U8 StackTableOffset;
    U8 TypeAttrib;
    U16 Offset1;
    U32 Offset3;
    U32 Zero;
};

_Static_assert(sizeof(struct IdtGate) == 16, "Invalid record size!");

struct __attribute__((packed)) IdtRegisterPtr {
    U16 Limit;
    U64 BaseOffset;
};

_Static_assert(sizeof(struct IdtRegisterPtr) == 10, "Invalid record size!");

#define IDT_ENTRIES 256

extern struct IdtGate InterruptDescriptorTable[IDT_ENTRIES];
extern struct IdtRegisterPtr IdtPointer;

extern void SetIdtGate(U64 _idx, void(*_routine)(void));
extern void LoadIdt(void);
extern void InstallInterrupts(void);

extern void InterruptRoutine0();
extern void InterruptRoutine1();
extern void InterruptRoutine2();
extern void InterruptRoutine3();
extern void InterruptRoutine4();
extern void InterruptRoutine5();
extern void InterruptRoutine6();
extern void InterruptRoutine7();
extern void InterruptRoutine8();
extern void InterruptRoutine9();
extern void InterruptRoutine10();
extern void InterruptRoutine11();
extern void InterruptRoutine12();
extern void InterruptRoutine13();
extern void InterruptRoutine14();
extern void InterruptRoutine15();
extern void InterruptRoutine16();
extern void InterruptRoutine17();
extern void InterruptRoutine18();
extern void InterruptRoutine19();
extern void InterruptRoutine20();
extern void InterruptRoutine21();
extern void InterruptRoutine22();
extern void InterruptRoutine23();
extern void InterruptRoutine24();
extern void InterruptRoutine25();
extern void InterruptRoutine26();
extern void InterruptRoutine27();
extern void InterruptRoutine28();
extern void InterruptRoutine29();
extern void InterruptRoutine30();
extern void InterruptRoutine31();

#define KERNEL_CS 0x08

extern const char* const INTERRUPT_NAMES[IDT_ENTRIES];

#endif
