#include <planck/compiler.h>
#include <gensym/asm_symbols.h>
#include <arch/trap.h>
#include <arch/segment.h>
#include <arch/cpu.h>

#define PUSH_FUNCTION(func)   \
    sub    $8, %rsp          ;\
    push   %rax              ;\
    leaq   func, %rax        ;\
    movq   %rax, 8(%rsp)     ;\
    pop    %rax

#define IDT_ENTRY_WRAPPER(n, f)  \
    PUSH_FUNCTION(f)            ;\
    pushq    $(n)               ;\
    jmp L_dispatch

#define TRAP_ERR(n, f)                   \
    Entry(f)                            ;\
    IDT_ENTRY_WRAPPER(n, L_dispatch)

#define TRAP(n, f)                       \
    Entry(f)                            ;\
    pushq    $0                         ;\
    IDT_ENTRY_WRAPPER(n, L_dispatch)

#define USER_TRAP TRAP

#define INTERRUPT(n)                     \
    Entry(_intr_ ## n)                  ;\
    pushq    $0                         ;\
    IDT_ENTRY_WRAPPER(n, L_dispatch)

#define TRAP_SPC(n, f)
#define TRAP_IST1(n, f)
#define TRAP_IST2(n, f)
#define USER_TRAP_SPC(n, f)

#define CPU_KERNEL_STACK 0

#include "idt_table.h"

L_dispatch:
    cmpl    $KERNEL64_CS, ISF64_CS(%rsp)
    je    L_dispatch_kernel

    swapgs

L_dispatch_U64:
    subq    $(ISS64_OFFSET), %rsp
    mov    %r15, R64_R15(%rsp)
    mov    %rsp, %r15
    mov    %gs:CPU_KERNEL_STACK, %rsp
    jmp    L_dispatch_64bit

L_dispatch_kernel:
    subq    $ISS64_OFFSET, %rsp
    mov    %r15, R64_R15(%rsp)
    mov    %rsp, %r15

L_dispatch_64bit:
    movl    $(SS_64), SS_FLAVOR(%r15)

    mov    %fs, R64_FS(%r15)
    mov    %gs, R64_GS(%r15)

    movq    %rax, R64_RAX(%r15)
    movq    %rbx, R64_RBX(%r15)
    movq    %rcx, R64_RCX(%r15)
    movq    %rdx, R64_RDX(%r15)
    movq    %rbp, R64_RBP(%r15)
    movq    %rdi, R64_RDI(%r15)
    movq    %rsi, R64_RSI(%r15)
    movq    %r8,  R64_R8(%r15)
    movq    %r9,  R64_R9(%r15)
    movq    %r10, R64_R10(%r15)
    movq    %r11, R64_R11(%r15)
    movq    %r12, R64_R12(%r15)
    movq    %r13, R64_R13(%r15)
    movq    %r14, R64_R14(%r15)

    iretq

Entry(idt64_debug)
Entry(idt64_nmi)
Entry(idt64_double_fault)
Entry(idt64_segnp)
Entry(idt64_stack_fault)
Entry(idt64_gen_prot)
Entry(idt64_page_fault)
Entry(idt64_mc)
