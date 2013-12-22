/*

   Copyright 2009 Pierre KRIEGER

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#ifndef _STDC_STRING_H_
#define _STDC_STRING_H_

#include <machine/_target.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void*	memcpy	(void* s1, const void* s2, size_t n);
void*	memmove	(void* s1, const void* s2, size_t n);
char*	strcpy	(char* s1, const char* s2);
char*	strncpy	(char* s1, const char* s2, size_t n);
char*	strcat	(char* s1, const char* s2);
char*	strncat	(char* s1, const char* s2, size_t n);
int		memcmp	(const void* s1, const void* s2, size_t n)		__attribute__((pure));
int		strcmp	(const char* s1, const char* s2)				__attribute__((pure));
int		strncmp	(const char* s1, const char* s2, size_t n)		__attribute__((pure));
void*	memchr	(const void* s, int c, size_t n);
char*	strchr	(const char* s, int c);
size_t	strcspn	(const char* s1, const char* s2);
char*	strpbrk	(const char* s1, const char* s2);
char*	strrchr	(const char* s, int c);
size_t	strspn	(const char* s1, const char* s2);
char*	strstr		(const char* s1, const char* s2);
char*	strtok	(char* s1, const char* s2);
void*	memset	(void* s, int c, size_t n);
size_t	strlen		(const char* s)							__attribute__((pure));


#ifdef __GNUC__
/* GCC has builtin functions which have two possible effects:
*    - either they are optimized (eg. __builtin_strlen("hello") could be replaced by 5)
*    - or they simply call the corresponding function (eg. __builtin_memcpy could simply be a call to memcpy)
*/
#define	memcpy(d,s,n)				__builtin_memcpy(d,s,n)
#define	strcpy(d,s) 				__builtin_strcpy(d,s)
#define	strncpy(d,s,n)				__builtin_strncpy(d,s,n);
#define	strcat(d,s)					__builtin_strcat(d,s)
#define	strncat(d,s,n)				__builtin_strncat(d,s,n)
#define	memcmp(a,b,n)				__builtin_memcmp(a,b,n)
#define	strcmp(a,b)				__builtin_strcmp(a,b)
#define	strncmp(a,b,n)				__builtin_strncmp(a,b,n)
#define	memchr(s,c,n)				__builtin_memchr(s,c,n)
#define	strchr(s,c)					__builtin_strchr(s,c)
#define	strcspn(a,b)				__builtin_strcspn(a,b)
#define	strpbrk(a,b)				__builtin_strpbrk(a,b)
#define	strrchr(s,c)					__builtin_strrchr(s,c)
#define	strspn(a,b)					__builtin_strspn(a,b)
#define	strstr(a,b)					__builtin_strstr(a,b)
#define	strtok(d,s)					__builtin_strtok(d,s)
#define	memset(s,c,n)				__builtin_memset(s,c,n)
#define	strlen(s)					__builtin_strlen(s)
#endif



#ifdef __cplusplus
}
#endif

#endif
