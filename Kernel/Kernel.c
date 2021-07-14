#include "Kernel.h"
#include "../Drivers/Screen.h"

void* MemCpy(void* const _dst, const void* const _src, const U32 _size) {
    register U8* to = (U8*)_dst;
    register const U8* from = (const U8*)_src;
    register const U8* const fromEnd = (const U8*)_src + _size;

    while (from < fromEnd) {
        *to++ = *from++;
    }

    return _dst;
}

volatile void* MemCpyV(volatile void* const _dst, const volatile void* const _src, U32 _size) {
    register volatile U8* to = (U8*)_dst;
    register const volatile U8* from = (const volatile U8*)_src;
    register const volatile U8* const fromEnd = from + _size;
    while (from < fromEnd) {
        *to++ = *from++;
    }
    return _dst;
}

void* MemSet(void* const _block, const U8 _val, const U32 _size) {
    register U8* to = (U8*)_block;
    register const U8* const from = to + _size;
    while (to < from) {
        *to++ = _val;
    }
    return _block;
}

volatile void* MemSetV(volatile void* const _block, const U8 _val, const U32 _size) {
    register volatile U8* to = (volatile U8*)_block;
    register const volatile U8* const from = to + _size;
    while (to < from) {
        *to++ = _val;
    }
    return _block;
}

void Panic(const char* const _msg, const char* const _file, const I32 _line) {
    ScreenPrintError("! ### FATAL KERNEL PANIC ### !\n");
    ScreenPrintError(_msg);

    ScreenPrintError("\nFile: ");
    ScreenPrintError(_file);

    char buf[64];
    MemSet(buf, 0, sizeof buf);
    I32ToStr(_line, buf);
    ScreenPrintError("\nLine: ");
    ScreenPrintError(buf);
    NewLn();

    const union Register32 eip = QueryEip();
    DumpReg(eip, "eip");
    NewLn();

    RegSet32 regSet;
    QueryRegSet(regSet);
    for(I32 i = 0; i < REGISTER_COUNT; ++i) {
        DumpReg(regSet[i], REG_NAMES[i]);
        NewLn();
    }

    #if PANIC_DUMP_CODE

    volatile const U8* machCode = (const U8*)(U64)eip.R32;
    if (machCode) {
        for(register I32 i = 0; i < PANIC_DUMP_SIZE; ++i) {
            const I32 k = *machCode++;
            MemSet(buf, 0, sizeof buf);
            I32ToStr(k, buf);
            ScreenPrint(buf);
            NewLn();
        }
    }

    #endif

    for(;;);
}

void I32ToStr(register I32 _n, register char* _str) {
    I32 sign = _n;
    if (sign < 0) {
        _n = -_n;
    }
    do {
        *_str++ = _n % 10 + '0';
    }
    while ((_n /= 10) > 0);
    if (sign < 0) {
         *_str++ = '-';
    }
    *_str = '\0';
}

const char* const REG_NAMES[REGISTER_COUNT] = {
    "eax",
    "ebx",
    "ecx",
    "edx",
    "esi",
    "edi",
    "esp",
    "ebp",
};

void QueryRegSet(RegSet32 _regSet) {
    U32* const regSet = &_regSet->R32;
    asm volatile("movl %%eax, %0": "=r" (regSet[REGISTER_EAX])::);
    asm volatile("movl %%ebx, %0": "=r" (regSet[REGISTER_EBX])::);
    asm volatile("movl %%ecx, %0": "=r" (regSet[REGISTER_ECX])::);
    asm volatile("movl %%edx, %0": "=r" (regSet[REGISTER_EDX])::);
    asm volatile("movl %%esi, %0": "=r" (regSet[REGISTER_ESI])::);
    asm volatile("movl %%edi, %0": "=r" (regSet[REGISTER_EDI])::);
    asm volatile("movl %%esp, %0": "=r" (regSet[REGISTER_ESP])::);
    asm volatile("movl %%ebp, %0": "=r" (regSet[REGISTER_EBP])::);
}

void DumpReg(const union Register32 _reg, const char* const _regName) {
    ScreenPrint("%");
    ScreenPrint(_regName);
    ScreenPrint(": ");
    char buf[32];
    MemSet(buf, 0, sizeof buf);
    const I32 repr = _reg.R32;
    I32ToStr(repr, buf);
    ScreenPrint(buf);
}
