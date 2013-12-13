#include <arch/planck_kernel.lds.h>
#include <arch/page.h>

OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(startup_64)
/*
PHDRS {
    text PT_LOAD FLAGS(5);
    data PT_LOAD FLAGS(6);
    init PT_LOAD FLAGS(7);
}*/

/*#undef KERNEL_VIRTUAL_ADDRESS
#define KERNEL_VIRTUAL_ADDRESS 0

#undef KERNEL_START
#define KERNEL_START 0x100000*/

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
        __rodata_base = .;
        *(.data)
        __rodata_limit = .;
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
        . += 4 + 80 * 1024;
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
