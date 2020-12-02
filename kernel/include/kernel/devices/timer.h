#ifndef _RLX_TIMER_H
#define _RLX_TIMER_H

#include "../types.h"

namespace rlxos::kernel::devices::timer {
    void initialize(uint32_t freq);

    void get_time(uint32_t* ticks, uint32_t* subticks);
}

#endif