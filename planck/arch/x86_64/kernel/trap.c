#include <arch/trap.h>
#include <arch/cpu.h>
#include <arch/segment.h>

typedef struct
{
    uint64_t    Address;
    uint32_t    Segment  : 20;
    uint32_t    IST      : 4;
    uint32_t    Access   : 8;
    uint32_t    Reserved : 32;
} IdtFake;

#define kIntrGate (kDescriptorPresent | kDescriptorPrivK | kDescriptorInterrupt)
#define uIntrGate (kDescriptorPresent | kDescriptorPrivU | kDescriptorInterrupt)

#define TRAP(n, name)             extern void *name ;
#define TRAP_ERR(n, name)         extern void *name ;
#define TRAP_SPC(n, name)         extern void *name ;
#define TRAP_IST1(n, name)        extern void *name ;
#define TRAP_IST2(n, name)        extern void *name ;
#define INTERRUPT(n)              extern void *Interrupt##n;
#define USER_TRAP(n, name)        extern void *name ;
#define USER_TRAP_SPC(n, name)    extern void *name;

#include "idttable.h"

#undef TRAP
#undef TRAP_ERR
#undef TRAP_SPC
#undef TRAP_IST1
#undef TRAP_IST2
#undef INTERRUPT
#undef USER_TRAP
#undef USER_TRAP_SPC

#define TRAP(n, name)      \
    [n] = {                \
        (uintptr_t)&name,  \
        kKernelCode64,     \
        0,                 \
        kIntrGate,         \
        0                  \
    },

#define TRAP_ERR TRAP
#define TRAP_SPC TRAP

#define TRAP_IST1(n, name) \
    [n] = {                \
        (uintptr_t)&name,  \
        kKernelCode64,     \
        1,                 \
        kIntrGate,         \
        0                  \
    },

#define TRAP_IST2(n, name) \
    [n] = {                \
        (uintptr_t)&name,  \
        kKernelCode64,     \
        2,                 \
        kIntrGate,         \
        0                  \
    },

#define INTERRUPT(n)              \
    [n] = {                       \
        (uintptr_t)&Interrupt##n, \
        kKernelCode64,            \
        0,                        \
        kIntrGate,                \
        0                         \
    },

#define USER_TRAP(n, name) \
    [n] = {                \
        (uintptr_t)&name,  \
        kKernelCode64,     \
        0,                 \
        uIntrGate,         \
        0                  \
    },

#define USER_TRAP_SPC USER_TRAP

static IdtFake KernelFakeIdt[IDT_SIZE] = {
#include "idttable.h"
};

static IdtGate64 KernelIdt[IDT_SIZE];
static DescriptorRegister64 KernelIdtr = { sizeof(KernelIdt) - 1, (uint64_t)&KernelIdt };

void AcTrapInitialize()
{
    for (int i = 0; i < IDT_SIZE; i++)
    {
        IdtFake *f = &KernelFakeIdt[i];
        IdtGate64 *g = &KernelIdt[i];

        g->OffsetLow = (uint16_t)(f->Address & 0xFFFF);
        g->Selector = f->Segment & 0xFFFF;
        g->IST = f->IST & 0x7;
        g->Access = f->Access;
        g->OffsetHigh = (uint16_t)((f->Address >> 16) & 0xFFFF);
        g->OffsetTop = (uint32_t)(f->Address >> 32);
    }

    lidt((uintptr_t *)&KernelIdtr);
}
