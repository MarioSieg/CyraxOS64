#ifndef PORTS_H
#define PORTS_H

#include "../Kernel/Kernel.h"

__attribute__((flatten)) static inline U8 PortInU8(const U16 _port) {
    U8 r;
    asm volatile("in %%dx, %%al" : "=a"(r) : "d"(_port));
    return r;
}

__attribute__((flatten)) static inline void PortOutU8(const U16 _port, const U8 _data) {
    asm volatile("out %%al, %%dx" :: "a"(_data), "d"(_port));
}

__attribute__((flatten)) static inline U16 PortInU16(const U16 _port) {
    U16 r;
    asm volatile("in %%dx, %%ax" : "=a"(r) : "d"(_port));
    return r;
}

__attribute__((flatten)) static inline void PortOutU16(const U16 _port, const U16 _data) {
    asm volatile("out %%ax, %%dx" :: "a"(_data), "d"(_port));
}

#endif
