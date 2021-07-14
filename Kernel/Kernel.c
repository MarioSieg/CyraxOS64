#include "Kernel.h"
#include "../Drivers/Screen.h"

void* MemCpy(void* const _dst, const void* const _src, const U64 _size) {
    register U8* restrict to = (U8*)_dst;
    register const U8* restrict from = (const U8*)_src;
    register const U8* restrict const fromEnd = (const U8*)_src + _size;
    while (from < fromEnd) {
        *to++ = *from++;
    }
    return _dst;
}

volatile void* MemCpyV(volatile void* const _dst, const volatile void* const _src, const U64 _size) {
    register volatile U8* restrict to = (U8*)_dst;
    register const volatile U8* restrict from = (const volatile U8*)_src;
    register const volatile U8* restrict const fromEnd = from + _size;
    while (from < fromEnd) {
        *to++ = *from++;
    }
    return _dst;
}

void* MemSet(void* const _block, const U8 _val, const U64 _size) {
    register U8* i = (U8*)_block;
    register const U8* const end = i + _size;
    while (i < end) {
        *i++ = _val;
    }
    return _block;
}

volatile void* MemSetV(volatile void* const _block, const U8 _val, const U64 _size) {
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
    FormatBuf64 buf;
    FmtI64(_line, buf);
    ScreenPrintError("\nLine: ");
    ScreenPrintError(buf);
    NewLine();
    DumpAllRegs();
    for(;;);
}

void FmtI64(register I64 _n, FormatBuf64 _buf) {
    register char* str = _buf;
    I64 sign = _n;
    if (sign < 0) {
        _n = -_n;
    }
    do {
        *str++ = _n % 10 + '0';
    }
    while ((_n /= 10) > 0);
    if (sign < 0) {
         *str++ = '-';
    }
    *str = '\0';
}

void FmtI64Hex(register I64 _n, FormatBuf64 _buf) {
    register char* put = _buf + sizeof(FormatBuf64);
    *--put = '\0';
    if (!_n) {
        *_buf = '0';
        return;
    }
    do {
        *--put = *("0123456789ABCDEF" + (_n & 0x0F));
        _n >>= 4;
    } while(_n && put != _buf);
}

const char* const REG_NAMES[REGISTER_COUNT] = {
    "rax",
    "rbx",
    "rcx",
    "rdx",
    "rsi",
    "rdi",
    "rsp",
    "rbp",
    "r8 ",
    "r9 ",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15",

    "xmm0",
    "xmm1",
    "xmm2",
    "xmm3",
    "xmm4",
    "xmm5",
    "xmm6",
    "xmm7",
    "xmm8",
    "xmm9",
    "xmm10",
    "xmm11",
    "xmm12",
    "xmm13",
    "xmm14",
    "xmm15"
};

void QueryRegSet(Register64AggregateSet _regSet64, Register128AggregateSet _regSet128) {
    U64* const regSet64 = (U64*)_regSet64;
    U64* const regSet128 = (U64*)_regSet128;
    asm volatile("movq %%rax, %0" : "=r" (regSet64[REGISTER_RAX])::);
    asm volatile("movq %%rbx, %0" : "=r" (regSet64[REGISTER_RBX])::);
    asm volatile("movq %%rcx, %0" : "=r" (regSet64[REGISTER_RCX])::);
    asm volatile("movq %%rdx, %0" : "=r" (regSet64[REGISTER_RDX])::);
    asm volatile("movq %%rsi, %0" : "=r" (regSet64[REGISTER_RSI])::);
    asm volatile("movq %%rdi, %0" : "=r" (regSet64[REGISTER_RDI])::);
    asm volatile("movq %%rsp, %0" : "=r" (regSet64[REGISTER_RSP])::);
    asm volatile("movq %%rbp, %0" : "=r" (regSet64[REGISTER_RBP])::);
    asm volatile("movq %%r8 , %0" : "=r" (regSet64[REGISTER_R8 ])::);
    asm volatile("movq %%r9 , %0" : "=r" (regSet64[REGISTER_R9 ])::);
    asm volatile("movq %%r10, %0" : "=r" (regSet64[REGISTER_R10])::);
    asm volatile("movq %%r11, %0" : "=r" (regSet64[REGISTER_R11])::);
    asm volatile("movq %%r12, %0" : "=r" (regSet64[REGISTER_R12])::);
    asm volatile("movq %%r13, %0" : "=r" (regSet64[REGISTER_R13])::);
    asm volatile("movq %%r14, %0" : "=r" (regSet64[REGISTER_R14])::);
    asm volatile("movq %%r15, %0" : "=r" (regSet64[REGISTER_R15])::);
    (void)regSet128;
}

void DumpReg64(const union Register64 _reg, const char* const _regName) {
    ScreenPrint("%");
    ScreenPrint(_regName);
    ScreenPrint(": ");
    FormatBuf64 buf;
    FmtI64Hex(_reg.R64, buf);
    ScreenPrint(buf);
    NewLine();
}

void DumpReg128(union Register128 _reg, const char* _regName) {
    (void)_reg;
    (void)_regName;
}

void DumpAllRegs(void) {
    Register64AggregateSet reg64Set;
    Register128AggregateSet reg128Set;
    QueryRegSet(reg64Set, reg128Set);

    for (U8 i = 0; i < REGISTER_COUNT >> 1; ++i) {
        DumpReg64(reg64Set[i], REG_NAMES[i]);
    }
    for (U8 i = 0; i < REGISTER_COUNT >> 1; ++i) {
        DumpReg128(reg128Set[i], REG_NAMES[i]);
    }
}
