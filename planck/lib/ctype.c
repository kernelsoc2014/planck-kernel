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

#include <ctype.h>

#undef isalnum
int isalnum(int c) {
	return isalpha(c) || isdigit(c);
}

#undef isalpha
int isalpha(int c) {
	return islower(c) || isupper(c);
}

#undef isblank
int isblank(int c) {
	return (c == ' ' || c == '\t');
}

#undef iscntrl
int iscntrl(int c) 	{
	return c >= 0x0 && c <= 0x8;
}

#undef isdigit
int isdigit(int c) {
	return c >= '0' && c <= '9';
}

#undef isgraph
int isgraph(int c) {
	return ispunct(c) || isalnum(c);
}

#undef islower
int islower(int c) {
	return c >= 'a' && c <= 'z';
}

#undef isprint
int isprint(int c) {
	return isgraph(c) || isspace(c);
}

#undef ispunct
int ispunct(int c) {
	return (c >= 0x21 && c <= 0x2F) || (c >= 0x3A && c <= 0x40) || (c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7E);
}

#undef isspace
int isspace(int c) {
	return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\f' || c == '\v';
}

#undef isupper
int isupper(int c) {
	return c >= 'A' && c <= 'Z';
}

#undef isxdigit
int isxdigit(int c) {
	return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

#undef tolower
int tolower(int c) {
	if (isupper(c))
		return c + 'a' - 'A';
	return c;
}

#undef toupper
int toupper(int c) {
	if (islower(c)) 
		return c - 'a' + 'A';
	return c;
}
