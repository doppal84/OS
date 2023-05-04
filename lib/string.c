#include "string.h"
#include <stddef.h>
void itoa(char *buf, int num) {
    int index = 0;

    if (num == 0)
    {
        buf[index++] = '0';
        buf[index++] = '\0';
        return;
    }

    while (num != 0)
    {
        int digit = num % 10;
        buf[index++] = '0' + digit;
        num /= 10;
    }

    buf[index] = '\0';
    strrev(buf, index);
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

}

size_t strlen(const char *str) {
    size_t len = 0;
    while (*str++)
    {
        len++;
    }
    return len;
}

char *strrev(char *str, unsigned int length) {
    char *left, *right;
    left = str;
    right = str + (length - 1);
    while (left < right) {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
    return str;
}
void *memcpy(void *dest, const void * src, size_t n)
{
    unsigned char *d, *s;
    d = (unsigned char*)dest;
    s = (unsigned char*)src;
    for (size_t i = 0; i < n; i++)
    {
        *d++ = *s++;
    }
    return dest;
}
void *memset(void *str, int c, size_t n) 
{
    unsigned char *s =str;
    for (size_t i = 0; i < n; i++)
    {
        *s++ =(unsigned char)c;
    }
    return str;
}

