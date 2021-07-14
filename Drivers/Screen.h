#ifndef SCREEN_H
#define SCREEN_H

#include "../Kernel/Kernel.h"

#define VGA_VRAM_PTR (volatile U8*)0xB8000
#define SCREEN_MAX_ROWS 25
#define SCREEN_MAX_COLS 80
#define SCREEN_COLOR_TEXT 0x0F
#define SCREEN_COLOR_ERROR 0xF4
#define SCREEN_PORT_CTRL 0x3D4
#define SCREEN_PORT_DATA 0x3D5

extern void ScreenClear(void);
extern void ScreenPrintAt(const char* _msg, I32 _col, I32 _row, U8 _attrib);

static inline void ScreenPrint(const char* _msg) {
    ScreenPrintAt(_msg, -1, -1, SCREEN_COLOR_TEXT);
}

static inline void NewLine(void) {
    ScreenPrintAt("\n", -1, -1, SCREEN_COLOR_TEXT);
}

static inline void ScreenPrintError(const char* _msg) {
    ScreenPrintAt(_msg, -1, -1, SCREEN_COLOR_ERROR);
}

#endif
