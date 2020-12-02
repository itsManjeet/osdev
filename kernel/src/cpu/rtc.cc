#include <kernel/cpu/rtc.h>

using namespace rlxos::cpu;

rtc::data_t
rtc::read()
{
    rtc::data_t _rt;

    _rt.sec   = get_register(0x00);
    _rt.min   = get_register(0x02);
    _rt.hour  = get_register(0x04);
    _rt.day   = get_register(0x07);
    _rt.month = get_register(0x08);
    _rt.year  = get_register(0x09);

    /* converting BCD to binary if ?? */
    if (!(get_register(0x0B) & 0x04))
    {
        _rt.sec  = (_rt.sec  & 0x0F) + ((_rt.sec / 16) * 10);
        _rt.min  = (_rt.min  & 0x0F) + ((_rt.min / 16) * 10);
        _rt.hour = ((_rt.hour & 0x0F) + (((_rt.hour & 0x70)/16)*10)) | (_rt.hour & 0x80); 
    }

    return _rt;
}

