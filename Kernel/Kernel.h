#ifndef KERNEL_H
#define KERNEL_H

#include "Foundation.h"
#include "Memory.h"
#include "Format.h"

/* Trigger a kernel panic, print file and line info and loop forever. */
_Noreturn extern void Panic(const char* _msg, const char* _file, const I32 _line);

/* Trigger a kernel panic, print file and line info and loop forever. */
#define PANIC(_msg) Panic(_msg, __FILE__, __LINE__)

#endif
