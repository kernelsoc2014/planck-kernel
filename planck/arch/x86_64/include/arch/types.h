#pragma once

#ifdef __GNUC__
typedef __signed char       __int8_t;
#else
typedef char                __int8_t;
#endif

typedef unsigned char       __uint8_t;
typedef    short            __int16_t;
typedef    unsigned short   __uint16_t;
typedef int                 __int32_t;
typedef unsigned int        __uint32_t;
typedef long long           __int64_t;
typedef unsigned long long  __uint64_t;

#ifdef __GNUC__
typedef __signed char       int8_t;
#else
typedef char                int8_t;
#endif

typedef  short              int16_t;
typedef int                 int32_t;
typedef long long           int64_t;

typedef unsigned char       u_int8_t;
typedef unsigned short      u_int16_t;
typedef unsigned int        u_int32_t;
typedef unsigned long long  u_int64_t;

typedef int64_t intptr_t;
typedef u_int64_t uintptr_t;
typedef u_int64_t size_t;
