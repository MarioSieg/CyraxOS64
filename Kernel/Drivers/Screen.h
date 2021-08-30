#ifndef SCREEN_H
#define SCREEN_H

#include "../Foundation.h"

#define VGA_VRAM_PTR (volatile U8*)0xB8000
#define SCREEN_MAX_ROWS 25
#define SCREEN_MAX_COLS 80
#define SCREEN_PORT_CTRL 0x3D4
#define SCREEN_PORT_DATA 0x3D5

extern void ScreenClear(void);
extern void ScreenPrintAt(const char* _msg, I32 _col, I32 _row, U8 _attrib);
extern void ScreenPrintAtFixed(const char* _msg, U64 _size, I32 _col, I32 _row, U8 _attrib);

#endif
