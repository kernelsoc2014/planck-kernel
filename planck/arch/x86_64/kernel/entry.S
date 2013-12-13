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
    IDT_ENTRY_WRAPPER(n, HNDL_ALLTRAPS)

#define TRAP(n, f)                       \
    Entry(f)                            ;\
    pushq    $0                         ;\
    IDT_ENTRY_WRAPPER(n, HNDL_ALLTRAPS)

#define USER_TRAP TRAP

#define INTERRUPT(n)                     \
    Entry(_intr_ ## n)                  ;\
    pushq    $0                         ;\
    IDT_ENTRY_WRAPPER(n, HNDL_ALLINTRS)

#define TRAP_SPC(n, f)
#define TRAP_IST1(n, f)
#define TRAP_IST2(n, f)
#define USER_TRAP_SPC(n, f)

#include "idt_table.h"

L_dispatch:
    cmpl    $KERNEL64_CS, ISF64_CS(%rsp)
    je    L_dispatch_kernel

    swapgs
    hlt

L_dispatch_kernel:
    subq    $(ISS64_OFFSET), %rsp
    mov    %r15, R64_R15(%rsp)
    mov    %rsp, %r15

