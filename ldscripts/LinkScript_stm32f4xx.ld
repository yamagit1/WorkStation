/*==================================================================
 *  Author  : YAMA team 
 *  email   : yamateamhaui@gmail.com
 *  address : Ha Noi University 
 *  ( Nhon - Bac Tu liem - Ha Noi - Viet Nam)
 *==================================================================*/

/*==================================================================
 * output format file
 * default : elf32-littlearm
 * can select in command-line optional
 *  + -EB : elf32-bigarm
 *  + -EL : elf32-littlearm
 *==================================================================*/
OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

/*==================================================================
 * Internal Memory Map - can modify with device
 * FLASH     : address - 0x08000000, length - 1M
 * SRAM      : address - 0x20000000, length - 128kb
 * SRAM_CCM  : address - 0x10000000, length - 64kb
 * total SRAM: up to 198kb
 *==================================================================*/

MEMORY
{
	FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 0x00100000
	SRAM (rwx) 	   : ORIGIN = 0x20000000, LENGTH = 0x00020000
	SRAM_CCM (rwx) : ORIGIN = 0x10000000, LENGTH = 0x00010000
}

_eram = 0x20000000 + 0x00020000;
/*==================================================================
 * command SECTIONS using type B 
 * +---------------------------------------------------+
   |   Section     |   type A  |   type B  |   type C  |
   +===================================================+
   |   .text       |   RAM     |   ROM     |   ROM     |
   |   .rodata     |   RAM     |   ROM     |   ROM2    |
   |   .data       |   RAM     |   RAM     |   RAM/ROM2|
   |   .bss        |   RAM     |   RAM     |   RAM     |
   +---------------------------------------------------+
 *==================================================================*/
SECTIONS
{
	.text :
	{
		_flash_s = .;
/*==================================================================
 * Section .isr_vector define in startup_stm32f4xx.c
 * define interrupt handle
 *==================================================================*/
		KEEP(*(.isr_vector))
		*(.text*)
		_flash_e = .;
		
		KEEP(*(.init))
		KEEP(*(.fini))
/*==================================================================
 * section .ctors
 * define construction
 *==================================================================*/
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)
/*==================================================================
 * section .dtors
 * define construction
 *==================================================================*/
		*crtbegin.o(.dtors)
		*crtbegin?.o(.dtors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
		*(SORT(.dtors.*))
		*(.dtors)
		
		*(.rodata*)
		
		KEEP(*(.eh_fram e*))
	} > FLASH 
	
	.ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH 
	
	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH 
	__exidx_end = .;
	__etext = .;
	
/*==================================================================
 *  _sidata is used in startup code *
 *==================================================================*/
	_sidata = __etext;
	
	.data : AT (__etext)
	{
		__data_start__ = .;

/*==================================================================
 *  _sdata is used in startup code *
 *==================================================================*/
		_sdata = __data_start__;
		
		*(vtable)
		*(.data*)
		
		. = ALIGN(4);
/*==================================================================
 *      preinit data
 *==================================================================*/
		
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		
		. = ALIGN(4);
/*==================================================================
 *      init data 
 *==================================================================*/
		
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
		
		. = ALIGN(4);
/*==================================================================
 *      finit data
 *==================================================================*/
		
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
		
		KEEP(*(.jcr*))
		. = ALIGN(4);
/*==================================================================
 *      All data end
 *==================================================================*/	
		__data_end__ = .;
		
/*==================================================================
 * _edata is used in startup code 
 *==================================================================*/
		_edata = __data_end__;
	} > SRAM 
	
	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		_sbss = __bss_start__;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		_ebss = __bss_end__;
	} > SRAM 
		
	.heap (COPY):
	{
		_Heap_Begin = .;
		__end__ = .;
		_end = __end__;
		end = __end__;
		*(.heap*)
		__HeapLimit = .;
		_Heap_Limit = .;
	} > SRAM 
	
/*==================================================================
 * .stack_dummy section doesn't contains any symbols. It is only
 * used for linker to calculate size of stack sections, and assign
 * values to stack symbols later
 *==================================================================*/
	
	.co_stack (NOLOAD):
	{
		. = ALIGN(8);
		*(.co_stack .co_stack.*)
	} > SRAM 
	
/*==================================================================
 * Set stack top to end of ram , and stack limit move down by
 * size of stack_dummy section
 *==================================================================*/
	
	__StackTop = ORIGIN(SRAM ) + LENGTH(SRAM );
	__StackLimit = __StackTop - SIZEOF(.co_stack);
	PROVIDE(__stack = __StackTop);
	
/*==================================================================
 * Check if data + heap + stack exceeds ram  limit
 *==================================================================*/
	
	ASSERT(__StackLimit >= __HeapLimit, "region ram  overflowed with stack")
}