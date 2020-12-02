#ifndef _RLX_VGA_H
#define _RLX_VGA_H

#include <kernel/types.h>

namespace x86::vga {

    namespace color {
        enum type {
            BLACK = 0, BLUE  = 1, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GRAY,
            DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
        };
    }

    void set_color(color::type, color::type);
    void set_color(color::type);
    void write(const char* );
    void write(const char*, uint32_t);
    void write(char);
    void clear();
    void initialize();

    void update_cursor();
}

#endif