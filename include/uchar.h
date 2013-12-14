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

#ifndef _STDC_UCHAR_H_
#define _STDC_UCHAR_H_

#include <wchar.h>
#include <stdint.h>

typedef	uint_least16_t		char16_t;
#define	__STDC_UTF_16__		1
typedef	uint_least32_t		char32_t;
#define	__STDC_UTF_32__		1

size_t		mbrtoc16(char16_t* pc16, const char* s, size_t n, mbstate_t* ps);
size_t		c16rtomb(char* s, char16_t c16, mbstate_t* ps);
size_t		mbrtoc32(char32_t* pc32, const char* s, size_t n, mbstate_t* ps);
size_t		c32rtomb(char* s, char32_t c32, mbstate_t* ps);

#endif
