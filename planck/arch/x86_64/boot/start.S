#include <planck/compiler.h>
#include <arch/boot.h>

.section .init
boot_stack:
    .fill BOOT_STACK_SIZE, 1, 0
boot_stack_end:

.code32
Entry(startup_64)
    cld
    movl $boot_stack_end, %esp



    hlt




