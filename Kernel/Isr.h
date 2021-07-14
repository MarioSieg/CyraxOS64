#ifndef ISR_H
#define ISR_H

/* Core structures for ISRs (Interrupt Service Routine) */

#include "Kernel.h"

struct __attribute__((packed)) IsrRegisterAggregate {
    /* Data segment selector */
    U32 Ds;
    /* GPRs pushed using pusha */
    U32 Edi, Esi, Ebp, Eep, Ebx, Edx, Ecx, Eax;

    /* Interrupt number and error code (if applicable) */
    U32 InterruptNumber, ErrorCode;

    /* Pushed by the CPU by default */
    U32 Eip, Cs, EFlags, UsrEsp, Ss;
};

extern void IsrInstallation(void);
extern void IsrHandler(struct IsrRegisterAggregate _regs);

extern void InterruptRoutine0(void);
extern void InterruptRoutine1(void);
extern void InterruptRoutine2(void);
extern void InterruptRoutine3(void);
extern void InterruptRoutine4(void);
extern void InterruptRoutine5(void);
extern void InterruptRoutine6(void);
extern void InterruptRoutine7(void);
extern void InterruptRoutine8(void);
extern void InterruptRoutine9(void);
extern void InterruptRoutine10(void);
extern void InterruptRoutine11(void);
extern void InterruptRoutine12(void);
extern void InterruptRoutine13(void);
extern void InterruptRoutine14(void);
extern void InterruptRoutine15(void);
extern void InterruptRoutine16(void);
extern void InterruptRoutine17(void);
extern void InterruptRoutine18(void);
extern void InterruptRoutine19(void);
extern void InterruptRoutine20(void);
extern void InterruptRoutine21(void);
extern void InterruptRoutine22(void);
extern void InterruptRoutine23(void);
extern void InterruptRoutine24(void);
extern void InterruptRoutine25(void);
extern void InterruptRoutine26(void);
extern void InterruptRoutine27(void);
extern void InterruptRoutine28(void);
extern void InterruptRoutine29(void);
extern void InterruptRoutine30(void);
extern void InterruptRoutine31(void);

extern const char* const INTERRUPT_MESSAGES[32];

#endif
