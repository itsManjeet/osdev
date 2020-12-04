#include <kernel/kernel.h>
#include <kernel/cpu/rtc.h>

using namespace rlxos::kernel;
using namespace x86;
extern "C" uint8_t   __shell_enabled = 0;
uint8_t   __input_buffer[256];
uint32_t  __input_buffer_loc = 0;
char   __last_char;
uint8_t   shellEnabled = 0;

#define SIZE(x) sizeof(x)/sizeof(x[0])
struct __commands_t {
    char id[256];
    char desc[1024];
    int (*handler)(char*);
};

int __help_cmd(char* cmd);

int __time_cmd(char* cmd)
{
    auto data = rlxos::cpu::rtc::read();
    io::print("Time: %d:%d:%d %d/%d/%d\n",data.hour, data.min, data.sec, data.day, data.month, data.year);
}
__commands_t __commands[] = {
    {"help","Print this help message", &__help_cmd},
    {"time","Print current time acc. UTC", &__time_cmd},
};

int __help_cmd(char* cmd)
{
    io::print("\nrlxos interactive shell\nUsage:\n");
    for(int i = 0; i < SIZE(__commands); i++) {
        io::print("   %s \t\t %s\n",__commands[i].id, __commands[i].desc);
    }
}



void
shell::put_char(char c)
{
    if (c == '\n') {
        __input_buffer[__input_buffer_loc++] = '\0';
        __input_buffer_loc = 0;
        vga::write('\n');
    } else if (c == '\b') {
        if (__input_buffer_loc) {
            __input_buffer_loc--;
            vga::write('\b');
        }
    } else {
        __input_buffer[__input_buffer_loc] = c;
        __input_buffer_loc++;
        vga::write(c);
    }

    __last_char = c;
}


void
__wait_for_input()
{
    __last_char == 0;
    uint32_t _x = 0;
    while (__last_char != '\n') {
        _x += __last_char;
    }
    __last_char = 0;
}

int
shell::is_enabled()
{
    return __shell_enabled;
}

void
shell::initialize()
{
    __shell_enabled = 1;
    uint8_t _solved = 0;

    while(1) {
        vga::set_color(vga::color::WHITE);
        io::print("\n>> ");
        __wait_for_input();
        _solved = 0;
        vga::set_color(vga::color::LIGHT_GRAY);
        for(int i = 0; i < SIZE(__commands); i++) {
            if (!memory::cmp((const uint8_t*)__commands[i].id, __input_buffer)) {
                __commands[i].handler((char*)__input_buffer);
                break;
            }
        }
    }
}
