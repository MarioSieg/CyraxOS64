#ifndef REGISTER_H
#define REGISTER_H

#include "Foundation.h"

/* Represents a 64-bit GPR such as %rax or %rsi. */
union Register64 {
    U64 R64;
    U8 Raw[sizeof(U64)];
    struct {
        U32 R32;
        union {
            U16 Reverved;
            U16 R16;
            struct {
                U8 R8Hi;
                U8 R8Lo;
            };
        };
   };
};

_Static_assert(sizeof(union Register64) == 8, "Invalid record size!");

/* Represents a 128-bit SSE vector register such as %xmm0 or %xmm3. */
union Register128 {
   struct {
        union {
            U64 U;
            F64 F;
        } Lo, Hi;
   };
   U8 Raw[sizeof(U64) << 1];
};

_Static_assert(sizeof(union Register128) == 16, "Invalid record size!");

/* Contains all register IDs except for %eip! */
enum Register {
    REGISTER_RAX = 0,
    REGISTER_RBX,
    REGISTER_RCX,
    REGISTER_RDX,
    REGISTER_RSI,
    REGISTER_RDI,
    REGISTER_RSP,
    REGISTER_RBP,
    REGISTER_R8,
    REGISTER_R9,
    REGISTER_R10,
    REGISTER_R11,
    REGISTER_R12,
    REGISTER_R13,
    REGISTER_R14,
    REGISTER_R15,

    REGISTER_CR0,
    REGISTER_CR2,
    REGISTER_CR3,
    REGISTER_CR4,

    REGISTER_GPR_COUNT,

    REGISTER_XMM0,
    REGISTER_XMM1,
    REGISTER_XMM2,
    REGISTER_XMM3,
    REGISTER_XMM4,
    REGISTER_XMM5,
    REGISTER_XMM6,
    REGISTER_XMM7,
    REGISTER_XMM8,
    REGISTER_XMM9,
    REGISTER_XMM10,
    REGISTER_XMM11,
    REGISTER_XMM12,
    REGISTER_XMM13,
    REGISTER_XMM14,
    REGISTER_XMM15,
    REGISTER_COUNT
};

/* Contains the names of all registers. */
extern const char* const REG_NAMES[REGISTER_COUNT];

/* Contains bit masks for all registers except for %eip! */
#define REGISTER_MASK_RAX   UINT64_C(1) << REGISTER_RAX
#define REGISTER_MASK_RBX   UINT64_C(1) << REGISTER_RBX
#define REGISTER_MASK_RCX   UINT64_C(1) << REGISTER_RCX
#define REGISTER_MASK_RDX   UINT64_C(1) << REGISTER_RDX
#define REGISTER_MASK_RSI   UINT64_C(1) << REGISTER_RSI
#define REGISTER_MASK_RDI   UINT64_C(1) << REGISTER_RDI
#define REGISTER_MASK_RSP   UINT64_C(1) << REGISTER_RSP
#define REGISTER_MASK_RBP   UINT64_C(1) << REGISTER_RBP
#define REGISTER_MASK_R8    UINT64_C(1) << REGISTER_R8 
#define REGISTER_MASK_R9    UINT64_C(1) << REGISTER_R9 
#define REGISTER_MASK_R10   UINT64_C(1) << REGISTER_R10
#define REGISTER_MASK_R11   UINT64_C(1) << REGISTER_R11
#define REGISTER_MASK_R12   UINT64_C(1) << REGISTER_R12
#define REGISTER_MASK_R13   UINT64_C(1) << REGISTER_R13
#define REGISTER_MASK_R14   UINT64_C(1) << REGISTER_R14
#define REGISTER_MASK_R15   UINT64_C(1) << REGISTER_R15

#define REGISTER_MASK_CR0   UINT64_C(1) << REGISTER_CR0
#define REGISTER_MASK_CR2   UINT64_C(1) << REGISTER_CR2
#define REGISTER_MASK_CR3   UINT64_C(1) << REGISTER_CR3
#define REGISTER_MASK_CR4   UINT64_C(1) << REGISTER_CR4

#define REGISTER_MASK_XMM0  UINT64_C(1) << REGISTER_XMM0
#define REGISTER_MASK_XMM1  UINT64_C(1) << REGISTER_XMM1
#define REGISTER_MASK_XMM2  UINT64_C(1) << REGISTER_XMM2
#define REGISTER_MASK_XMM3  UINT64_C(1) << REGISTER_XMM3
#define REGISTER_MASK_XMM4  UINT64_C(1) << REGISTER_XMM4
#define REGISTER_MASK_XMM5  UINT64_C(1) << REGISTER_XMM5
#define REGISTER_MASK_XMM6  UINT64_C(1) << REGISTER_XMM6
#define REGISTER_MASK_XMM7  UINT64_C(1) << REGISTER_XMM7
#define REGISTER_MASK_XMM8  UINT64_C(1) << REGISTER_XMM8
#define REGISTER_MASK_XMM9  UINT64_C(1) << REGISTER_XMM9
#define REGISTER_MASK_XMM10 UINT64_C(1) << REGISTER_XMM10
#define REGISTER_MASK_XMM11 UINT64_C(1) << REGISTER_XMM11
#define REGISTER_MASK_XMM12 UINT64_C(1) << REGISTER_XMM12
#define REGISTER_MASK_XMM13 UINT64_C(1) << REGISTER_XMM13
#define REGISTER_MASK_XMM14 UINT64_C(1) << REGISTER_XMM14
#define REGISTER_MASK_XMM15 UINT64_C(1) << REGISTER_XMM15

/* Contains storage for all registers. */
typedef union Register64 Register64AggregateSet[REGISTER_GPR_COUNT];
typedef union Register128 Register128AggregateSet[REGISTER_COUNT -  REGISTER_GPR_COUNT - 1];

/* Query the value of %rip. */
__attribute__((always_inline)) static inline union Register64 QueryRip() {
    U64 rip;
    __asm__ volatile(
        "call 1f \n\t"
        "1: popq %0"
        : "=r"(rip)
    );
    return *(union Register64*)rip;
}

/* Read the value of the (TSC) time stamp counter. */
__attribute__((always_inline)) static inline U64 ReadTsc() {
    U32 lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return (U64)lo | (U64)hi << 32;
}

/* Queries regset from register data. These values are not that accurate. */
extern void ASM_PROC QueryRegSet(Register64AggregateSet _regSet64, Register128AggregateSet _regSet128);

/* Prints the value of a single register and the name. */
extern void DumpReg64(union Register64 _reg, const char* _regName);

/* Prints the value of a single register and the name. */
extern void DumpReg128(union Register128 _reg, const char* _regName);

/* Prints the value of all registers. */ 
extern void DumpAllRegs(Bool _xmm);

#endif
