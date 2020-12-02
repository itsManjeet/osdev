#ifndef _SERIAL_H
#define _SERIAL_H

#include "../types.h"

static inline void outb(uint16_t prt, uint8_t val)
{
	asm volatile ("outb %1, %0" :: "dN"(prt), "a"(val));
}

static inline uint8_t inb(uint16_t prt)
{
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (prt));
	return ret;
}
static inline uint16_t inw(uint16_t prt)
{
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (prt));
	return ret;
}


#endif