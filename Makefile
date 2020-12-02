
ARCH=i386

ARCH_DIR=arch/$(ARCH)

include $(ARCH_DIR)/make.config

CFLAGS= -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -I kernel/include -I $(ARCH_DIR)
CXXFLAGS = $(CFLAGS) -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive -Wno-write-strings -Wno-narrowing
LDFLAGS=  -T $(ARCH_DIR)/link.ld
ASFLAGS = -f elf32

KERNEL_SRC_DIR=kernel/src

KERNEL_SRC_OBJS=\
$(KERNEL_SRC_DIR)/kernel.o \
$(KERNEL_SRC_DIR)/io.o \
$(KERNEL_SRC_DIR)/shell.o \
$(KERNEL_SRC_DIR)/sys/memory.o \
$(KERNEL_SRC_DIR)/devices/timer.o \
$(KERNEL_SRC_DIR)/devices/keyboard.o \
$(KERNEL_SRC_DIR)/cpu/interrupts.o

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
$(KERNEL_SRC_OBJS)

all: kernel/rlxnix

clean:
	rm $(ARCH_DIR)/*.o kernel/src/*.o kernel/src/*/*.o
	rm kernel/rlxnix

kernel/rlxnix: $(KERNEL_OBJS) $(ARCH_DIR)/link.ld
	ld -m elf_i386 $(LDFLAGS) -o kernel/rlxnix $(KERNEL_OBJS)
	
.s.o:
	nasm $(ASFLAGS) $<
	
run: kernel/rlxnix
	qemu-system-x86_64 -kernel kernel/rlxnix -m 1024
