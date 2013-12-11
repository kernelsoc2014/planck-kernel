#include <arch/planck_kernel.lds.h>
#include <arch/page.h>

OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(phys_startup_64)

PHDRS {
    text PT_LOAD FLAGS(5);
    data PT_LOAD FLAGS(6);
    init PT_LOAD FLAGS(7);
}

SECTIONS
{
    . = KERNEL_START;

    phys_startup_64 = startup_64 - KERNEL_VIRTUAL_ADDRESS;

    . = ALIGN(PAGE_SIZE);
    .text : AT(ADDR(.text) - KERNEL_VIRTUAL_ADDRESS) {
        __text_base = .;
        *(.multiboot)
        *(.text)
        __text_limit = .;
    } :text

    . = ALIGN(PAGE_SIZE);
    .rodata : AT(ADDR(.rodata) - KERNEL_VIRTUAL_ADDRESS) {
        __rodata_base = .;
        *(.rodata)
        *(.rodata.*)
        __rodata_limit = .;
    }

    . = ALIGN(PAGE_SIZE);
    .bss : AT(ADDR(.bss) - KERNEL_VIRTUAL_ADDRESS) {
        __bss_base = .;
        *(.bss)
        __bss_limit = .;
    }

    . = ALIGN(PAGE_SIZE);
    .brk : AT(ADDR(.brk) - KERNEL_VIRTUAL_ADDRESS) {
        __brk_base = .;
        __brk_base_pa = . - KERNEL_VIRTUAL_ADDRESS;
        . += 4 + 64 * 1024;
        __brk_limit = .;
    }

    . = ALIGN(PAGE_SIZE);
    .init . - KERNEL_VIRTUAL_ADDRESS : AT(ADDR(.init) - KERNEL_VIRTUAL_ADDRESS) {
        __init_base = .;
        *(.init)
        *(.init.*)
        __init_limit = .;
    } :init
}
