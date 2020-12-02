#ifndef _RLX_DESC_H
#define _RLX_DESC_H

#include <kernel/types.h>

namespace x86::descriptor {
namespace gdt {
    
    struct entry_t
    {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t  base_middle;
        uint8_t  access;
        uint8_t  granulartiy;
        uint8_t  base_high;
    } __attribute__((packed));

    struct pointer_t
    {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed));

}

namespace idt {

    struct entry_t
    {
        uint16_t base_lower;
        uint16_t selector;
        uint8_t  zero;
        uint8_t  flags;
        uint16_t  base_high;
    } __attribute__((packed));


    struct pointer_t
    {
        uint16_t limit;
        uint32_t base;

    } __attribute__((packed));
}

    void initialize(void);
}

#endif