#include <kernel/kernel.h>

using namespace rlxos::kernel;
using namespace x86;
extern "C" uint8_t   __shell_enabled = 0;
uint8_t   __input_buffer[256];
uint32_t  __input_buffer_loc = 0;
uint8_t   __last_char = 0;
uint8_t   shellEnabled = 0;

// #define SIZE(x) sizeof(x)/sizeof(x[0])

// struct _Command {
//     char id[256];
//     int (*handler)(char*);
// };

// _Command AvaliableCommands[] = {
//     {"help", &_HelpFunc},
//     {"time", &_TimeFunc},
// };

extern "C"
void
__put_char_in_shell(char c)
{
    uint8_t ch = c;
    switch (ch) {
        case '\n':
            __input_buffer[__input_buffer_loc] = '\0';
            __input_buffer_loc = 0;
            vga::write('\n');
            break;

        case '\b':
            if (__input_buffer_loc) {
                __input_buffer_loc--;
                vga::write('\b');
            }
            break;
        
        default:
            __input_buffer[__input_buffer_loc] = ch;
            __input_buffer_loc++;
            vga::write(ch);
            break;
    }

    __last_char = ch;
}


void
__wait_for_input()
{
    while (__last_char != '\n')
    {

    }
    __last_char = 0;
}

void
shell::initialize()
{
    __shell_enabled = 1;
    uint8_t _solved = 0;

    while(1) {
        io::print("\n>> ");
        __wait_for_input();
        _solved = 0;
        io::print("You typed: %s",__input_buffer);
    }
}
