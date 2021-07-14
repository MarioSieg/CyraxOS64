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

#define TRUE        1
#define FALSE       0
#define NULL        ((void*)0)

#define LIKELY(_x)   __builtin_expect(!!( _x ), TRUE)
#define UNLIKELY(_x) __builtin_expect(!!( _x ), FALSE)

/* Copy '_size' bytes of memory from '_src' to '_dst'.  */
extern void* MemCpy(void* _dst, const void* _src, U32 _size);

/* Volatile copy '_size' bytes of memory from '_src' to '_dst'.  */
extern volatile void* MemCpyV(volatile void* _dst, const volatile void* _src, U32 _size);

/* Fill the memory '_block' of '_size_ with '_val'. */
extern void* MemSet(void* _block, U8 _val, U32 _size);

/* Volatile fill the memory '_block' of '_size_ with '_val'. */
extern volatile void* MemSetV(volatile void* _block, U8 _val, U32 _size);

/* Trigger a kernel panic, print file and line info and loop forever. */
__attribute__((noreturn)) extern void Panic(const char* _msg, const char* _file, const I32 _line);

#define PANIC_DUMP_CODE TRUE
#define PANIC_DUMP_SIZE 8

/* Trigger a kernel panic, print file and line info and loop forever. */
#define PANIC(_msg) Panic(_msg, __FILE__, __LINE__)

/* Convert an I32 into a string buffer. */
extern void I32ToStr(I32 _n, char* _str);

/* Represents a 32-bit GPR such as %eax or %esi. */
union Register32 {
    U32 R32;
    struct {
        U16 Reverved;
        U16 R16;
        struct {
            U8 R8Hi;
            U8 R8Lo;
        };
    };
};

/* Contains all register IDs except for %eip! */
enum Register {
    REGISTER_EAX = 0,
    REGISTER_EBX = 1,
    REGISTER_ECX = 2,
    REGISTER_EDX = 3,
    REGISTER_ESI = 4,
    REGISTER_EDI = 5,
    REGISTER_ESP = 6,
    REGISTER_EBP = 7,
    REGISTER_COUNT
};

/* Contains the names of all registers. */
extern const char* const REG_NAMES[REGISTER_COUNT];

/* Contains bit masks for all registers except for %eip! */
enum RegisterMask {
    REGISTER_MASK_EAX = 1 << REGISTER_EAX,
    REGISTER_MASK_EBX = 1 << REGISTER_EBX,
    REGISTER_MASK_ECX = 1 << REGISTER_ECX,
    REGISTER_MASK_EDX = 1 << REGISTER_EDX,
    REGISTER_MASK_ESI = 1 << REGISTER_ESI,
    REGISTER_MASK_EDI = 1 << REGISTER_EDI,
    REGISTER_MASK_ESP = 1 << REGISTER_ESP,
    REGISTER_MASK_EBP = 1 << REGISTER_EBP,
};

/* Contians storage for all registers. */
typedef union Register32 RegSet32[REGISTER_COUNT];

/* Query the value of %eip. */
__attribute__((always_inline)) static inline union Register32 QueryEip() {
    U64 eip;
    asm
    (
        "call 1f \n\t"
        "1: popq %0"
        : "=r"(eip)
    );
    union Register32 r = {0};
    return r;
}

/* Queries regset from register data. These values are not that accurate. */
extern void QueryRegSet(RegSet32 _regSet);

/* Prints the value of a single register and the name. */
extern void DumpReg(union Register32 _reg, const char* _regName);

#endif
