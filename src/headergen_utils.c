#include "headergen_utils.h"

#include <ctype.h>

static void strtoupper(char *dst, const char *src)
{
    while (*src)
    {
        *dst++ = (char)toupper(*src++);
    }
    
    *dst = '\0';
}

static void strntoupper(char *dst, const char *src, size_t n)
{
    size_t i = 0;

    while (*src && i < n)
    {
        *dst++ = (char)toupper(*src++);
        i++;
    }
    
    *dst = '\0';
}