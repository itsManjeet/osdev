#include <kernel/kernel.h>

using namespace rlxos::kernel;

#define SUBTICKS_PER_TICKS 100000
uint32_t __ticks = 0;
uint32_t __sub_ticks = 0;

static void __timer_cb(rlxos::cpu::registers_t* r)
{
    __sub_ticks++;
    
    if (__sub_ticks >= SUBTICKS_PER_TICKS)
    {
        io::print("ticks: %d\n",__ticks);    
        __sub_ticks = 0;
        __ticks++;
    }
}

void
devices::timer::get_time(uint32_t* ticks, uint32_t* subticks)
{
    *ticks = __ticks;
    *subticks = __sub_ticks;
}



void 
devices::timer::initialize(uint32_t freq)
{
    io::process("initializing timer");
    interrupt::install(32, &__timer_cb);

    uint16_t _d = 1193180 / freq;
    outb(0x43, 0x36);
    io::print("   Frequency=%d\n   Subticks/Ticks=%d\n",freq, SUBTICKS_PER_TICKS);

    uint8_t low = (uint8_t) (_d & 0xFF);
    uint8_t high = (uint8_t) ((_d >> 8) & 0xFF);

    outb(0x40, low);
    outb(0x40, high);
}