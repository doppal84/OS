#include "console.h"

int terminal_position = 0;
char* const VGA_BUFFER = (char*) 0xb8000;
void clear_screen()
{
	for(int i=0; i< VGA_TOTAL_BYTES; i+=2)
		{
			VGA_BUFFER[i] = 0;
			VGA_BUFFER[i+1] = 0x07;
		}
	terminal_position = 0;

}

void print_character(char c)
{
	if(c == '\n')
	{ terminal_position = (VGA_BYTES_PER_ROW - (terminal_position % VGA_BYTES_PER_ROW)) + terminal_position;
		return;
	}
	VGA_BUFFER[terminal_position] = c;
	VGA_BUFFER[++terminal_position] = 0x07;
	terminal_position = terminal_position + 1;
	

}

void print_string(char* str)
{
	for (int i=0; str[i] != '\0'; i++)
	{
		print_character(str[i]);
		
	}
	
}


void print_line(char* str)
{
	print_string(str);
	print_character('\n');	

}
