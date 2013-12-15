#include <planck/compiler.h>
#include <arch/segment.h>
#include <arch/page.h>

GdtDescriptor BootGdt[GDT_SIZE]
    __initdata __attribute__((aligned(PAGE_SIZE))) = {
    [SEL_TO_INDEX(kKernelCode64)] = MAKE_GDT_DESCRIPTOR(
        0,
        0xfffff,
        kDescriptor64 | kDescriptorG,
        kDescriptorPresent | kDescriptorPrivK | kDescriptorCodeR
    ),
    [SEL_TO_INDEX(kKernelData)] = MAKE_GDT_DESCRIPTOR(
        0,
        0xfffff,
        kDescriptor32 | kDescriptorG,
        kDescriptorPresent | kDescriptorPrivK | kDescriptorDataW
    )
};
