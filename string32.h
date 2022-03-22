/**
 * This file expose a collection of 32 bit
 * string functions.
 */

#ifndef STRING32
#define STRING32

int isdigit32(char c);

char *strcpy32(char *dst, const char *src);

int strlen32(const char *str);

const char* itoa32(int n);
const char* hex32(unsigned long n);

int atoi32(const char* str);

#endif
