#pragma once

#include <planck/compiler.h>
#include <planck/status.h>
#include <arch/segment.h>
#include <arch/task.h>

typedef void (*TrapHandler)(int from, void *params);

__BEGIN_DECLS

void AcTrapInitialize();
void AcTrapRegisterHandler(int number, TrapHandler handler);

__END_DECLS
