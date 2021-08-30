#ifndef STDOUT_H
#define STDOUT_H

#include "Stream.h"

/* Initialize output stream. */
extern struct Stream* InitStdOut(struct Stream* _storage, U8* _buf, U64 _size);

/* Returns the output stream. */
extern struct Stream* GetStdOut(void);

/* Flushes the output stream. */
extern void FlushStdOut(void);

#endif
