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
    DECLARE("KERNEL64_CS", kKernelCode64);
    DECLARE("KERNEL_DS", kKernelData);
    DECLARE("USER32_CS", kUserCode32);
    DECLARE("USER32_DS", kUserData);
    DECLARE("USER64_CS", kUserCode64);
    DECLARE("USER64_DS", kUserData);

    DECLARE("SS_TYPE", offsetof(TaskSavedState *, Type));
    DECLARE("SS_32", kTaskState32);
    DECLARE("SS_64", kTaskState64);

#define R_(x)  offsetof(TaskSavedState *, State.T32.x)
    DECLARE("R32_CS",     R_(CS));
    DECLARE("R32_SS",     R_(SS));
    DECLARE("R32_DS",     R_(DS));
    DECLARE("R32_ES",     R_(ES));
    DECLARE("R32_FS",     R_(FS));
    DECLARE("R32_GS",     R_(GS));
    DECLARE("R32_UESP",   R_(UserESP));
    DECLARE("R32_EBP",    R_(EBP));
    DECLARE("R32_EAX",    R_(EAX));
    DECLARE("R32_EBX",    R_(EBX));
    DECLARE("R32_ECX",    R_(ECX));
    DECLARE("R32_EDX",    R_(EDX));
    DECLARE("R32_ESI",    R_(ESI));
    DECLARE("R32_EDI",    R_(EDI));
    DECLARE("R32_TRAPNO", R_(TrapNumber));
    DECLARE("R32_ERR",    R_(Error));
    DECLARE("R32_EFLAGS", R_(EFlags));
    DECLARE("R32_EIP",    R_(EIP));
    DECLARE("R32_CR2",    R_(CR2));
    DECLARE("ISS32_SIZE", sizeof(TaskSavedState32));

#define R64_(x)  offsetof(TaskSavedState *, State.T64.x)
    DECLARE("R64_FS",     R64_(GS));
    DECLARE("R64_GS",     R64_(GS));
    DECLARE("R64_R8",     R64_(R8));
    DECLARE("R64_R9",     R64_(R9));
    DECLARE("R64_R10",    R64_(R10));
    DECLARE("R64_R11",    R64_(R11));
    DECLARE("R64_R12",    R64_(R12));
    DECLARE("R64_R13",    R64_(R13));
    DECLARE("R64_R14",    R64_(R14));
    DECLARE("R64_R15",    R64_(R15));
    DECLARE("R64_RBP",    R64_(RBP));
    DECLARE("R64_RAX",    R64_(RAX));
    DECLARE("R64_RBX",    R64_(RBX));
    DECLARE("R64_RCX",    R64_(RCX));
    DECLARE("R64_RDX",    R64_(RDX));
    DECLARE("R64_RSI",    R64_(RSI));
    DECLARE("R64_RDI",    R64_(RDI));
    DECLARE("R64_V_ARG6", R64_(Arg6));
    DECLARE("R64_V_ARG7", R64_(Arg7));
    DECLARE("R64_V_ARG8", R64_(Arg8));
    DECLARE("R64_CS",     R64_(Interrupt.CS));
    DECLARE("R64_SS",     R64_(Interrupt.SS));
    DECLARE("R64_RSP",    R64_(Interrupt.RSP));
    DECLARE("R64_TRAPNO", R64_(Interrupt.TrapNumber));
    DECLARE("R64_TRAPFN", R64_(Interrupt.TrapFunction));
    DECLARE("R64_ERR",    R64_(Interrupt.Error));
    DECLARE("R64_RFLAGS", R64_(Interrupt.RFlags));
    DECLARE("R64_RIP",    R64_(Interrupt.RIP));
    DECLARE("R64_CR2",    R64_(CR2));
    DECLARE("ISS64_OFFSET", R64_(Interrupt));
    DECLARE("ISS64_SIZE",   sizeof(TaskSavedState64));

#define ISF64_(x)  offsetof(InterruptStackFrame *, x)
    DECLARE("ISF64_TRAPNO", ISF64_(TrapNumber));
    DECLARE("ISF64_TRAPFN", ISF64_(TrapFunction));
    DECLARE("ISF64_ERR",    ISF64_(Error));
    DECLARE("ISF64_RIP",    ISF64_(RIP));
    DECLARE("ISF64_CS",     ISF64_(CS));
    DECLARE("ISF64_RFLAGS", ISF64_(RFlags));
    DECLARE("ISF64_RSP",    ISF64_(RSP));
    DECLARE("ISF64_SS",     ISF64_(SS));
    DECLARE("ISF64_SIZE",   sizeof(InterruptStackFrame));

    return 0;
}
