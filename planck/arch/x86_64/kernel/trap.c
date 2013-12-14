#include <arch/trap.h>
#include <arch/cpu.h>
#include <arch/segment.h>

typedef struct {
    uint64_t    address;
    uint32_t    segment : 20;
    uint32_t    IST : 4;
    uint32_t    access : 8;
    uint32_t    reserved : 32;
} idt_fake_t;

#define K_INTR_GATE (ACC_P | ACC_PL_K | ACC_INTR_GATE)
#define U_INTR_GATE (ACC_P | ACC_PL_U | ACC_INTR_GATE)

#define TRAP(n, name)             extern void *name ;
#define TRAP_ERR(n, name)         extern void *name ;
#define TRAP_SPC(n, name)         extern void *name ;
#define TRAP_IST1(n, name)        extern void *name ;
#define TRAP_IST2(n, name)        extern void *name ;
#define INTERRUPT(n)              extern void *_intr_##n;
#define USER_TRAP(n, name)        extern void *name ;
#define USER_TRAP_SPC(n, name)    extern void *name;

#include "idt_table.h"

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
        KERNEL64_CS,       \
        0,                 \
        K_INTR_GATE,       \
        0                  \
    },

#define TRAP_ERR TRAP
#define TRAP_SPC TRAP

#define TRAP_IST1(n, name) \
    [n] = {                \
        (uintptr_t)&name,  \
        KERNEL64_CS,       \
        1,                 \
        K_INTR_GATE,       \
        0                  \
    },

#define TRAP_IST2(n, name) \
    [n] = {                \
        (uintptr_t)&name,  \
        KERNEL64_CS,       \
        2,                 \
        K_INTR_GATE,       \
        0                  \
    },

#define INTERRUPT(n)             \
    [n] = {                      \
        (uintptr_t)&_intr_ ## n, \
        KERNEL64_CS,             \
        0,                       \
        K_INTR_GATE,             \
        0                        \
    },

#define USER_TRAP(n, name) \
    [n] = {                \
        (uintptr_t)&name,  \
        KERNEL64_CS,       \
        0,                 \
        U_INTR_GATE,       \
        0                  \
    },

#define USER_TRAP_SPC USER_TRAP

static idt_fake_t kernel_fake_idt[IDT_SIZE] = {
#include "idt_table.h"
};

static idt_gate64_t kernel_idt[IDT_SIZE];
static descriptor_descriptor64_t kernel_idtr = { sizeof(kernel_idt) - 1, (uint64_t)&kernel_idt };

void trap_init()
{
    for (int i = 0; i < IDT_SIZE; i++)
    {
        idt_fake_t *f = &kernel_fake_idt[i];
        idt_gate64_t *g = &kernel_idt[i];

        g->offset_low = (uint16_t)(f->address & 0xFFFF);
        g->selector = f->segment & 0xFFFF;
        g->IST = f->IST & 0x7;
        g->access = f->access;
        g->offset_high = (uint16_t)((f->address >> 16) & 0xFFFF);
        g->offset_top = (uint32_t)(f->address >> 32);
    }

    lidt((uintptr_t *)&kernel_idtr);
    //sti();
}
