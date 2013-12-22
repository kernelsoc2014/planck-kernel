#include <planck/compiler.h>
#include <arch/boot.h>
#include <multiboot2.h>

static BootInfo __initdata tbi;

BootInfo *__init MultibootSetup(struct multiboot_tag *tags)
{
    return &tbi;
}
