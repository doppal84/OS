#include "lib.h"

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
