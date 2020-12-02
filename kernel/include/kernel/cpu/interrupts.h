#ifndef _RLX_INT_H
#define _RLX_INT_H


#include "descriptor.h"
#include "registers.h"

namespace rlxos::kernel::interrupt {
    typedef void(*func_t)(rlxos::cpu::registers_t*);
    void install(uint8_t, func_t);
}


#endif