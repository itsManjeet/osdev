#ifndef _RLX_MEM_H
#define _RLX_MEM_H

#include "../types.h"

namespace rlxos::kernel::memory {
    void set(uint8_t *dest, uint8_t val, uint32_t len);
    int8_t cmp(const uint8_t *x, const uint8_t *y);
}


#endif