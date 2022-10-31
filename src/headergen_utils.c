#include "headergen_utils.h"

#include <ctype.h>

void strntoupper(char *dst, const char *src, size_t n)
{
    size_t i = 0;

    while (*src && i < n)
    {
        *dst++ = (char)toupper(*src++);
        i++;
    }
    
    *dst = '\0';
}

void strntouppersnakecase(char *dst, const char *src, size_t n)
{
    size_t i = 0;

    while (*src && i < n)
    {
        *dst = (char)toupper(*src++);
        if (*dst == ' ') *dst = '_';
        dst++;
        i++;
    }
    
    *dst = '\0';
}