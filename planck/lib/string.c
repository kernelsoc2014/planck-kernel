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

#include <string.h>
#include <machine/_target.h>

#undef memcpy
void* memcpy(void* destination, const void* source, size_t num) {
#if defined(__GNUC__) && defined(_TARGET_X86_)
	void* temporaryDestination = destination;
	asm volatile("rep movsl ; mov %3, %2 ; rep movsb" : "+S"(source), "+D"(temporaryDestination) : "c"(num / 4), "r"(num % 4) : "cc", "memory");
#else
	const unsigned char* vsource = (const unsigned char*)source;
	unsigned char* vdestination = (unsigned char*)destination;
	while (num >= 1) {
		*vdestination = *vsource;
		vsource++; vdestination++; num--;
	}
#endif
	return destination;
}

#undef memmove
void* memmove(void* destination, const void* source, size_t num) {
#ifdef _TARGET_X86_
	if (destination < source)
		asm volatile("rep movsb" :: "S"(source), "D"(destination), "c"((long)num) : "cc", "memory");
	else
		asm volatile("std; rep movsb; cld" :: "S"((unsigned char*)source + num - 1), "D"((unsigned char*)destination + num - 1), "c"((long)num) : "cc", "memory");
#else
	const unsigned char* sp;
	unsigned char* dp;
	if (destination < source) {
		sp = (const unsigned char*)source; dp = (unsigned char*)destination;
		while (num) { *dp = *sp; dp++; sp++; num--; }
	} else {
		while (num) {
			sp = (unsigned char*)source + num - 1;
			dp = (unsigned char*)destination + num - 1;
			*dp = *sp;
			num--;
		}
	}
#endif
	return destination;
}

#undef strcpy
char* strcpy(char* destination, const char* source) {
	return memcpy(destination, source, strlen(source) + 1);
}

#undef strncpy
char* strncpy(char* destination, const char* source, size_t n) {
	size_t len = strlen(source) + 1;
	if (len > n) len = n;
	memcpy(destination, source, len);
	if (len < n) memset(destination + len, '\0', n - len);
	return destination;
}

#undef strcat
char* strcat(char* s1, const char* s2) {
	strcpy(s1 + strlen(s1), s2);
	return s1;
}

#undef strncat
char* strncat(char* s1, const char* s2, size_t n) {
	size_t n2 = strlen(s2);
	if (n2 > n) n2 = n;
	strncpy(s1 + strlen(s1), s2, n2);
	s1[strlen(s1) + n2] = '\0';
	return s1;
}

#undef memcmp
int memcmp(const void* ptr1, const void* ptr2, size_t num) {
	const unsigned char* vptr1 = (const unsigned char*)ptr1;
	const unsigned char* vptr2 = (const unsigned char*)ptr2;
	while (num) {
		if (*vptr1 > *vptr2) return 1;
		else if (*vptr1 < *vptr2) return -1;
		vptr1++; vptr2++; num--;
	}
	return 0;
}

#undef strcmp
int strcmp(const char* str1, const char* str2) {
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	
	int cmpResult = memcmp(str1, str2, (len1 < len2) ? len1 : len2);
	if (cmpResult != 0)
		return cmpResult;
	
	if (len1 > len2)
		return 1;
	else if (len1 < len2)
		return -1;
	
	return 0;
}

#undef strncmp
int strncmp(const char* s1, const char* s2, size_t n) {
	return memcmp(s1, s2, n);
}

#undef memchr
void* memchr(const void* ptr, int value, size_t num) {
	const unsigned char* vptr = (const unsigned char*)ptr;
	while (num) {
		if (*vptr == (unsigned char)value)
			return ((void*)vptr);
		vptr++; num--;
	}
	return NULL;
}

#undef strchr
char* strchr(const char* s, int c) {
	return memchr(s, c, strlen(s) + 1);
}

#undef strcspn
size_t strcspn(const char* s1, const char* s2) {
	char* pbrk = strpbrk(s1, s2);
	if (pbrk == NULL)
		return strlen(s1);
	return (size_t)(pbrk - s1);
}

#undef strpbrk
char* strpbrk(const char* s1, const char* s2) {
	int s2len = strlen(s2);
	for (; *s1 != '\0'; s1++) {
		int i;
		for (i = 0; i < s2len; i++)
			if (*s1 == s2[i])
				return (char*)s1;
	}
	return NULL;
}

#undef strrchr
char* strrchr(const char* str, int character) {
	int i = strlen(str);
	for (; i >= 0; i--)
		if (str[i] == character)
			return (char*)str + i;
	return NULL;
}

#undef strspn
size_t strspn(const char* s1, const char* s2) {
	int found = 0;
	size_t len = 0;
	do {
		int i;
		for (i = 0; i < strlen(s2); i++) {
			if (s1[len] == s2[i]) {
				len++;
				found = 1;
				break;
			}
		}
	} while(found);
	return len;
}

#undef strstr
char* strstr(const char* s1, const char* s2) {
	size_t s2len = strlen(s2);
	for (; *s1 != '\0'; s1++) {
		int i;
		for (i = 0; i < s2len; i++) {
			if (s2[i] == '\0')
				return (char*)s1;
			if (s2[i] == *s1)
				continue;
			break;
		}
	}
	return NULL;
}

#undef strtok
char* strtok(char* s1, const char* s2) {
	static char* prevS1;
	if (s1 == NULL) {
		if (prevS1 == NULL)
			return NULL;
		s1 = prevS1;
	}
	
	s1 += strspn(s1, s2);
	if (*s1 == '\0')
		return NULL;
	size_t s1newLen = strcspn(s1, s2);
	
	if (s1[s1newLen] == '\0') {
		// we are at the end of the original string
		// next call should return NULL whatever s2 is
		prevS1 = NULL;
	} else {
		s1[s1newLen] = '\0';
		prevS1 = s1 + s1newLen + 1;
	}
	
	return s1;
}

#undef memset
void* memset(void* ptr, int value, size_t num) {
#if defined(__GNUC__) && defined(_TARGET_X86_)
	// 'stosl' will use the value in eax but we only want the value in al
	// so we make eax = al << 24 | al << 16 | al << 8 | al
	if ((value & 0xff) == 0)
		// this is a little optimization because memset is most often called with value = 0
		value = 0;
	else {
		value = (value & 0xff) | ((value & 0xff) << 8);
		value = (value & 0xffff) | ((value & 0xffff) << 16);
	}
	
	void* temporaryPtr = ptr;
	asm volatile("rep stosl ; mov %3, %2 ; rep stosb" : "+D"(temporaryPtr) : "a"(value), "c"(num / 4), "r"(num % 4) : "cc", "memory");
#else
	unsigned char* vptr = (unsigned char*)ptr;
	while (num) {
		*vptr = (unsigned char)value;
		vptr++; num--;
	}
#endif
	return ptr;
}

#undef strlen
size_t strlen(const char* str) {
	size_t len = 0;
#if defined(__GNUC__) && defined(_TARGET_X86_)
	const char* endPtr = str;
	asm("repne scasb" : "+D"(endPtr) : "a"(0), "c"(~0) : "cc");
	len = (endPtr - str) - 1;
#else
	while (*str != '\0') { str++; len++; }
#endif
	return len;
}
