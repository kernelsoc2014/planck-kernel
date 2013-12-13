#include <planck/compiler.h>
#include <arch/boot.h>
#include <multiboot2.h>

static bootinfo_t __initdata tbi;

bootinfo_t *__init multiboot_setup(struct multiboot_tag *tags)
{
    return &tbi;
}
