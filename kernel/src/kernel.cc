#include <kernel/kernel.h>

using namespace x86;
using namespace rlxos::kernel;


extern "C"
void _start(void* multiboot)
{
	descriptor::initialize();

	//vga::set_color(vga::color::BLACK, vga::color::CYAN);
	vga::initialize();
	
	devices::timer::initialize(10);
	
	devices::keyboard::initialize();

	//asm volatile("int $0x3");
	
	shell::initialize();
	for(;;);
}