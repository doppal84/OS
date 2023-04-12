#include "console.h"
#include "keyboard.h"

void main() {

	//clear_screen();
	//print_character('H');
	//print_string("ello");
	//print_line("world");
	//print_string("TODAY");
	unsigned char byte;
        while (1) {
                while (byte = scan()) {
                        
                        print_character(charmap[byte]);
                }
        }
	return;
}
