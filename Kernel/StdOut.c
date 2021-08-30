#include "StdOut.h"
#include "Format.h"
#include "Kernel.h"
#include "Drivers/Screen.h"

static void StdOutFlushCallback(struct Stream* const _self, U8* const _buf, const U64 _size) {
    (void)_size, (void)_self;
    ScreenPrintAtFixed((const char*)_buf, _size, -1, -1, PRINT_COLOR_TEXT);
}

static struct Stream* STDOUT = NULL;

struct Stream* InitStdOut(struct Stream* const _storage, U8* const _buf, const U64 _size) {
    if (UNLIKELY(STDOUT)) {
        return STDOUT;
    }
    if (UNLIKELY(!_storage || !_buf || !_size)) {
        return NULL;
    }
    _storage->Begin = _storage->Needle = _buf;
    _storage->WriteCallback = NULL;
    _storage->FlushCallback = &StdOutFlushCallback;
    _storage->FlushThreshold = _size;
    return STDOUT = _storage;
}

struct Stream* GetStdOut(void) {
    if (UNLIKELY(!STDOUT)) {
        PANIC("Stream for stdout not initialized!");
    }
    return STDOUT;
}

void FlushStdOut(void) {
    if (UNLIKELY(!StreamFlush(STDOUT))) {
        PANIC("Stream flush of stdout failed!");
    }
}
