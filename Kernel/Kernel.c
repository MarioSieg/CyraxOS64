#include "Kernel.h"
#include "Register.h"
#include "Format.h"
#include "StdOut.h"
#include "Drivers/Screen.h"

void Panic(const char* const _msg, const char* const _file, const I32 _line) {
    ScreenPrintAt("! ### FATAL KERNEL PANIC ### !\n", -1, -1, PRINT_COLOR_ERROR);
    ScreenPrintAt(_msg, -1, -1, PRINT_COLOR_ERROR);
    ScreenPrintAt("\nFile: ", -1, -1, PRINT_COLOR_ERROR);
    ScreenPrintAt(_file, -1, -1, PRINT_COLOR_ERROR);
    char buf[32];
    FmtI64(_line, buf);
    ScreenPrintAt("\nLine: ", -1, -1, PRINT_COLOR_ERROR);
    ScreenPrintAt(buf, -1, -1, PRINT_COLOR_ERROR);
    PrintNL();
    DumpAllRegs(FALSE);
    FlushStdOut();
    for(;;);
}
