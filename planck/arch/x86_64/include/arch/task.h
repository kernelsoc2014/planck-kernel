#pragma once

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <planck/compiler.h>

#pragma pack(4)

typedef struct
{
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t cr2;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint16_t trapno;
    uint16_t cpu;
    uint32_t err;
    uint32_t eip;
    uint32_t cs;
    uint32_t efl;
    uint32_t uesp;
    uint32_t ss;
} task_state32_t;

typedef struct
{
    uint16_t trapno;
    uint16_t cpu;
    uint32_t _pad;
    uint64_t trapfn;
    uint64_t err;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} interrupt_stack_frame_t;

typedef struct
{
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t r10;
    uint64_t r8;
    uint64_t r9;
    uint64_t v_arg6;
    uint64_t v_arg7;
    uint64_t v_arg8;
    uint64_t cr2;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t rbp;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rax;

    uint32_t gs;
    uint32_t fs;

    interrupt_stack_frame_t isf;
} task_state64_t;

typedef struct
{
    uint32_t res0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t res1;
    uint64_t ist[7];
    uint64_t res2;
    uint16_t res3;
    uint16_t iomap;
} system_tss_t;

#pragma pack()

__BEGIN_DECLS

extern system_tss_t task_kernel_tss;

__END_DECLS

#endif
