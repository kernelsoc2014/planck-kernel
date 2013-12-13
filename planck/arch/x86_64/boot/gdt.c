#include <planck/compiler.h>
#include <arch/segment.h>
#include <arch/page.h>

gdt_descriptor_t boot_gdt[GDT_SIZE]
    __initdata __attribute__((aligned(PAGE_SIZE))) = {
    [SEL_TO_INDEX(KERNEL64_CS)] = MAKE_GDT_DESCRIPTOR(
        0,
        0xfffff,
        SZ_64 | SZ_G,
        ACC_P | ACC_PL_K | ACC_CODE_R
    ),
    [SEL_TO_INDEX(KERNEL_DS)] = MAKE_GDT_DESCRIPTOR(
        0,
        0xfffff,
        SZ_32 | SZ_G,
        ACC_P | ACC_PL_K | ACC_DATA_W
    )
};
