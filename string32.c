#include "string32.h"

/**
 * @brief Does char rapresent digit
 * 
 * @param c 
 * @return int 
 */
int isdigit32(char c)
{
    return '0' <= c && c <= '9';
}

/**
 * @brief Copy src string in dst
 *
 * @param dst 
 * @param src 
 * @return char* 
 */
char *strcpy32(char *dst, const char *src)
{
    char *ans = dst;

    if (!dst || !src)
        return (void*)0;
    
    if (!*src)
        *dst = '\0';

    do {
        *dst++ = *src;
    } while (*src++);

    return ans;
}

int strlen32(const char *str)
{
    int len = 0;

    if (!str)
        return -1;

    while (*str++)
        ++len;    

    return len;
}

/**
 * @brief return a pointer to a
 *  statically allocated buffer
 *  contained the string representing
 *  the given integer
 * 
 * @param n 
 * @return const char* 
 */
const char* itoa32(int n)
{
    static char buffer[12];
    int i = 0;
    int digits = 0; /* number of digits in n */
    int copy;

    if (n == 0)
    {
        strcpy32(buffer, "0");
        return buffer;
    }

    if (n < 0)
    {
        n = -n;
        buffer[0] = '-';
        ++i;
    }

    /* Count digits */
    copy = n;
    while (n)
    {
        ++digits;
        n /= 10;
    }
    i += digits;
    /* Place zero terminator */
    buffer[i--] = '\0';
    while (copy)
    {
        buffer[i] = '0' + (copy % 10);
        copy /= 10;
        --i;
    }

    return buffer;
}

static char hexdigit32(int n)
{
    switch (n)
    {
    case  1: return '1';
    case  2: return '2';
    case  3: return '3';
    case  4: return '4';
    case  5: return '5';
    case  6: return '6';
    case  7: return '7';
    case  8: return '8';
    case  9: return '9';
    case 10: return 'a';
    case 11: return 'b';
    case 12: return 'c';
    case 13: return 'd';
    case 14: return 'e';
    case 15: return 'f';
    default: return '0';
    }
}

const char* hex32(unsigned long n)
{
    static char buffer[22] = "0x";
    int i = 0;

    // 32 bits = 8 hex digits
    for (i = 0; i != 8; ++i)
    {
        buffer[2+i] = hexdigit32((n >> 4*(15 - i)) & 0x0f);
    }

    return buffer;
}

int atoi32(const char* str)
{
    int number = 0;
    int negative = 0;

    if (!str || *str == '\0')
        return 0;

    switch (*str)
    {
    case '+':
        ++str;
        break;
    case '-':
        negative = 1;
        ++str;
        break;
    }

    /* There is a number? */
    if (!isdigit32(*str))
        return 0;

    do
    {
        number = number*10 + (*str - '0');
    } while (isdigit32(*++str));

    return negative ? -number : number;
}
