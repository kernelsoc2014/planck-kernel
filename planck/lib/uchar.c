#include <uchar.h>
/*
size_t mbrtoc16(char16_t* pc16, const char* s, size_t n, mbstate_t* ps) {
	char32_t ch32;
	size_t returnValue = mbrtoc32(&ch32, s, n, NULL);
	if (returnValue >= (size_t)-3 && returnValue <= (size_t)-1)
		return returnValue;

	if (ch32 <= 0xFFFD) {

	}
}

size_t c16rtomb(char* s, char16_t c16, mbstate_t* ps) {
}*/

size_t mbrtoc32(char32_t* pc32, const char* s, size_t n, mbstate_t* ps) {
	// first case: null character
	if (*s == 0) {
		*pc32 = 0;
		return 0;
	}

	// second case: simple ASCII char
	if ((*s & 80) == 0) {
		*pc32 = *s;
		return 1;
	}

	// last case: multibytes characters
	if ((*s & 0xE0) == 0xC0) {				// 110xxxxx => 2 bytes
		if (n < 2)	return (size_t)-2;
		*pc32 = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
		return 2;
	} else if ((*s & 0xF0) == 0xE0) {			// 1110xxxx => 3 bytes
		if (n < 3)	return (size_t)-2;
		*pc32 = ((s[0] & 0xF) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
		return 3;
	} else if ((*s & 0xF8) == 0xF0) {			// 11110xxx => 4 bytes
		if (n < 4)	return (size_t)-2;
		*pc32 = ((s[0] & 0x7) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[4] & 0x3F);
		return 4;
	}

	return (size_t)-1;
}

size_t c32rtomb(char* s, char32_t c32, mbstate_t* ps) {
	if (c32 <= 0x7F) {			// at most 7 bits => 1 byte
		*s = (char)c32 & 0x7F;
		return 1;
	} else if (c32 <= 0x7FF) {		// at most 11 bits => 2 bytes
		s[1] = 0x80 | (char)(c32 & 0x3F);
		s[0] = 0xC0 | (char)(c32 >> 6);
		return 2;
	} else if (c32 <= 0xFFFF) {		// at most 16 bits => 3 bytes
		s[2] = 0x80 | (char)(c32 & 0x3F);
		s[1] = 0x80 | (char)((c32 >> 6) & 0x3F);
		s[0] = 0xE0 | (char)(c32 >> 12);
		return 3;
	} else if (c32 <= 0x1FFFFF) {	// at most 21 bits => 4 bytes
		s[3] = 0x80 | (char)(c32 & 0x3F);
		s[2] = 0x80 | (char)((c32 >> 6) & 0x3F);
		s[1] = 0x80 | (char)((c32 >> 12) & 0x3F);
		s[0] = 0xF0 | (char)(c32 >> 18);
		return 4;
	}

	return (size_t)-1;
}
