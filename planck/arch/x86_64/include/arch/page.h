#pragma once

#include <planck/compiler.h>

#define PAGE_PRESENT _AC(0x1, ULL)
#define PAGE_WRITE   _AC(0x2, ULL)
#define PAGE_USER    _AC(0x4, ULL)
#define PAGE_WTHRU   _AC(0x8, ULL)
#define PAGE_NCACHE  _AC(0x10, ULL)
#define PAGE_REF     _AC(0x20, ULL)
#define PAGE_PS      _AC(0x80, ULL)
#define PAGE_PTA     _AC(0x80, ULL)
#define PAGE_WIRED   _AC(0x200, ULL)
#define PAGE_NX      (_AC(1, ULL) << 63)

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
#define PML4_SELF_INDEX 510

#define KERNEL_VIRTUAL_ADDRESS       0xFFFFFFFF80000000
#define KERNEL_PHYSICAL_ADDRESS      0x100000
#define KERNEL_START (KERNEL_VIRTUAL_ADDRESS + KERNEL_PHYSICAL_ADDRESS)

#ifndef __ASSEMBLER__

#include <stdint.h>

typedef uint64_t        pml4_entry_t;
typedef uint64_t        pdpt_entry_t;
typedef uint64_t        pd_entry_t;
typedef uint64_t        pt_entry_t;
typedef uint64_t        pmap_paddr_t;

#endif
