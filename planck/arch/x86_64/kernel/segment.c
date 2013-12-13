#include <arch/segment.h>
#include <arch/task.h>
#include <arch/cpu.h>

static gdt_descriptor_t kernel_gdt[GDT_SIZE];
static descriptor_descriptor64_t kernel_gdtr = { sizeof(kernel_gdt) - 1, (uint64_t)&kernel_gdt };

void segment_set(int seg, uint32_t base, uint32_t limit, uint8_t gran, uint8_t access)
{
    gdt_descriptor_t *g = &kernel_gdt[SEL_TO_INDEX(seg)];

    g->limit_low = limit & 0xffff;
    g->limit_high = (limit >> 16) & 0xf;
    g->base_low = base & 0xffff;
    g->base_med = (base >> 16) & 0xff;
    g->base_high = (base >> 24) & 0xff;
    g->access = access;
    g->granularity = gran;
}

void segment_set64(int seg, uint64_t base, uint64_t limit, uint8_t gran, uint8_t access)
{
    gdt_descriptor64_t *g = (gdt_descriptor64_t *)&kernel_gdt[SEL_TO_INDEX(seg)];

    g->limit_low = limit & 0xFFFF;
    g->base_low = (uint16_t)(base & 0xFFFF);
    g->base_med = (uint8_t)((base >> 16) & 0xFF);
    g->access = access;
    g->limit_high = (limit >> 16) & 0xFF;
    g->granularity = gran;
    g->base_high = (uint8_t)((base >> 24) & 0xFF);
    g->base_top = (uint32_t)(    base >> 32);
}

void segment_init()
{
    uint64_t tss = (uint64_t)&task_kernel_tss;
    uint64_t tss_limit = sizeof(task_kernel_tss) - 1;

    segment_set(KERNEL64_CS, 0, 0xfffff, SZ_64 | SZ_G, ACC_P | ACC_PL_K | ACC_CODE_R);
    segment_set(KERNEL_DS, 0, 0xfffff, SZ_32 | SZ_G, ACC_P | ACC_PL_K | ACC_DATA_W);
    segment_set(USER32_CS, 0, 0xfffff, SZ_32 | SZ_G, ACC_P | ACC_PL_U | ACC_CODE_R);
    segment_set(USER32_DS, 0, 0xfffff, SZ_32 | SZ_G, ACC_P | ACC_PL_U | ACC_DATA_W);
    segment_set(USER64_DS, 0, 0xfffff, SZ_64 | SZ_G, ACC_P | ACC_PL_U | ACC_CODE_R);
    segment_set64(KERNEL_TSS, tss, tss_limit, 0, ACC_P | ACC_PL_K | ACC_TSS);

    lgdt((uintptr_t *)&kernel_gdtr);
    set_tr(KERNEL_TSS);
}
