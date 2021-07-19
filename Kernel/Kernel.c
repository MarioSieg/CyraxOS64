#include "Kernel.h"
#include "../Drivers/Screen.h"

void* MemCpy(void* restrict const _dst, const void* restrict const _src, const U64 _size) {
    register U8* restrict to = (U8*)_dst;
    register const U8* restrict from = (const U8*)_src;
    register const U8* restrict const fromEnd = (const U8*)_src + _size;
    while (from < fromEnd) {
        *to++ = *from++;
    }
    return _dst;
}

volatile void* MemCpyV(volatile void* restrict const _dst, const volatile void* restrict const _src, const U64 _size) {
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

void ReverseBytes(void* const _buf, const U64 _size) {
    register U8* restrict lo = (U8*)_buf;
    register U8* restrict hi = lo + _size - 1;
    register U8 tmp;
    while (lo < hi) {
        tmp = *lo;
        *lo++ = *hi;
        *hi-- = tmp;
    }
}

void Panic(const char* const _msg, const char* const _file, const I32 _line) {
    ScreenPrintError("! ### FATAL KERNEL PANIC ### !\n");
    ScreenPrintError(_msg);
    ScreenPrintError("\nFile: ");
    ScreenPrintError(_file);
    char buf[32];
    FmtI64(_line, buf);
    ScreenPrintError("\nLine: ");
    ScreenPrintError(buf);
    NewLine();
    DumpAllRegs(FALSE);
    for(;;);
}

U64 FmtI64(register I64 _n, char _buf[32]) {
    register char* str = _buf;
    register U64 i = 0;
    I64 sign;
    if ((sign = _n) < 0) {
         _n = -_n;
    }
    i = 0;
    do {
        str[i++] = _n % 10 + '0';
    } while ((_n /= 10) > 0);
    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';
    ReverseBytes(str, i);
    return i;
}

U64 FmtI64Hex(register I64 _n, char _buf[32]) {
    register U8 width = 32;
    register char* dst = _buf;
    register char* res = dst + 32;
    register U64 i = 0;
    dst = res;
    while (width--) {
        *--dst = "0123456789ABCDEF"[_n & 0x0F];
        _n >>= 4;
        ++i;
    }
    return i;
}

const char* const REG_NAMES[REGISTER_COUNT] = {
    "%rax",
    "%rbx",
    "%rcx",
    "%rdx",
    "%rsi",
    "%rdi",
    "%rsp",
    "%rbp",
    "%r8 ",
    "%r9 ",
    "%r10",
    "%r11",
    "%r12",
    "%r13",
    "%r14",
    "%r15",

    "%xmm0 ",
    "%xmm1 ",
    "%xmm2 ",
    "%xmm3 ",
    "%xmm4 ",
    "%xmm5 ",
    "%xmm6 ",
    "%xmm7 ",
    "%xmm8 ",
    "%xmm9 ",
    "%xmm10",
    "%xmm11",
    "%xmm12",
    "%xmm13",
    "%xmm14",
    "%xmm15"
};

void DumpReg64(const union Register64 _reg, const char* const _regName) {
    ScreenPrint(_regName);
    ScreenPrint(": ");
    char buf[32];
    FmtI64Hex(_reg.R64, buf);
    ScreenPrint(buf);
    NewLine();
}

void DumpReg128(union Register128 _reg, const char* _regName) {
    ScreenPrint(_regName);
    ScreenPrint(": ");
    char buf[64];
    const U64 off = FmtI64Hex(_reg.Hi.U, buf);
    FmtI64Hex(_reg.Lo.U, buf + off - 1);
    ScreenPrint(buf);
    NewLine();
}

void DumpAllRegs(const Bool _xmm) {
    Register64AggregateSet reg64Set;
    Register128AggregateSet reg128Set;
    QueryRegSet(reg64Set, reg128Set);
    for (U8 i = 0; i < REGISTER_COUNT >> 1; ++i) {
        DumpReg64(reg64Set[i], REG_NAMES[i]);
    }
    if (_xmm) {
        for (U8 i = 15; i < REGISTER_COUNT; ++i) {
            DumpReg128(reg128Set[i - 16], REG_NAMES[i]);
        }
    }
}
