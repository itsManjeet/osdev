#ifndef _KERNEL_H
#define _KERNEL_H

#include "types.h"
#include "io.h"
#include "sys/memory.h"
#include "sys/serial.h"
#include "devices/timer.h"
#include "devices/keyboard.h"
#include "shell.h"
#include "cpu/interrupts.h"
#include <vga.h>

#define LOGO "       .__          \n \
_______|  | ___  ___   ____  ______\n \
\\_  __ \\  | \\  \\/  /  /  _ \\/  ___/\n \
 |  | \\/  |__>    <  (  <_> )___ \\ \n \
 |__|  |____/__/\\_ \\  \\____/____  >\n \
                  \\/            \\/ \n"

#define VERSION "0.1.0"
#define PANIC(mesg) Panic(mesg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : PanicAssert(__FILE__, __LINE__, #b))

static void Panic(const char* mesg, const char* file, uint32_t line)
{
    asm volatile("cli");

    rlxos::kernel::io::print("PANIC(%s) at %s : %d\n", mesg, file, line);

    for(;;);
}

static void PanicAssert(const char* file, uint32_t line, const char* desc)
{
    asm volatile("cli");

    rlxos::kernel::io::print("ASSERTION_FAILED(%s) at %s : %d\n", desc, file, line);

    for(;;);
}

#endif
