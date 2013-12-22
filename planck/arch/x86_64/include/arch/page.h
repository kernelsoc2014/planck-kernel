#pragma once

#include <planck/compiler.h>

#define PAGE_SHIFT 12
#define PAGE_SIZE  (_AC(1, ULL) << PAGE_SHIFT)
#define PAGE_MASK  (~(PAGE_SIZE - 1))

#define PT_SHIFT   21
#define PT_SIZE    (_AC(1, ULL) << PT_SHIFT)
#define PT_MASK    (~(PT_SIZE - 1))

#define PD_SHIFT   30
#define PD_SIZE    (_AC(1, ULL) << PD_SHIFT)
#define PD_MASK    (~(PD_SIZE - 1))

#define PDP_SHIFT  39
#define PDP_SIZE   (_AC(1, ULL) << PDP_SHIFT)
#define PDP_MASK   (~(PDP_SIZE - 1))

#define PML4_SHIFT 48
#define PML4_SIZE  (_AC(1, ULL) << PML4_SHIFT)
#define PML4_MASK  (~(PML4_SIZE - 1))

#define PAGE_TABLE_ENTRY_COUNT 512
#define PML4_KERNEL_INDEX 511

#define KERNEL_VIRTUAL_ADDRESS       0xFFFFFFFF80000000
#define KERNEL_PHYSICAL_ADDRESS      0x100000
#define KERNEL_START (KERNEL_VIRTUAL_ADDRESS + KERNEL_PHYSICAL_ADDRESS)
