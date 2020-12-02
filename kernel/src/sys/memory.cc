#include <kernel/sys/memory.h>

using namespace rlxos::kernel;

void memory::set(uint8_t* dest, uint8_t val, uint32_t len)
{
    uint8_t* _t = (uint8_t*)dest;
    for(; len != 0; len--) *_t++ = val;
}

int8_t memory::cmp(const uint8_t* a, const uint8_t* b)
{
    while(*a)
    {
        if (*a != *b)  
            break;
        *a++;
        *b++;
    }

    return *(const uint8_t*)a - *(const uint8_t*)b;
}