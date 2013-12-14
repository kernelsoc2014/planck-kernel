#pragma once

#include <stdarg.h>
#include <planck/compiler.h>

__BEGIN_DECLS

void early_vprintk(const char *format, va_list args);
void early_printk(const char *format, ...);

__END_DECLS
