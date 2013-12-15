#include <planck/compiler.h>
#include <gensym/asm_symbols.h>
#include <arch/boot.h>
#include <arch/cpu.h>

#define SWITCH_TO_64BIT_MODE                            \
    movl $CR4_PAE, %eax                                ;\
    movl %eax, %cr4                                    ;\
    movl $MSR_IA32_EFER, %ecx                          ;\
    rdmsr                                              ;\
    orl $(MSR_IA32_EFER_LME | MSR_IA32_EFER_NXE), %eax ;\
    wrmsr                                              ;\
    movl $BootPml4, %eax                               ;\
    movl %eax, %cr3                                    ;\
    movl %cr0, %eax                                    ;\
    orl $(CR0_PG | CR0_WP), %eax                       ;\
    movl %eax, %cr0                                    ;\
    ljmpl $KERNEL64_CS, $64f                           ;\
64:                                                    ;\
    .code64

.balign 8
.section .multiboot
mb_start:
    .long 0xE85250D6
    .long 0
    .long mb_end - mb_start
    .long -(0xE85250D6 + mb_end - mb_start)

mb_start_entry:
    .short 3
    .short 0
    .long mb_end_entry - mb_start_entry
    .long MultibootStartup
    .long 0
mb_end_entry:

mb_start_request:
    .short 6
    .short 0
    .long mb_end_request - mb_start_request
    .long 1
    .long 3
    .long 4
    .long 5
    .long 6
    .long 0
mb_end_request:

    .short 0
    .short 0
    .long 8
mb_end:

.section .init
.code32
MultibootStartup:
    xor $0x36d76289, %eax
    jz 1f
    hlt

1:
    cld
    movl $BootStackEnd, %esp

    pushl %ebx
    call MultibootSetup
    movl %eax, %edi

    jmp Startup64Post

Entry(Startup64)
    cld
    movl $BootStackEnd, %esp

Startup64Post:
    movl $BootGdtr, %eax
    lgdtl (%eax)

    SWITCH_TO_64BIT_MODE

    leaq KiKernelStart, %rcx
    pushq %rdi
    callq *%rcx
    hlt

Entry(StartupSlave64)
    cli
    cld
    movl $BootSlaveStackEnd, %esp
    xor %edi, %edi
    jmp Startup64Post

.section .init.data

BootGdtr:
    .word 160
    .quad BootGdt

BootStack:
    .fill BOOT_STACK_SIZE, 1, 0
BootStackEnd:

BootSlaveStack:
    .fill BOOT_STACK_SIZE, 1, 0
BootSlaveStackEnd:
