#pragma once

#include <stdarg.h>
#include <planck/compiler.h>

__BEGIN_DECLS

void KeEarlyVOutput(const char *format, va_list args);
void KeEarlyOutput(const char *format, ...);

__END_DECLS
