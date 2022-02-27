/**
 * This file expose a collection of 64 bit
 * string functions.
 */

#ifndef STRING64
#define STRING64

int isdigit64(char c);

char *strcpy64(char *dst, const char *src);

int strlen64(const char *str);

const char* itoa64(int n);
const char* ltoa64(long n);

int atoi64(const char* str);

#endif
