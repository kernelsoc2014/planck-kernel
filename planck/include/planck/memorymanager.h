#pragma once

#include <stdint.h>
#include <planck/compiler.h>
#include <planck/status.h>

__BEGIN_DECLS

typedef enum
{
    kMemoryZoneDefault = 0,
    kMemoryZoneDMA,
    kMemoryZoneNormal,
    kMemoryZoneHeap,
    kMemoryZoneHardware,
    kMemoryZonePaging,
    kMemoryZoneKernel,
    kMemoryZoneMax
} KernelMemoryZone;

typedef enum
{
    kPageNone      = 0,
    kPageReserve   = 1,
    kPageCommit    = 2
} AllocPageFlags;

uintptr_t MmMapPage(KernelMemoryZone zone, uintptr_t address, uintptr_t physicalAddress, uintptr_t size, AllocPageFlags flags);
uintptr_t MmAllocPage(KernelMemoryZone zone, uintptr_t address, uintptr_t size, AllocPageFlags flags);
uintptr_t MmFreePage(KernelMemoryZone zone, uintptr_t address, uintptr_t size);
uintptr_t MmGetPhysicalAddress(KernelMemoryZone zone, uintptr_t address);

__END_DECLS
