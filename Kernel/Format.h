#ifndef FORMAT_H
#define FORMAT_H

#include "Foundation.h"

/* Convert an I64 into a string buffer. */
extern U64 FmtI64(I64 _n, char _buf[64]);

/* Convert an I64 into a string buffer. */
extern U64 FmtI64Hex(I64 _n, char _buf[32]);

#define PRINT_COLOR_TEXT 0x0F
#define PRINT_COLOR_ERROR 0xF4

/* Prints a message out. */
extern void Print(const char* _msg);

/* Prints a message out as error. */
extern void EPrint(const char* _msg);

/* Clears the screem. */
extern void Clear(void);

/* Prints a new line. */
static inline void PrintNL(void) { 
    Print("\n");
}

#endif
