#include <arch/arch.h>
#include <planck/kmalloc.h>

void KiKernelStart(void *bootArguments)
{
    KiAllocInitialize();

    AcInitialize(bootArguments);
}
