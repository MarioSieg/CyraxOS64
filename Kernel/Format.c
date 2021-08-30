#include "Format.h"
#include "Memory.h"
#include "StdOut.h"
#include "Drivers/Screen.h"

U64 FmtI64(register I64 _n, char _buf[64]) {
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
    res[-1] = '\0';
    register U64 i = 0;
    dst = res;
    while (width--) {
        *--dst = "0123456789ABCDEF"[_n & 0x0F];
        _n >>= 4;
        ++i;
    }
    return i;
}

void Print(const char* const _msg) {
    StreamWriteStr(GetStdOut(), _msg);
}

void EPrint(const char* _msg) {
    ScreenPrintAt(_msg, -1, -1, PRINT_COLOR_ERROR);
}

void Clear(void) {
    ScreenClear();
}
