#pragma once

#ifdef __ASSEMBLER__
#define _AC(X, Y) X
#define _AT(T, X) X
#else
#define _AC_JOIN(X, Y) (X##Y)
#define _AC(X, Y) _AC_JOIN(X,Y)
#define _AT(T, X) ((T)(X))
#endif

#ifdef __ASSEMBLER__

#define Entry(x) \
    .global x; \
    x:

#else

#define __section(S) __attribute__((__section__(#S)))
#define __init __section(.init.text)
#define __initdata __section(.init.data)

#endif
