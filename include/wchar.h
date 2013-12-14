#ifndef _STDC_WCHAR_H_
#define _STDC_WCHAR_H_

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef 	int				mbstate_t;
typedef	__WINT_TYPE__		wint_t;
struct tm;

int					swprintf	(wchar_t* s, size_t n, const wchar_t* format, ...);
int					swscanf	(const wchar_t* s, const wchar_t* format, ...);
int					vswprintf	(wchar_t* s, size_t n, const wchar_t* format, va_list arg);
int					vswscanf	(const wchar_t* s, const wchar_t* format, va_list arg);
double				wcstod	(const wchar_t* nptr, wchar_t** endptr);
float					wcstof	(const wchar_t* nptr, wchar_t** endptr);
long double			wcstold	(const wchar_t* nptr, wchar_t** endptr);
long int				wcstol	(const wchar_t* nptr, wchar_t** endptr, int base);
long long int			wcstoll	(const wchar_t* nptr, wchar_t** endptr, int base);
unsigned long int		wcstoul	(const wchar_t* nptr, wchar_t** endptr, int base);
unsigned long long int	wcstoull	(const wchar_t* nptr, wchar_t** endptr, int base);
wchar_t*				wcscpy	(wchar_t* s1, const wchar_t* s2);
wchar_t*				wcsncpy	(wchar_t* s1, const wchar_t* s2, size_t n);
wchar_t*				wmemcpy	(wchar_t* s1, const wchar_t* s2, size_t n);
wchar_t*				wmemmove	(wchar_t* s1, const wchar_t* s2, size_t n);
wchar_t*				wcscat	(wchar_t* s1, const wchar_t* s2);
wchar_t*				wcsncat	(wchar_t* s1, const wchar_t* s2, size_t n);
int					wcscmp	(const wchar_t* s1, const wchar_t* s2);
int					wcscoll	(const wchar_t* s1, const wchar_t* s2);
int					wcsncmp	(const wchar_t* s1, const wchar_t* s2, size_t n);
size_t				wcsxfrm	(wchar_t* s1, const wchar_t* s2, size_t n);
int					wmemcmp	(const wchar_t* s1, const wchar_t* s2, size_t n);
wchar_t*				wcschr	(const wchar_t* s, wchar_t c);
size_t				wcscspn	(const wchar_t* s1, const wchar_t* s2);
wchar_t*				wcspbrk	(const wchar_t* s1, const wchar_t* s2);
wchar_t*				wcsrchr	(const wchar_t* s, wchar_t c);
size_t				wcsspn	(const wchar_t* s1, const wchar_t* s2);
wchar_t*				wcsstr	(const wchar_t* s1, const wchar_t* s2);
wchar_t*				wcstok	(wchar_t* s1, const wchar_t* s2, wchar_t** ptr);
wchar_t*				wmemchr	(const wchar_t* s, wchar_t c, size_t n);
size_t				wcslen	(const wchar_t* s);
wchar_t*				wmemset	(wchar_t* s, wchar_t c, size_t n);
size_t				wcsftime	(wchar_t* s, size_t maxsize, const wchar_t* format, const struct tm* timeptr);
wint_t				btowc	(int c);
int					wctob	(wint_t c);
int					mbsinit	(const mbstate_t* ps);
size_t				mbrlen	(const char* s, size_t n, mbstate_t* ps);
size_t				mbrtowc	(wchar_t* pwc, const char* s, size_t n, mbstate_t* ps);
size_t				wcrtomb	(char* s, wchar_t wc, mbstate_t* ps);
size_t				mbsrtowcs	(wchar_t* dst, const char** src, size_t len, mbstate_t* ps);
size_t				wcsrtombs	(char* dst, const wchar_t** src, size_t len, mbstate_t* ps);

#ifdef __cplusplus
}
#endif
	
#endif
