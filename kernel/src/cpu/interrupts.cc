#include <kernel/kernel.h>

using namespace rlxos::kernel;
using namespace x86;

interrupt::func_t __interrupt_handlers[256];

#define STR(x) #x
void
interrupt::install(uint8_t num, interrupt::func_t handler)
{
    vga::set_color(vga::color::LIGHT_GRAY);
    io::print("* ");
    vga::set_color(vga::color::DARK_GRAY);
    io::print("installed interrupt handler for %d\n",num);
    __interrupt_handlers[num] = handler;
}

char *__exceptions_mesg[] = {
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",
  "Double Fault 007",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault!",
  "Unknown Interrupt",
  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};


extern "C"
void _X86_ISR_CB(rlxos::cpu::registers_t *regs)
{
    io::print("recived interrupt: %d\n",regs->int_no);
    if (__interrupt_handlers[regs->int_no] != 0) {
        interrupt::func_t handler = __interrupt_handlers[regs->int_no];
        handler(regs);
    }
    if (regs->int_no < 32) {

        vga::set_color(vga::color::WHITE);
        io::print("\nEXCEPTION: '%s' (INT:%x ERR:%x) !\n", __exceptions_mesg[regs->int_no], regs->int_no, regs->err_code);
        
        vga::set_color(vga::color::LIGHT_CYAN);
        io::print("\nSystem State:\n");

        vga::set_color(vga::color::DARK_GRAY);

        uint32_t ticks, subticks;
        devices::timer::get_time(&ticks, &subticks);
        io::print("TICKS: %d    SUBTICKS: %d\n",ticks, subticks);
        io::print("DS=%x\n",regs->ds);
        io::print("EDI=%x\tESI=%x\tEBP=%x\tESP=%x\nEBX=%x\tEDX=%x\tECX=%x\tEAX=%x\n", regs->edi, regs->esi, regs->ebp, regs->esp, regs->ebx, regs->edx, regs->ecx, regs->eax);
        io::print("EIP=%x\tCS=%x\nEFLAGS=%x\tUSRESP=%x\nSS=%x\n",regs->eip, regs->cs, regs->eflags, regs->usr_esp, regs->ss);
        for(;;);
    }
}

extern "C"
void _X86_IRQ_CB(rlxos::cpu::registers_t* regs)
{
    if (regs->int_no >= 40)
    {
        outb(0xA0, 020);
    }

    outb(0x20, 0x20);
    
    if (__interrupt_handlers[regs->int_no] != 0)
    {
        interrupt::func_t handler = __interrupt_handlers[regs->int_no];
        handler(regs);
    }
}