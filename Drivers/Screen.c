#include "Screen.h"
#include "Ports.h"

static inline I32 GetOffset(const I32 _col, const I32 _row) {
    return (_row * SCREEN_MAX_COLS + _col) << 1;
}

static inline I32 GetRowOffset(const I32 _offset) {
    return _offset / (SCREEN_MAX_COLS << 1);
}

static inline I32 GetColOffset(const I32 _offset) {
    return (_offset - (GetRowOffset(_offset) * (SCREEN_MAX_COLS << 1))) >> 1;
}

static I32 GetCursorOffset() {
    PortOutU8(SCREEN_PORT_CTRL, 14);
    I32 offset = PortInU8(SCREEN_PORT_DATA) << 8;
    PortOutU8(SCREEN_PORT_CTRL, 15);
    offset += PortInU8(SCREEN_PORT_DATA);
    return offset << 1;
}

static void SetCursorOffset(I32 _offset) {
    _offset >>= 1;
    PortOutU8(SCREEN_PORT_CTRL, 14);
    PortOutU8(SCREEN_PORT_DATA, (_offset >> 8) & 0xFF);
    PortOutU8(SCREEN_PORT_CTRL, 15);
    PortOutU8(SCREEN_PORT_DATA, _offset & 0xFF);
}

void ScreenClear(void) {
    register const I32 size = SCREEN_MAX_COLS * SCREEN_MAX_ROWS;
    register volatile U8* const vga = VGA_VRAM_PTR;
    for (register I32 i = 0; i < size; ++i) {
        *(vga + (i * 2)) = ' ';
        *(vga + (i * 2 + 1)) = SCREEN_COLOR_TEXT;
    }
    SetCursorOffset(GetOffset(0, 0));
}

static I32 PrintCharAt(const char _c, I32 _col, I32 _row, const U8 _attrib) {
    volatile U8* const vga = VGA_VRAM_PTR;
    if (_col >= SCREEN_MAX_COLS || _row >= SCREEN_MAX_ROWS) {
        *(vga + ((SCREEN_MAX_COLS * SCREEN_MAX_ROWS) << 1) - 2) = 'X';
        *(vga + ((SCREEN_MAX_COLS * SCREEN_MAX_ROWS) << 1) - 1) = SCREEN_COLOR_ERROR;
        return GetOffset(_col, _row);
    }
    I32 offset = _col >= 0 && _row >= 0 ? GetOffset(_col, _row) : GetCursorOffset();
    if (_c == '\n') {
        _row = GetRowOffset(offset);
        offset = GetOffset(0, _row + 1);
    } else {
        *(vga + offset) = _c;
        *(vga + offset + 1) = _attrib;
        offset += 2;
    }
    if (offset >= SCREEN_MAX_ROWS * (SCREEN_MAX_COLS << 1)) {
        for (register I32 i = 0; i < SCREEN_MAX_ROWS; ++i) {
            MemCpyV
            (
                GetOffset(0, i - 1) + VGA_VRAM_PTR,
                GetOffset(0, i) + VGA_VRAM_PTR,
                SCREEN_MAX_COLS << 1
            );
        }
        volatile U8* last = GetOffset(0, SCREEN_MAX_ROWS - 1) + VGA_VRAM_PTR;
        MemSetV(last, 0, SCREEN_MAX_COLS << 1);
        offset -= SCREEN_MAX_COLS << 1;
    }
    SetCursorOffset(offset);
    return offset;
}

void ScreenPrintAt(register const char* _msg, register I32 _col, register I32 _row, register const U8 _attrib) {
    I32 offset;
    if (_col >= 0 && _row >= 0)
        offset = GetOffset(_col, _row);
    else {
        offset = GetCursorOffset();
        _row = GetRowOffset(offset);
        _col = GetColOffset(offset);
    }
    while (*_msg) {
        offset = PrintCharAt(*_msg++, _col, _row, _attrib);
        _row = GetRowOffset(offset);
        _col = GetColOffset(offset);
    }
}
