#include <planck/compiler.h>
#include <arch/segment.h>
#include <arch/page.h>

struct real_descriptor kernel_master_gdt[GDT_SIZE]
    __initdata __attribute__((aligned(PAGE_SIZE))) = {
    [SEL_TO_INDEX(KERNEL32_CS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
        SZ_32 | SZ_G,
        ACC_P | ACC_PL_K | ACC_CODE_R
    ),
    [SEL_TO_INDEX(KERNEL_DS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
        SZ_32 | SZ_G,
        ACC_P | ACC_PL_K | ACC_DATA_W
    ),
    [SEL_TO_INDEX(KERNEL64_CS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
        SZ_64 | SZ_G,
        ACC_P | ACC_PL_K | ACC_CODE_R
    ),
    [SEL_TO_INDEX(KERNEL64_SS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
        SZ_32 | SZ_G,
        ACC_P | ACC_PL_K | ACC_DATA_W
    ),
    [SEL_TO_INDEX(USER_CS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
         SZ_32 | SZ_G,
        ACC_P | ACC_PL_U | ACC_CODE_R
    ),
    [SEL_TO_INDEX(USER_DS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
        SZ_32 | SZ_G,
        ACC_P | ACC_PL_U | ACC_DATA_W
    ),
    [SEL_TO_INDEX(USER64_CS)] = MAKE_REAL_DESCRIPTOR(
        0,
        0xfffff,
        SZ_64 | SZ_G,
        ACC_P | ACC_PL_U | ACC_CODE_R
    )
};
