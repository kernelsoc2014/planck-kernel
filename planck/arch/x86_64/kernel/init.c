#include <arch/arch.h>
#include <arch/segment.h>
#include <arch/trap.h>

void arch_init(void *args)
{
    segment_init();
    trap_init();
}
