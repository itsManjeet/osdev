#ifndef _RLX_REGS_H
#define _RLX_REGS_H

#include "../types.h"

namespace rlxos::cpu {
    struct registers_t {
        uint32_t ds;
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
        uint32_t int_no, err_code;
        uint32_t eip, cs, eflags, usr_esp, ss;
    };
}
#endif