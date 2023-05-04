#include "keyboard.h"
unsigned char inb(unsigned short int port) {

        unsigned char ret;
      __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "Nd" (port));
        return ret;
}

unsigned char scan(void) {

        unsigned char brk;
        static unsigned char key = 0;
        unsigned char scan = inb(0x60);
        brk = scan & 0x80;
        scan = scan & 0x7f;
        if (brk)
                return key = 0;
        else if (scan != key)
                return key = scan;
        else
                return 0;
}
