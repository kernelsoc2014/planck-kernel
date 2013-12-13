#pragma once

#include <stdint.h>
#include <planck/compiler.h>

#ifndef __ASSEMBLER__

#pragma pack(4)

typedef struct
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint16_t trap_number, cpu;
    uint32_t error;
    uint32_t eip, cs, efl, uesp, ss;
} task_state32_t;

typedef struct
{
    uint64_t rdi, rsi, rdx, r10, r8, r9;
    uint64_t v_arg6, v_arg7, v_arg8;
    uint64_t cr2;
    uint64_t r15, r14, r13, r12, r11;
    uint64_t rbp, rbx, rcx, rax;
    uint32_t gs, fs;
    uint16_t trap_number, cpu;
    uint32_t _pad;
    uint64_t trapfn;
    uint64_t err, rip, cs, rflags, rsp, ss;
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
