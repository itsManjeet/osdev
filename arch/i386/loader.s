MBOOT_PAGE_ALIGN	equ 1 << 0
MBOOT_MEM_INFO		equ 1 << 1
MBOOT_HEADER_MAGIC	equ 0x1BADB002
MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

[GLOBAL _X86_MultiBoot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

; Multboot Header
_X86_MultiBoot:
    dd	MBOOT_HEADER_MAGIC
	dd	MBOOT_HEADER_FLAGS
	dd	MBOOT_CHECKSUM

	dd	_X86_MultiBoot
	dd	code
	dd	bss
	dd	end
	dd	_SysLoader

[GLOBAL _SysLoader]
[EXTERN _start]


; Loader Entry Point
_SysLoader:
    ; push ebx to _KernalStart argument stack
    ; ebx contain pointer to Multiboot structure provided by
    ; Grub
    push ebx    

    ; Clear interrupt
    cli

    ; Load _KernelStart
    call _start

    jmp $


; Global Descriptor
[GLOBAL _X86_GDT_Flush]
_X86_GDT_Flush:
    mov eax, [esp + 4]
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:.flush

.flush:
	ret


; Interrupt Descriptor 
[GLOBAL _X86_IDT_Flush]
_X86_IDT_Flush:
    mov eax, [esp+4]
	lidt [eax]
	ret


%macro X86_ISR_NOERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp _X86_ISR_COMMON
%endmacro

%macro X86_ISR_ERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli
		push byte %1
		jmp _X86_ISR_COMMON
%endmacro

%macro X86_IRQ 2
	[GLOBAL irq%1]
	irq%1:
		cli
		push byte 0
		push byte %2
		jmp _X86_IRQ_COMMON
%endmacro

X86_ISR_NOERRCODE 0
X86_ISR_NOERRCODE 1
X86_ISR_NOERRCODE 2
X86_ISR_NOERRCODE 3
X86_ISR_NOERRCODE 4
X86_ISR_NOERRCODE 5
X86_ISR_NOERRCODE 6
X86_ISR_NOERRCODE 7
X86_ISR_ERRCODE 8
X86_ISR_NOERRCODE 9
X86_ISR_ERRCODE 10
X86_ISR_ERRCODE 11
X86_ISR_ERRCODE 12
X86_ISR_ERRCODE 13
X86_ISR_ERRCODE 14
X86_ISR_NOERRCODE 15
X86_ISR_NOERRCODE 16
X86_ISR_NOERRCODE 17
X86_ISR_NOERRCODE 18
X86_ISR_NOERRCODE 19
X86_ISR_NOERRCODE 20
X86_ISR_NOERRCODE 21
X86_ISR_NOERRCODE 22
X86_ISR_NOERRCODE 23
X86_ISR_NOERRCODE 24
X86_ISR_NOERRCODE 25
X86_ISR_NOERRCODE 26
X86_ISR_NOERRCODE 27
X86_ISR_NOERRCODE 28
X86_ISR_NOERRCODE 29
X86_ISR_NOERRCODE 30
X86_ISR_NOERRCODE 31

X86_IRQ 0, 32
X86_IRQ 1, 33
X86_IRQ 2, 34
X86_IRQ 3, 35
X86_IRQ 4, 36
X86_IRQ 5, 37
X86_IRQ 6, 38
X86_IRQ 7, 39
X86_IRQ 8, 40
X86_IRQ 9, 41
X86_IRQ 10, 42
X86_IRQ 11, 43
X86_IRQ 12, 44
X86_IRQ 13, 45
X86_IRQ 14, 46
X86_IRQ 15, 47


[EXTERN _X86_ISR_CB]
_X86_ISR_COMMON:
    pusha

    push ds
    push es
    push fs
    push gs
    
	mov ax, 0x10
    
	mov ds, ax
    mov fs, ax
    mov gs, ax
    
	mov eax, esp
    push eax
    
	mov eax, _X86_ISR_CB
    call eax
    
	pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
	add esp, 8
    iret
[EXTERN _X86_IRQ_CB]
_X86_IRQ_COMMON:
    pusha
    
	push ds
    push es
    push fs
    push gs
    
	mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
	mov eax, esp
    push eax
    
	mov eax, _X86_IRQ_CB
    call eax
    
	pop eax
    pop gs
    pop fs
    pop es
    pop ds

    popa
    add esp, 8
    iret
