#ifndef _RLX_CMOS_H
#define _RLX_CMOS_H

#include "../kernel.h"
#define CURRENT_YEAR 2020

namespace rlxos::cpu::rtc {
    struct data_t {
        uint8_t sec, min, hour;
        uint8_t day, month, year;
    };

    enum port {
        ADDRESS = 0x70,
        DATA    = 0x71
    };

    static uint8_t update_flag() {
        outb(port::ADDRESS, 0x0A);
        return (inb(port::DATA) & 0x80);
    }

    static uint8_t get_register(int reg) {
        outb(port::ADDRESS, reg);
        return inb(port::DATA);
    }

    data_t read();
}
#endif