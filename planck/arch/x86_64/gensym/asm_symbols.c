#include <stdint.h>
#include <stddef.h>
#include <arch/cpu.h>
#include <arch/page.h>
#include <arch/segment.h>
#include <arch/trap.h>
#include <arch/boot.h>

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE)0)->MEMBER)

#define DECLARE(SYM, VAL) \
    __asm("#DEFINITION##define " SYM "\t%0" : : "n" ((size_t)(VAL)))

#define AST_URGENT 1

int main(int argc, char **argv)
{
    DECLARE("SS_FLAVOR", offsetof(x86_saved_state_t *, flavor));
    DECLARE("SS_32", X86_SAVED_STATE32);
    DECLARE("SS_64", X86_SAVED_STATE64);

#define R_(x)  offsetof(x86_saved_state_t *, ss_32.x)
    DECLARE("R32_CS",     R_(cs));
    DECLARE("R32_SS",     R_(ss));
    DECLARE("R32_DS",     R_(ds));
    DECLARE("R32_ES",     R_(es));
    DECLARE("R32_FS",     R_(fs));
    DECLARE("R32_GS",     R_(gs));
    DECLARE("R32_UESP",   R_(uesp));
    DECLARE("R32_EBP",    R_(ebp));
    DECLARE("R32_EAX",    R_(eax));
    DECLARE("R32_EBX",    R_(ebx));
    DECLARE("R32_ECX",    R_(ecx));
    DECLARE("R32_EDX",    R_(edx));
    DECLARE("R32_ESI",    R_(esi));
    DECLARE("R32_EDI",    R_(edi));
    DECLARE("R32_TRAPNO", R_(trapno));
    DECLARE("R32_ERR",    R_(err));
    DECLARE("R32_EFLAGS", R_(efl));
    DECLARE("R32_EIP",    R_(eip));
    DECLARE("R32_CR2",    R_(cr2));
    DECLARE("ISS32_SIZE", sizeof(x86_saved_state32_t));

#define R64_(x)  offsetof(x86_saved_state_t *, ss_64.x)
    DECLARE("R64_FS",     R64_(fs));
    DECLARE("R64_GS",     R64_(gs));
    DECLARE("R64_R8",     R64_(r8));
    DECLARE("R64_R9",     R64_(r9));
    DECLARE("R64_R10",    R64_(r10));
    DECLARE("R64_R11",    R64_(r11));
    DECLARE("R64_R12",    R64_(r12));
    DECLARE("R64_R13",    R64_(r13));
    DECLARE("R64_R14",    R64_(r14));
    DECLARE("R64_R15",    R64_(r15));
    DECLARE("R64_RBP",    R64_(rbp));
    DECLARE("R64_RAX",    R64_(rax));
    DECLARE("R64_RBX",    R64_(rbx));
    DECLARE("R64_RCX",    R64_(rcx));
    DECLARE("R64_RDX",    R64_(rdx));
    DECLARE("R64_RSI",    R64_(rsi));
    DECLARE("R64_RDI",    R64_(rdi));
    DECLARE("R64_V_ARG6", R64_(v_arg6));
    DECLARE("R64_V_ARG7", R64_(v_arg7));
    DECLARE("R64_V_ARG8", R64_(v_arg8));
    DECLARE("R64_CS",     R64_(isf.cs));
    DECLARE("R64_SS",     R64_(isf.ss));
    DECLARE("R64_RSP",    R64_(isf.rsp));
    DECLARE("R64_TRAPNO", R64_(isf.trapno));
    DECLARE("R64_TRAPFN", R64_(isf.trapfn));
    DECLARE("R64_ERR",    R64_(isf.err));
    DECLARE("R64_RFLAGS", R64_(isf.rflags));
    DECLARE("R64_RIP",    R64_(isf.rip));
    DECLARE("R64_CR2",    R64_(cr2));
    DECLARE("ISS64_OFFSET", R64_(isf));
    DECLARE("ISS64_SIZE",   sizeof(x86_saved_state64_t));

#define ISF64_(x)  offsetof(x86_64_intr_stack_frame *, x)
    DECLARE("ISF64_TRAPNO", ISF64_(trapno));
    DECLARE("ISF64_TRAPFN", ISF64_(trapfn));
    DECLARE("ISF64_ERR",    ISF64_(err));
    DECLARE("ISF64_RIP",    ISF64_(rip));
    DECLARE("ISF64_CS",     ISF64_(cs));
    DECLARE("ISF64_RFLAGS", ISF64_(rflags));
    DECLARE("ISF64_RSP",    ISF64_(rsp));
    DECLARE("ISF64_SS",     ISF64_(ss));
    DECLARE("ISF64_SIZE",   sizeof(x86_64_intr_stack_frame));

    return 0;
}
