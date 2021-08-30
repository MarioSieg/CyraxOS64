#ifndef FOUNDATION_H
#define FOUNDATION_H

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
typedef U64                     UIntPtr64;
typedef I64                     PtrDiff64;

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

#endif
