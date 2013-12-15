#include <arch/planck_kernel.lds.h>
#include <arch/page.h>

OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(Startup64)

SECTIONS
{
    . = KERNEL_START;

    .text ALIGN(PAGE_SIZE) : AT(ADDR(.text) - KERNEL_VIRTUAL_ADDRESS)
    {
        __text_base = .;
        *(.multiboot)
        *(.text)
        __text_limit = .;
    }

    .data ALIGN(PAGE_SIZE) : AT(ADDR(.data) - KERNEL_VIRTUAL_ADDRESS)
    {
        __data_base = .;
        *(.data)
        __data_limit = .;
    }

    .rodata ALIGN(PAGE_SIZE) : AT(ADDR(.rodata) - KERNEL_VIRTUAL_ADDRESS)
    {
        __rodata_base = .;
        *(.rodata)
        *(.rodata.*)
        __rodata_limit = .;
    }

    .bss ALIGN(PAGE_SIZE) : AT(ADDR(.bss) - KERNEL_VIRTUAL_ADDRESS)
    {
        __bss_base = .;
        *(.bss)
        __bss_limit = .;
    }

    .brk ALIGN(PAGE_SIZE) : AT(ADDR(.brk) - KERNEL_VIRTUAL_ADDRESS)
    {
        __brk_base = .;
        . += 64 * 1024;
        __brk_limit = .;
    }

    .init . - KERNEL_VIRTUAL_ADDRESS : AT(ADDR(.init))
    {
        __init_base = .;
        *(.init)
        *(.init.*)
        __init_limit = .;
    }

    /DISCARD/ :
    {
        *(.eh_frame)
    }
}
