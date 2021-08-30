#ifndef STREAM_H
#define STREAM_H

#include "Foundation.h"

struct Stream {
    U8* Begin;
    U8* Needle;
    void (*WriteCallback)(struct Stream* const _self, U8 _x);
    void (*FlushCallback)(struct Stream* const _self, U8* _buf, U64 _size);
    PtrDiff64 FlushThreshold;
};

extern void StreamWrite(struct Stream* _self, U8 _value);
extern void StreamWriteBuf(struct Stream* _self, const U8* _buffer, U64 _size);
extern void StreamWriteStr(struct Stream* _self, const char* _str);
extern void StreamIter(struct Stream* _self, void(*_callback)(U8));
extern Bool StreamShouldFlush(const struct Stream* _self);
extern Bool StreamFlush(struct Stream* _self);
extern Bool StreamAutoFlush(struct Stream* _self);

#endif
