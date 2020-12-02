#include <kernel/kernel.h>

using namespace rlxos::kernel;

#define READ_PORT 0x60

unsigned char __key_map[128] = {
  0,  
  27, 
  '1', 
  '2', 
  '3', 
  '4', 
  '5', 
  '6', 
  '7', 
  '8',	
  '9', 
  '0',
  '-', 
  '=', 
  '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 
  'w', 
  'e', 
  'r',
  't', 
  'y', 
  'u', 
  'i', 
  'o', 
  'p', 
  '[', 
  ']', 
  '\n',	/* Enter key */
    0,  /* 29   - Control */
  'a', 
  's', 
  'd', 
  'f', 
  'g', 
  'h', 
  'j', 
  'k', 
  'l', 
  ';',
  '\'', 
  '`',   
  0,		/* Left shift */
 '\\', 
  'z', 
  'x', 
  'c', 
  'v', 
  'b', 
  'n',
  'm', 
  ',', 
  '.', 
  '/',   
  0,				/* Right shift */
  '*',
  0,	/* Alt */
  ' ',	/* Space bar */
  0,	/* Caps lock */
  0,	/* 59 - F1 key ... > */
  0,  
  0,   
  0,  
  0,   
  0,   
  0,   
  0,   
  0,
  0,	/* < ... F10 */
  0,	/* 69 - Num lock*/
  0,	/* Scroll Lock */
  0,	/* Home key */
  '\xDD',	/* Up Arrow */
  0,	/* Page Up */
  '-',
  0,	/* Left Arrow */
  0,
  0,	/* Right Arrow */
  '+',
  0,	/* 79 - End key*/
  0,	/* Down Arrow */
  0,	/* Page Down */
  0,	/* Insert Key */
  0,	/* Delete Key */
  0,   
  0,   
  0,
  0,	/* F11 Key */
  0,	/* F12 Key */
  0,	/* All other keys are undefined */
};

//extern "C" uint8_t __shell_enabled;
//extern "C" void __put_char_in_shell(char c);

static 
void __kernel_cb(rlxos::cpu::registers_t) {
    unsigned char scanCode = inb(READ_PORT);

    
    //io::print("Keycode: %d\n",scanCode);
    if (scanCode & 0x80) {
      //io::print("Shift press");
    } else {
        x86::vga::write(__key_map[scanCode]);
        //io::print("keypress");

    }
}

void
devices::keyboard::initialize()
{
    io::process("initializing keyboard");
    io::print("   Read Port=%x\n",READ_PORT);
    interrupt::install(33, &__kernel_cb);
}