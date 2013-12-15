#include <arch/segment.h>
#include <arch/task.h>
#include <arch/cpu.h>

static GdtDescriptor KernelGdt[GDT_SIZE];
static DescriptorRegister64 KernelGdtr = { sizeof(KernelGdt) - 1, (uint64_t)&KernelGdt };

static void AcSegmentSet(int seg, uint32_t base, uint32_t limit, uint8_t gran, uint8_t access)
{
    GdtDescriptor *g = &KernelGdt[SEL_TO_INDEX(seg)];

    g->LimitLow = limit & 0xffff;
    g->LimitHigh = (limit >> 16) & 0xf;
    g->BaseLow = base & 0xffff;
    g->BaseMed = (base >> 16) & 0xff;
    g->BaseHigh = (base >> 24) & 0xff;
    g->Access = access;
    g->Granularity = gran;
}

static void AcSegmentSet64(int seg, uint64_t base, uint64_t limit, uint8_t gran, uint8_t access)
{
    GdtDescriptor64 *g = (GdtDescriptor64 *)&KernelGdt[SEL_TO_INDEX(seg)];

    g->LimitLow = limit & 0xFFFF;
    g->BaseLow = (uint16_t)(base & 0xFFFF);
    g->BaseMed = (uint8_t)((base >> 16) & 0xFF);
    g->Access = access;
    g->LimitHigh = (limit >> 16) & 0xFF;
    g->Granularity = gran;
    g->BaseHigh = (uint8_t)((base >> 24) & 0xFF);
    g->BaseTop = (uint32_t)(base >> 32);
}

void AcSegmentInitialize()
{
    uint64_t tss = (uint64_t)&TaskKernelTss;
    uint64_t tss_limit = sizeof(TaskKernelTss) - 1;

    AcSegmentSet(kKernelCode64,  0,   0xfffff, kDescriptor64 | kDescriptorG, kDescriptorPresent | kDescriptorPrivK | kDescriptorCodeR);
    AcSegmentSet(kKernelData,    0,   0xfffff, kDescriptor32 | kDescriptorG, kDescriptorPresent | kDescriptorPrivK | kDescriptorDataW);
    AcSegmentSet(kUserCode32,    0,   0xfffff, kDescriptor32 | kDescriptorG, kDescriptorPresent | kDescriptorPrivU | kDescriptorCodeR);
    AcSegmentSet(kUserData,      0,   0xfffff, kDescriptor32 | kDescriptorG, kDescriptorPresent | kDescriptorPrivU | kDescriptorDataW);
    AcSegmentSet(kUserCode64,    0,   0xfffff, kDescriptor64 | kDescriptorG, kDescriptorPresent | kDescriptorPrivU | kDescriptorCodeR);
    AcSegmentSet64(kSystemTss, tss, tss_limit, 0,                              kDescriptorPresent | kDescriptorPrivK | kDescriptorTss);

    lgdt((uintptr_t *)&KernelGdtr);
    set_tr(kSystemTss);
}
