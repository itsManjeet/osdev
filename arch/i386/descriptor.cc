#include "descriptor.h"
#include <kernel/kernel.h>

using namespace x86::descriptor;
using namespace rlxos::kernel;

extern "C" void _X86_GDT_Flush(uint32_t);
extern "C" void _X86_IDT_Flush(uint32_t);

gdt::entry_t __gdt_entries[5];
gdt::pointer_t __gdt_ptr;

idt::entry_t __idt_entries[256];
idt::pointer_t __idt_pointer;

extern "C" void isr0 ();
extern "C" void isr1 ();
extern "C" void isr2 ();
extern "C" void isr3 ();
extern "C" void isr4 ();
extern "C" void isr5 ();
extern "C" void isr6 ();
extern "C" void isr7 ();
extern "C" void isr8 ();
extern "C" void isr9 ();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

static void __get_set_gate(int32_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    __gdt_entries[n].base_low = (base & 0xFFFF);
    __gdt_entries[n].base_middle = (base >> 16) & 0xFF;
    __gdt_entries[n].base_high = (base >> 24) & 0xFF;

    __gdt_entries[n].limit_low = (limit & 0xFFFF);
    __gdt_entries[n].granulartiy = (limit >> 16) & 0x0F;

    __gdt_entries[n].granulartiy |= gran & 0xF0;
    __gdt_entries[n].access = access; 
}

static void __gdt_initialize()
{
    __gdt_ptr.limit = (sizeof(gdt::entry_t) * 5) - 1;
    __gdt_ptr.base  = (uint32_t) &__gdt_entries;

    __get_set_gate(0,   0,  0,          0,      0);         // Null Segment
    __get_set_gate(1,   0,  0xFFFFFFFF, 0x9A,   0xCF);      // Kernel Code Segment
    __get_set_gate(2,   0,  0xFFFFFFFF, 0x92,   0xCF);      // Kernel Data Segment
    __get_set_gate(3,   0,  0xFFFFFFFF, 0xFA,   0xCF);      // UserMode Code Segment
    __get_set_gate(4,   0,  0xFFFFFFFF, 0xF2,   0xCF);      // UserMode Data Segment

    _X86_GDT_Flush((uint32_t)&__gdt_ptr);
}

static void __idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    __idt_entries[num].base_lower = base & 0xFFFF;
    __idt_entries[num].base_high  = (base >> 16) & 0xFFFF;

    __idt_entries[num].selector  = sel;
    __idt_entries[num].zero      = 0;
    __idt_entries[num].flags     = flags;
}

static void __idt_initialize()
{
    __idt_pointer.limit = sizeof(idt::entry_t) * 256 - 1;
    __idt_pointer.base  = (uint32_t)&__idt_entries;

    rlxos::kernel::memory::set((unsigned char*)&__idt_entries, 0, sizeof(idt::entry_t) * 256);

    /*
     * Remapping Interrupt Descriptor table
     * */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);


    __idt_set_gate(0,  (uint32_t)isr0 , 0x08, 0x8E);
    __idt_set_gate(1,  (uint32_t)isr1 , 0x08, 0x8E);
    __idt_set_gate(2,  (uint32_t)isr2 , 0x08, 0x8E);
    __idt_set_gate(3,  (uint32_t)isr3 , 0x08, 0x8E);
    __idt_set_gate(4,  (uint32_t)isr4 , 0x08, 0x8E);
    __idt_set_gate(5,  (uint32_t)isr5 , 0x08, 0x8E);
    __idt_set_gate(6,  (uint32_t)isr6 , 0x08, 0x8E);
    __idt_set_gate(7,  (uint32_t)isr7 , 0x08, 0x8E);
    __idt_set_gate(8,  (uint32_t)isr8 , 0x08, 0x8E);
    __idt_set_gate(9,  (uint32_t)isr9 , 0x08, 0x8E);
    __idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    __idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    __idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    __idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    __idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    __idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    __idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    __idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    __idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    __idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    __idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    __idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    __idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    __idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    __idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    __idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    __idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    __idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    __idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    __idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    __idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    __idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    __idt_set_gate(32, (uint32_t)irq0 , 0x08, 0x8E);
    __idt_set_gate(33, (uint32_t)irq1 , 0x08, 0x8E);
    __idt_set_gate(34, (uint32_t)irq2 , 0x08, 0x8E);
    __idt_set_gate(35, (uint32_t)irq3 , 0x08, 0x8E);
    __idt_set_gate(36, (uint32_t)irq4 , 0x08, 0x8E);
    __idt_set_gate(37, (uint32_t)irq5 , 0x08, 0x8E);
    __idt_set_gate(38, (uint32_t)irq6 , 0x08, 0x8E);
    __idt_set_gate(39, (uint32_t)irq7 , 0x08, 0x8E);
    __idt_set_gate(40, (uint32_t)irq8 , 0x08, 0x8E);
    __idt_set_gate(41, (uint32_t)irq9 , 0x08, 0x8E);
    __idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    __idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    __idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    __idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    __idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    __idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

    _X86_IDT_Flush((uint32_t)&__idt_pointer);

}

using namespace rlxos::kernel;
extern interrupt::func_t __interrupt_handlers[];

void
x86::descriptor::initialize()
{
    __gdt_initialize();
    __idt_initialize();

    rlxos::kernel::memory::set((unsigned char*)&__interrupt_handlers, 0, sizeof(interrupt::func_t) * 256);
    asm volatile("sti");
}

