#include <arch/arch.h>

void kernel_start(void *args)
{
    arch_init(args);
}
