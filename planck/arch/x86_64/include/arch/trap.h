#pragma once

#include <planck/compiler.h>
#include <arch/segment.h>
#include <arch/task.h>

#define TRAP_FROM_X86_32 0
#define TRAP_FROM_X86_64 1

#ifndef __ASSEMBLER__

typedef void (*trap_handler_t)(int from, void *params);

__BEGIN_DECLS

void trap_init();
void trap_register_handler(int number, trap_handler_t handler);

__END_DECLS

#endif
