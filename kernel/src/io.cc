#include <kernel/kernel.h>

using namespace rlxos::kernel;

char* _cnv(uint32_t num, uint8_t base)
{
    static char repr[] = "0123456789ABCDEF";
    static char buf[50];
    char *ptr;
    ptr = &buf[49];
    *ptr = '\0';

    do {
        *--ptr = repr[num % base];
        num /= base;
    } while(num != 0);

    return ptr;
}

void
io::process(char* fmt, ...)
{
    va_list arg;
    x86::vga::set_color(x86::vga::color::LIGHT_MAGENTA);
    io::print(":: process :: ");

    va_start(arg, fmt);
    x86::vga::set_color(x86::vga::color::LIGHT_GRAY);
    io::print(fmt, arg);
    x86::vga::set_color(x86::vga::color::DARK_GRAY);
    io::print("....\n");
    va_end(arg);
}

void
io::print(char* fmt, ...)
{
    va_list parms;
    va_start(parms, fmt);

    while(*fmt != '\0')
    {
        if (fmt[0] != '%' || fmt[1] == '%')
        {
            if (fmt[0] == '%')
                fmt++;
            
            uint32_t amt = 1;
            while(fmt[amt] && fmt[amt] != '%')
                amt++;
            
            x86::vga::write(fmt, amt);
            fmt += amt;
            continue;
        }

        const char* fmt_begn_at = fmt++;
        if (*fmt == 'c')
        {
            fmt++;
            char c = (char) va_arg(parms, int);
            x86::vga::write(c);
        }

        else if (*fmt == 's')
        {
            fmt++;
            const char* str = va_arg(parms, const char*);
            x86::vga::write(str);
        }

        else if (*fmt == 'd')
        {
            fmt++;
            int d = va_arg(parms, int);
            if (d < 0)
            {
                d = -d;
                x86::vga::write('-');
            }
            x86::vga::write(_cnv(d, 10));
        }

        else if (*fmt == 'x')
        {
            fmt++;
            unsigned long x = va_arg(parms, unsigned long);
            x86::vga::write("0x");
            x86::vga::write(_cnv(x, 16));
        }
    }

    va_end(parms);
}
