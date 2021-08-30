#include "Stream.h"
#include "Kernel.h"

void StreamWrite(struct Stream* const _self, const U8 _value) {
    if (_self->WriteCallback) {
        (*_self->WriteCallback)(_self, _value);
    }
    *_self->Needle++ = _value;
    if (StreamShouldFlush(_self) && !StreamFlush(_self)) {
        PANIC("Failed to flush stream!");
    }
}

void StreamWriteBuf(struct Stream* const _self, const U8* const _buffer, const U64 _size) {
    register const U8* i = _buffer;
    register const U8* const end = _buffer + _size;
    while (i < end) {
        StreamWrite(_self, *i++);
    }
}

void StreamWriteStr(struct Stream* const _self, register const char* _str) {
    while(*_str) {
        StreamWrite(_self, *_str++);
    }
}

void StreamIter(struct Stream* const _self, void (*const _callback)(U8)) {
    register U8* i = _self->Begin;
    register U8* const end = _self->Needle;
    while (i < end) {
        (*_callback)(*i++);
    }
}

Bool StreamShouldFlush(const struct Stream* const _self) {
    const PtrDiff64 diff = _self->Needle - _self->Begin;
    return diff >= _self->FlushThreshold;
}

Bool StreamFlush(struct Stream* const _self) {
    if (!_self->FlushCallback) {
        return FALSE;
    }
    const PtrDiff64 diff = _self->Needle - _self->Begin;
    if (!diff) {
        return FALSE;
    }
    (*_self->FlushCallback)(_self, _self->Begin, diff);
    _self->Needle = _self->Begin;
    return TRUE;
}

Bool StreamAutoFlush(struct Stream* const _self) {
    return StreamShouldFlush(_self) && StreamFlush(_self);
}
