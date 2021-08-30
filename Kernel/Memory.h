#ifndef MEMORY_H
#define MEMORY_H

#include "Foundation.h"

/* Copy '_size' bytes of memory from '_src' to '_dst'.  */
extern void* MemCpy(void* restrict _dst, const void* restrict _src, U64 _size);

/* Fill the memory '_block' of '_size_ with '_val'. */
extern void* MemSet(void* _block, U8 _val, U64 _size);

/* Reverses the bytes in the buffer. */
extern void ReverseBytes(void* _buf, U64 _size);

#endif
