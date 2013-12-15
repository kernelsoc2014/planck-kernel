#pragma once

#include <stdint.h>
#include <stddef.h>
#include <planck/memorymanager.h>

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

#ifndef __ASSEMBLER__

__BEGIN_DECLS

typedef uint64_t MmPml4Entry;
typedef uint64_t MmPdptEntry;
typedef uint64_t MmPdEntry;
typedef uint64_t MmPtEntry;

typedef struct
{
    uintptr_t  Base;
    uintptr_t  Limit;
    size_t     FirstFreeByte;
    size_t     FirstFreeBit;
    uintptr_t *Bitmap;
} PhysicalMemoryMap;

typedef struct MemoryRegionEntry
{
    uintptr_t Base;
    uintptr_t Size;
    MmPdptEntry *Pdpt;
    struct MemoryRegionEntry *APrev, *ANext;
    struct MemoryRegionEntry *SPrev, *SNext;
} MemoryRegionEntry;

typedef struct
{
    uintptr_t Base;
    uintptr_t Limit;
    MemoryRegionEntry *AHead;
    MemoryRegionEntry *SHead;
    MemoryRegionEntry *UHead;
} MemoryRegion;

enum PageFlags
{
    kPagePresent        = 0x1ULL,
    kPageWrite          = 0x2ULL,
    kPageUser           = 0x4ULL,
    kPageWriteThrough   = 0x8ULL,
    kPageNoCache        = 0x10ULL,
    kPageAccessed       = 0x20ULL,
    kPageSuperPage      = 0x80ULL,
    kPageWired          = 0x200ULL,
    kPageNoExecute      = 1ULL << 63
};

void MmPageInitialize();

void MemoryRegionCreate(MemoryRegion *region, uintptr_t base, uintptr_t limit);
uintptr_t MemoryRegionAlloc(MemoryRegion *region, uintptr_t address, size_t count, uint8_t flags);
void MemoryRegionFree(MemoryRegion *region, uintptr_t address, uint64_t count, uint8_t flags);

__END_DECLS

#endif
