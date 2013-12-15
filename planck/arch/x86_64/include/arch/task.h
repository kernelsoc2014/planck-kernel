#pragma once

#include <stdint.h>
#include <planck/compiler.h>
#include <planck/status.h>

__BEGIN_DECLS

typedef enum
{
    kTaskState32,
    kTaskState64
} TaskStateType;

#pragma pack(4)

typedef struct
{
    uint32_t GS;
    uint32_t FS;
    uint32_t ES;
    uint32_t DS;
    uint32_t EDI;
    uint32_t ESI;
    uint32_t EBP;
    uint32_t CR2;
    uint32_t EBX;
    uint32_t EDX;
    uint32_t ECX;
    uint32_t EAX;
    uint16_t TrapNumber;
    uint16_t CPU;
    uint32_t Error;
    uint32_t EIP;
    uint32_t CS;
    uint32_t EFlags;
    uint32_t UserESP;
    uint32_t SS;
} TaskSavedState32;

typedef struct
{
    uint16_t TrapNumber;
    uint16_t CPU;
    uint32_t Pad;
    uint64_t TrapFunction;
    uint64_t Error;
    uint64_t RIP;
    uint64_t CS;
    uint64_t RFlags;
    uint64_t RSP;
    uint64_t SS;
} InterruptStackFrame;

typedef struct
{
    uint64_t RDI;
    uint64_t RSI;
    uint64_t RDX;
    uint64_t R10;
    uint64_t R8;
    uint64_t R9;
    uint64_t Arg6;
    uint64_t Arg7;
    uint64_t Arg8;
    uint64_t CR2;
    uint64_t R15;
    uint64_t R14;
    uint64_t R13;
    uint64_t R12;
    uint64_t R11;
    uint64_t RBP;
    uint64_t RBX;
    uint64_t RCX;
    uint64_t RAX;

    uint32_t GS;
    uint32_t FS;

    InterruptStackFrame Interrupt;
} TaskSavedState64;

typedef struct
{
    uint32_t Type;
    uint32_t Pad[3];

    union
    {
        TaskSavedState32 T32;
        TaskSavedState64 T64;
    } State;
} TaskSavedState;

typedef struct
{
    uint32_t Reserved0;
    uint64_t RSP0;
    uint64_t RSP1;
    uint64_t RSP2;
    uint64_t Reserved1;
    uint64_t IST[7];
    uint64_t Reserved2;
    uint16_t Reserved3;
    uint16_t IOMap;
} SystemTss;

#pragma pack()

extern SystemTss TaskKernelTss;

__END_DECLS
