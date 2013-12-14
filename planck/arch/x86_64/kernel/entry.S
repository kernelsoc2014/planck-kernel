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
    IDT_ENTRY_WRAPPER(n, kernel_handle_traps)

#define TRAP(n, f)                       \
    Entry(f)                            ;\
    pushq    $0                         ;\
    IDT_ENTRY_WRAPPER(n, kernel_handle_traps)

#define USER_TRAP TRAP

#define INTERRUPT(n)                     \
    Entry(_intr_ ## n)                  ;\
    pushq    $0                         ;\
    IDT_ENTRY_WRAPPER(n, kernel_handle_interrupt)

#define TRAP_SPC(n, f)
#define TRAP_IST1(n, f)
#define TRAP_IST2(n, f)
#define USER_TRAP_SPC(n, f)

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

    movl    %fs, R64_FS(%r15)
    movl    %gs, R64_GS(%r15)

    mov    %rax, R64_RAX(%r15)
    mov    %rbx, R64_RBX(%r15)
    mov    %rcx, R64_RCX(%r15)
    mov    %rdx, R64_RDX(%r15)
    mov    %rbp, R64_RBP(%r15)
    mov    %rdi, R64_RDI(%r15)
    mov    %rsi, R64_RSI(%r15)
    mov    %r8,  R64_R8(%r15)
    mov    %r9,  R64_R9(%r15)
    mov    %r10, R64_R10(%r15)
    mov    %r11, R64_R11(%r15)
    mov    %r12, R64_R12(%r15)
    mov    %r13, R64_R13(%r15)
    mov    %r14, R64_R14(%r15)