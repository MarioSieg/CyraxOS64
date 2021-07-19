#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char           U8;
typedef signed char             I8;
typedef unsigned short int      U16;
typedef signed short int        I16;
typedef unsigned int            U32;
typedef signed int              I32;
typedef unsigned long long      U64;
typedef signed long long        I64;
typedef float                   F32;
typedef double                  F64;
typedef U8                      Bool;
typedef U32                     UIntPtr32;
typedef U64                     UIntPtr64;

#define U8_MIN      0x00
#define U8_MAX      0xFF
#define I8_MIN     -0x80
#define I8_MAX      0x7F

#define U16_MIN     0x0000
#define U16_MAX     0xFFFF
#define I16_MIN    -0x8000
#define I16_MAX     0x7FFF

#define U32_MIN     0x00000000
#define U32_MAX     0xFFFFFFFF
#define I32_MIN    -0x80000000
#define I32_MAX     0x7FFFFFFF

#define U64_MIN     0x0000000000000000
#define U64_MAX     0xFFFFFFFFFFFFFFFF
#define I64_MIN    -0x8000000000000000
#define I64_MAX     0x7FFFFFFFFFFFFFFF

#define I8_C(_x)    _x
#define U8_C(_x)    _x
#define I16_C(_x)   _x
#define U16_C(_x)   _x
#define I32_C(_x)   _x
#define U32_C(_x)   _x##U
#define I64_C(_x)   _x##LL
#define U64_C(_x)   _x##ULL

#define TRUE        1
#define FALSE       0
#define NULL        ((void*)0)

/* Optimize branches for a TRUE condition. Might affect code layout, caching and instruction branch hints. */
#define LIKELY(_x)   __builtin_expect(!!( _x ), TRUE)

/* Optimize branches for a FALSE condition. Might affect code layout, caching and instruction branch hints. */
#define UNLIKELY(_x) __builtin_expect(!!( _x ), FALSE)

/* Marks a function which is written in assembly. */
#define ASM_PROC

/* Copy '_size' bytes of memory from '_src' to '_dst'.  */
extern void* MemCpy(void* restrict _dst, const void* restrict _src, U64 _size);

/* Volatile copy '_size' bytes of memory from '_src' to '_dst'.  */
extern volatile void* MemCpyV(volatile void* restrict _dst, const volatile void* restrict _src, U64 _size);

/* Fill the memory '_block' of '_size_ with '_val'. */
extern void* MemSet(void* _block, U8 _val, U64 _size);

/* Volatile fill the memory '_block' of '_size_ with '_val'. */
extern volatile void* MemSetV(volatile void* _block, U8 _val, U64 _size);

/* Reverses the bytes in the buffer. */
extern void ReverseBytes(void* _buf, U64 _size);

/* Trigger a kernel panic, print file and line info and loop forever. */
_Noreturn extern void Panic(const char* _msg, const char* _file, const I32 _line);

/* Trigger a kernel panic, print file and line info and loop forever. */
#define PANIC(_msg) Panic(_msg, __FILE__, __LINE__)

/* Convert an I64 into a string buffer. */
extern U64 FmtI64(I64 _n, char _buf[32]);

/* Convert an I64 into a string buffer. */
extern U64 FmtI64Hex(I64 _n, char _buf[32]);

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
    REGISTER_RAX    = 0,
    REGISTER_RBX    = 1,
    REGISTER_RCX    = 2,
    REGISTER_RDX    = 3,
    REGISTER_RSI    = 4,
    REGISTER_RDI    = 5,
    REGISTER_RSP    = 6,
    REGISTER_RBP    = 7,
    REGISTER_R8     = 8,
    REGISTER_R9     = 9,
    REGISTER_R10    = 10,
    REGISTER_R11    = 11,
    REGISTER_R12    = 12,
    REGISTER_R13    = 13,
    REGISTER_R14    = 14,
    REGISTER_R15    = 15,

    REGISTER_XMM0   = 16,
    REGISTER_XMM1   = 17,
    REGISTER_XMM2   = 18,
    REGISTER_XMM3   = 19,
    REGISTER_XMM4   = 20,
    REGISTER_XMM5   = 21,
    REGISTER_XMM6   = 22,
    REGISTER_XMM7   = 23,
    REGISTER_XMM8   = 24,
    REGISTER_XMM9   = 25,
    REGISTER_XMM10  = 26,
    REGISTER_XMM11  = 27,
    REGISTER_XMM12  = 28,
    REGISTER_XMM13  = 29,
    REGISTER_XMM14  = 30,
    REGISTER_XMM15  = 31,
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
typedef union Register64 Register64AggregateSet[REGISTER_COUNT >> 1];
typedef union Register128 Register128AggregateSet[REGISTER_COUNT >> 1];

/* Query the value of %eip. */
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
