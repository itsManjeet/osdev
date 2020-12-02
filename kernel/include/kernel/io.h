#ifndef _RLX_IO_H
#define _RLX_IO_H


#include "types.h"

#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)
typedef __builtin_va_list va_list;

namespace rlxos::kernel::io {
    void print(char* fmt, ...);
    void process(char* fmt, ...);
}

#endif