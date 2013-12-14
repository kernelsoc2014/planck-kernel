#include <arch/arch.h>
#include <planck/kmalloc.h>

void kernel_start(void *args)
{
    // Initialize brk alloc
    kmalloc_initialize();

    arch_init(args);
}
