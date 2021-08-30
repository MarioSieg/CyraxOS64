#include "Memory.h"

void* MemCpy(void* restrict const _dst, const void* restrict const _src, const U64 _size) {
    register U8* restrict to = (U8*)_dst;
    register const U8* restrict from = (const U8*)_src;
    register const U8* restrict const fromEnd = (const U8*)_src + _size;
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
