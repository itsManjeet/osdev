#ifndef _RLX_SHELL_H
#define _RLX_SHELL_H

namespace rlxos::kernel::shell {
    void initialize();
    void put_char(char c);
    int is_enabled();
}


#endif