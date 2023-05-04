#ifndef H_LIB
#define H_LIB

#include <stddef.h>

void *memcpy(void *dest, const void * src, size_t n);
void *memset(void *str, int c, size_t n);
void itoa(char *buf, int num);
int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);
char *strrev(char *str, unsigned int length);

#endif
