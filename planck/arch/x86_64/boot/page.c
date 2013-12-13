#include <planck/compiler.h>
#include <arch/page.h>

extern pml4_entry_t boot_pml4[PAGE_TABLE_ENTRY_COUNT];
extern pdpt_entry_t boot_pdpt[PAGE_TABLE_ENTRY_COUNT];
extern pd_entry_t boot_ptd[4096];

#define PML4_FLAGS (PAGE_PRESENT | PAGE_WRITE)
#define ID_MAP_PML4(x) [(x)] = (PML4_FLAGS + boot_pdpt),

pml4_entry_t boot_pml4[PAGE_TABLE_ENTRY_COUNT]
    __initdata __attribute__((aligned(PAGE_SIZE))) = {

    [0] = PML4_FLAGS + (pml4_entry_t)boot_pdpt,
    [PML4_KERNEL_INDEX] = PML4_FLAGS + (pml4_entry_t)boot_pdpt
};

#define PDPT_FLAGS (PAGE_PRESENT | PAGE_WRITE)
pdpt_entry_t boot_pdpt[PAGE_TABLE_ENTRY_COUNT]
    __initdata __attribute__((aligned(PAGE_SIZE))) = {

    [0] = PDPT_FLAGS + (pdpt_entry_t)&boot_ptd[0],
    [1] = PDPT_FLAGS + (pdpt_entry_t)&boot_ptd[512],
    [2] = PDPT_FLAGS + (pdpt_entry_t)&boot_ptd[1024],
    [3] = PDPT_FLAGS + (pdpt_entry_t)&boot_ptd[1536],
    [510] = PDPT_FLAGS + (pdpt_entry_t)&boot_ptd[0],
    [511] = PDPT_FLAGS + (pdpt_entry_t)&boot_ptd[512]
};

#define L0(x,n)  x(n)
#define L1(x,n)  L0(x,n-1)     L0(x,n)
#define L2(x,n)  L1(x,n-2)     L1(x,n)
#define L3(x,n)  L2(x,n-4)     L2(x,n)
#define L4(x,n)  L3(x,n-8)     L3(x,n)
#define L5(x,n)  L4(x,n-16)    L4(x,n)
#define L6(x,n)  L5(x,n-32)    L5(x,n)
#define L7(x,n)  L6(x,n-64)    L6(x,n)
#define L8(x,n)  L7(x,n-128)   L7(x,n)
#define L9(x,n)  L8(x,n-256)   L8(x,n)
#define L10(x,n) L9(x,n-512)   L9(x,n)
#define L11(x,n) L10(x,n-1024) L10(x,n)

#define FOR_0_TO_2047(x) L11(x,2047)

#define PDT_FLAGS (PAGE_PS | PAGE_PRESENT | PAGE_WRITE)
#define ID_MAP_2MEG(x) [(x)] = ((((uint64_t)(x)) << 21) | (PDT_FLAGS)),

pd_entry_t boot_ptd[4096]
    __initdata __attribute__((aligned(PAGE_SIZE))) = {
    FOR_0_TO_2047(ID_MAP_2MEG)
};
