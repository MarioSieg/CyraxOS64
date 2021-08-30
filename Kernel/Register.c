#include "Register.h"
#include "Format.h"
#include "Memory.h"

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

    "%cr0",
    "%cr2",
    "%cr3",
    "%cr4",

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
    Print(_regName);
    Print(": ");
    char buf[64];
    FmtI64(_reg.R64, buf);
    Print(buf);
    PrintNL();
}

void DumpReg128(union Register128 _reg, const char* _regName) {
    Print(_regName);
    Print(": ");
    char buf[64];
    const U64 off = FmtI64Hex(_reg.Hi.U, buf);
    FmtI64Hex(_reg.Lo.U, buf + off - 1);
    Print(buf);
    PrintNL();
}

void DumpAllRegs(const Bool _xmm) {
    (void)_xmm;
    Register64AggregateSet reg64Set;
    Register128AggregateSet reg128Set;
    QueryRegSet(reg64Set, reg128Set);
    for (U8 i = 0; i < REGISTER_GPR_COUNT; ++i) {
        DumpReg64(reg64Set[i], REG_NAMES[i]);
    }
}
