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

#include <stdlib.h>
#include <ctype.h>
#include <machine/_target.h>

static unsigned long _rand_value = 1;

double				atof		(const char* nptr);

int atoi(const char* str) {
	int result = 0;
	while (isspace(*str))
		str++;
	while (isdigit(*str))
		result = (result * 10) + (*(str++) - '0');
	return result;
}

long int atol(const char* str) {
	long int result = 0;
	while (isspace(*str))
		str++;
	while (isdigit(*str))
		result = (result * 10) + (*(str++) - '0');
	return result;
}

long long int atoll(const char* str) {
	long long int result = 0;
	while (isspace(*str))
		str++;
	while (isdigit(*str))
		result = (result * 10) + (*(str++) - '0');
	return result;
}

double				strtod	(const char* nptr, char** endptr);
float					strtof		(const char* nptr, char** endptr);
long double			strtold	(const char* nptr, char** endptr);
long int				strtol		(const char* nptr, char** endptr, int base);
long long int			strtoll	(const char* nptr, char** endptr, int base);
unsigned long int		strtoul	(const char* nptr, char** endptr, int base);
unsigned long long int	strtoull	(const char* nptr, char** endptr, int base);

int rand() {
	_rand_value = _rand_value * 110351524 + 12345;
	return (_rand_value % (RAND_MAX + 1));
}

void srand(unsigned int seed) {
	_rand_value = seed;
}

void*				bsearch	(const void* key, const void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));
void					qsort		(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

int abs(int j) {
	return (j < 0) ? (-j) : j;
}

long int labs(long int j) {
	return (j < 0) ? (-j) : j;
}

long long int llabs(long long int j) {
	return (j < 0) ? (-j) : j;
}

div_t div(int numer, int denom) {
	div_t result;
	result.quot = numer / denom;
	result.rem = numer % denom;
	return result;
}

ldiv_t ldiv(long int numer, long int denom) {
	ldiv_t result;
	result.quot = numer / denom;
	result.rem = numer % denom;
	return result;
}

lldiv_t lldiv(long long int numer, long long int denom) {
	lldiv_t result;
	/*result.quot = numer / denom;
	result.rem = numer % denom;*/
	return result;
}

int					mblen	(const char* s, size_t n);
int					mbtowc	(wchar_t* pwc, const char* s, size_t n);
int					wctomb	(char* s, wchar_t wc);
size_t				mbstowcs	(wchar_t* pwcs, const char* s, size_t n);
size_t				wcstombs	(char* s, const wchar_t* pwcs, size_t n);

