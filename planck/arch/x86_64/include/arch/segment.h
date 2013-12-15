#pragma once

#define GDT_SIZE 19
#define IDT_SIZE 256

#define SEL_TO_INDEX(s)  ((s) >> 3)

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <planck/compiler.h>
#include <planck/status.h>

#pragma pack(1)

typedef struct
{
    uint16_t Size;
    uint32_t Address;
} DescriptorRegister;

typedef struct
{
    uint16_t Size;
    uint64_t Address;
} DescriptorRegister64;

typedef struct
{
    uint32_t LimitLow : 16;
    uint32_t BaseLow : 16;
    uint32_t BaseMed : 8;
    uint32_t Access : 8;
    uint32_t LimitHigh : 4;
    uint32_t Granularity : 4;
    uint32_t BaseHigh : 8;
} GdtDescriptor;

typedef struct
{
    uint32_t LimitLow : 16;
    uint32_t BaseLow : 16;
    uint32_t BaseMed : 8;
    uint32_t Access : 8;
    uint32_t LimitHigh : 4;
    uint32_t Granularity :4 ;
    uint32_t BaseHigh : 8;
    uint32_t BaseTop : 32;
    uint32_t Reserved : 32;
} GdtDescriptor64;

typedef struct
{
    uint32_t OffsetLow : 16;
    uint32_t Selector : 16;
    uint32_t WordCount : 8;
    uint32_t Access : 8;
    uint32_t OffsetHigh : 16;
} IdtGate;

typedef struct
{
    uint32_t OffsetLow : 16;
    uint32_t Selector : 16;
    uint32_t IST : 3;
    uint32_t Zeroes : 5;
    uint32_t Access : 8;
    uint32_t OffsetHigh : 16;
    uint32_t OffsetTop : 32;
    uint32_t Reserved : 32;
} IdtGate64;

typedef enum
{
    kNullSegment  = 0x00,
    kKernelCode64 = 0x08,
    kKernelData   = 0x10,
    kUserCode32   = 0x18 | 3,
    kUserData     = 0x20 | 3,
    kUserCode64   = 0x28 | 3,
    kSystemTss    = 0x30
} KernelSegments;

typedef enum
{
    kDescriptor64 = 0x2,
    kDescriptor32 = 0x4,
    kDescriptorG  = 0x8
} DescriptorSize;

typedef enum
{
    kDescriptorA         = 0x01,
    kDescriptorTssBusy   = 0x02,
    kDescriptorTss       = 0x09,
    kDescriptorInterrupt = 0x0e,
    kDescriptorTrap      = 0x0f,
    kDescriptorUser      = 0x10,
    kDescriptorData      = 0x10,
    kDescriptorDataW     = 0x12,
    kDescriptorDataE     = 0x14,
    kDescriptorDataEW    = 0x16,
    kDescriptorCode      = 0x18,
    kDescriptorCodeR     = 0x1A,
    kDescriptorCodeC     = 0x1C,
    kDescriptorCodeCR    = 0x1E,
    kDescriptorPrivK     = 0x00,
    kDescriptorPrivU     = 0x60,
    kDescriptorPresent   = 0x80
} DescriptorAccess;

#pragma pack()

#define MAKE_GDT_DESCRIPTOR(base, lim, gran, acc) { \
    .LimitLow = lim & 0xffff, \
    .LimitHigh = (lim >> 16) & 0xf, \
    .BaseLow = base & 0xffff, \
    .BaseMed = (base >> 16) & 0xff, \
    .BaseHigh = (base >> 24) & 0xff, \
    .Access = acc, \
    .Granularity = gran \
}

__BEGIN_DECLS

void AcSegmentInitialize();

__END_DECLS

#endif
