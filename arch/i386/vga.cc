#include <kernel/kernel.h>
#include <vga.h>

using namespace x86;
using namespace rlxos::kernel;

static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;
static uint16_t *buffer = (uint16_t*) 0xB8000;
static uint8_t background = vga::color::BLACK,
			   foreground = vga::color::LIGHT_GRAY;


void vga::set_color(vga::color::type bg, vga::color::type fg)
{
	background = bg;
	foreground = fg;
}

void vga::set_color(vga::color::type fg)
{
	foreground = fg;
}

void vga::initialize()
{
	vga::clear();
	io::process("initializing vga");
	io::print("   Buffer=%x\n   BG=%x FG=%x\n",buffer, background,foreground);
}

void vga::update_cursor()
{
	uint16_t curloc = cursor_y * 80 + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, curloc >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, curloc);
}

void vga::clear()
{
	uint8_t color_attr = background << 4 | foreground & 0xFF;
	for (int i = 0; i < 80 * 25; i++)
		buffer[i] = (uint16_t)' ' | ((uint16_t)color_attr << 8);

	cursor_x = 0;
	cursor_y = 0;
	vga::update_cursor();
}

void vga::write(char ch)
{
	uint16_t c = ch;
	uint8_t _col_attr = (background << 4) | (foreground & 0x0F);
	uint16_t _attr = _col_attr << 8;

	if (c == 0x08 && cursor_x) // backspace
	{
		cursor_x--;
		buffer[cursor_y * 80 + cursor_x] = ' ' | _attr;
	}
	else if (c == 0x09) // tab
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	else if (c == '\r')
		cursor_x = 0;

	else if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}

	else if (c >= ' ')
	{
		buffer[cursor_y * 80 + cursor_x] = c | _attr;
		cursor_x++;
	}

	if (cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y++;
	}

	if (cursor_y >= 25)
	{
		vga::clear();
	}

	vga::update_cursor();
}

void vga::write(const char *c, uint32_t size)
{
	int i = 0;
	while (i < size)
	{
		vga::write(c[i++]);
	}
}

void vga::write(const char *c)
{
	int i = 0;
	while (c[i])
		vga::write(c[i++]);
}